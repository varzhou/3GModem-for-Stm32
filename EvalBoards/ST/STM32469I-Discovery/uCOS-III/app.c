/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <includes.h>
#include  <os_app_hooks.h>
#include  "stm32f4xx_hal.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/* ----------------- APPLICATION GLOBALS -------------- */
 OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart          (void     *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : 1) STM32F4xx HAL library initialization:
*                      a) Configures the Flash prefetch, intruction and data caches.
*                      b) Configures the Systick to generate an interrupt. However, the function ,
*                         HAL_InitTick(), that initializes the Systick has been overwritten since Micrium's
*                         RTOS has its own Systick initialization and it is recommended to initialize the
*                         Systick after multitasking has started.
*
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR  err;

    HAL_Init();                                                 /* See Note 1.                                          */

    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    Math_Init();                                                /* Initialize Mathematical Module                       */

    BSP_IntDisAll();                                            /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */
    App_OS_SetAllHooks();
    
    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"App Task Start",
                 (OS_TASK_PTR   )AppTaskStart,
                 (void         *)0u,
                 (OS_PRIO       )APP_TASK_START_PRIO,
                 (CPU_STK      *)&AppTaskStartStk[0u],
                 (CPU_STK_SIZE  )APP_TASK_START_STK_SIZE / 10u,
                 (CPU_STK_SIZE  )APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
#include "bsp_ser.h"
#include "usbh_linux.h"
#include "memory.h"
#include "shell.h"
#include "lwip/tcpip.h"
#include "lwip/stats.h"
#include "ping.h"

#include "stm32469i_discovery_lcd.h"


extern void iperf_init(void);
extern int modem_init(void);
extern int usb_modeswitch_init(void);



CPU_INT16S clear (CPU_INT16U argc,
                       CPU_CHAR *argv[],
                       SHELL_OUT_FNCT out_fnct,
                       SHELL_CMD_PARAM *pcmd_param)
{
    /*clear lcd terminal sreen*/
    lcd_terminal_clear();
    return 0;
}

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR      err;
    SHELL_ERR shell_err;

    (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    
    /* Initializes uC/Shell */
    Shell_Init();
    /* Create tcp_ip stack thread */
    tcpip_init( NULL, NULL );
    
    /* Initializes iperf */
    iperf_init();

#ifndef USE_LWIP_MALLOC
    /* Initialize heap if not merge kmalloc() with lwip mem_malloc() function.
     * see memory.h */
    usbh_mem_init();
#endif
    
    /* Initializes usb host */
    usb_init();

    /* Register 3G modem(virtual serial) driver */    
    modem_init();
    /* Register usb_modeswitch driver */
    usb_modeswitch_init();   
     
    /* If all usb driver are initialized, start usb host. */
    usb_start();
    
    
    /* Add lwip stats command*/    
    Shell_CmdTblAdd("stats", (SHELL_CMD[]){ {"stats", (SHELL_CMD_FNCT)stats_display}, {0, 0 }}, &shell_err);    
    /* Add ping command*/    
    Shell_CmdTblAdd("ping",  (SHELL_CMD[]){ {"ping", ping}, {0, 0 }}, &shell_err);  
    /* Add LCD clear command*/    
    Shell_CmdTblAdd("clear", (SHELL_CMD[]){ {"clear", clear}, {0, 0 }}, &shell_err);     


    while (DEF_TRUE)                                            /* Task body, always written as an infinite loop.       */
    {
        OSTimeDlyHMSM(0u, 0u, 0u, 500,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}





void assert_failed(uint8_t *file, uint32_t line)
{
    printf("assert_failed in:%s,line:%d \n", file ? (char *)file : "n", line);
    while (1);
}




static CPU_CHAR  my_buf_str[128];
extern UART_HandleTypeDef UartHandle;

void  my_printf (char *format, ...)
{

    va_list   v_args;
    char  *p_str = &my_buf_str[0];


    va_start(v_args, format);
    (void)vsnprintf((char       *)&my_buf_str[0],
                    (CPU_SIZE_T  ) sizeof(my_buf_str),
                    (char const *) format,
                    v_args);
    va_end(v_args);


    while ((*p_str) != (CPU_CHAR )0)
    {
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TXE) == 0);
        UartHandle.Instance->DR = *p_str & 0XFF;
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TC) == 0);

        p_str++;
    }

}

#define printf my_printf



void hard_fault_handler_c (unsigned int * hardfault_args)
{
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;
    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);
    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    printf ("\r\n\r\n[Hard fault handler - all numbers in hex]\r\n");
    printf ("R0 = %x\r\n", stacked_r0);
    printf ("R1 = %x\r\n", stacked_r1);
    printf ("R2 = %x\r\n", stacked_r2);
    printf ("R3 = %x\r\n", stacked_r3);
    printf ("R12 = %x\r\n", stacked_r12);
    printf ("LR [R14] = %x subroutine call return address\r\n", stacked_lr);
    printf ("PC [R15] = %x program counter\r\n", stacked_pc);
    printf ("PSR = %x\r\n", stacked_psr);
    printf ("BFAR = %x\r\n", (*((volatile unsigned long *)(0xE000ED38))));
    printf ("CFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED28))));
    printf ("HFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED2C))));
    printf ("DFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED30))));
    printf ("AFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED3C))));
    printf ("SCB_SHCSR = %x\r\n", SCB->SHCSR);

    printf("OSIntNestingCtr:%d  OSSchedLockNestingCtr:%d CPU_IntDisNestCtr:%d\r\n",OSIntNestingCtr,OSSchedLockNestingCtr,CPU_IntDisNestCtr);
    printf("OSTCBCurPtr->NamePtr = %s StkSize:%d  StkUsed:%d\r\n",OSTCBCurPtr->NamePtr,OSTCBCurPtr->StkSize,OSTCBCurPtr->StkUsed);


    while (1);
}


