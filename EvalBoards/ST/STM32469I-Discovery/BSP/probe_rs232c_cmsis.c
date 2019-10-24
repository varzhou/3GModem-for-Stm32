/*
*********************************************************************************************************
*                                       uC/Probe Communication
*
*                         (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        COMMUNICATION: RS-232
*
*                                          PORT FOR ST STM32
*
* Filename      : probe_rs232c.c
* Version       : V2.20
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_rs232.h>
#include  <bsp.h>
#include  <os.h>
#include  "stm32f4xx_hal.h"


/*
*********************************************************************************************************
*                                               ENABLE
*
* Note(s) : (1) See 'probe_rs232.h  ENABLE'.
*********************************************************************************************************
*/

#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)                     /* See Note #1.                                         */


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
static UART_HandleTypeDef ProbeRS232UartHandle;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef    PROBE_RS232_CFG_COMM_SEL

  #error  "PROBE_RS232_CFG_COMM_SEL          not #define'd in 'probe_com_cfg.h'"
  #error  "                                  [MUST be  PROBE_RS232_UART_3]     "
  #error  "                                  [     ||  PROBE_RS232_UART_6]     "

#elif     (PROBE_RS232_CFG_COMM_SEL != PROBE_RS232_UART_3) && \
          (PROBE_RS232_CFG_COMM_SEL != PROBE_RS232_UART_6)

  #error  "PROBE_RS232_CFG_COMM_SEL    illegally #define'd in 'probe_com_cfg.h'"
  #error  "                                  [MUST be  PROBE_RS232_UART_3]     "
  #error  "                                  [     ||  PROBE_RS232_UART_6]     "
#endif


/*
*********************************************************************************************************
*                                       ProbeRS232_InitTarget()
*
* Description : Initialize the UART for Probe communication.
*
* Argument(s) : baud_rate       Intended baud rate of the RS-232.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_Init().
*
* Note(s)     : (1) Though the baud rate used may vary from application to application or target to
*                   target, other communication settings are constamt.  The hardware must always be
*                   configured for the following :
*
*                   (a) No parity
*                   (b) One stop bit
*                   (c) Eight data bits.
*
*               (2) Neither receive nor transmit interrupts should be enabled by this function.
*
*               (3) The following constants control the GPIO remap for the USART control lines :
*
*                        PROBE_RS232_UART_3_REMAP
*                        PROBE_RS232_UART_6_REMAP
*                        PROBE_RS232_UART_3_REMAP_PARTIAL
*                        PROBE_RS232_UART_3_REMAP_FULL
*
*                    Though the #error directives in 'LOCAL CONFIGURATION ERRORS' will require that
*                    all are defined, the value of those bearing on the USART not used will have no
*                    effect.
*
*                (4) PROBE_RS232_UART_3_REMAP_PARTIAL has precedence over PROBE_RS232_UART_3_REMAP_FULL,
*                    if both are defined to DEF_TRUE.
*********************************************************************************************************
*/

void  ProbeRS232_InitTarget (CPU_INT32U baud_rate)
{
    GPIO_InitTypeDef        GPIO_InitStruct;

                                                                /* ----------------- INIT USART STRUCT ---------------- */
    ProbeRS232UartHandle.Init.BaudRate   = baud_rate;
    ProbeRS232UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    ProbeRS232UartHandle.Init.StopBits   = UART_STOPBITS_1;
    ProbeRS232UartHandle.Init.Parity     = UART_PARITY_NONE;
    ProbeRS232UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    ProbeRS232UartHandle.Init.Mode       = UART_MODE_TX_RX;


#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_3)
    __HAL_RCC_GPIOB_CLK_ENABLE();       /* Enable GPIO clock.                                   */
    __HAL_RCC_USART3_CLK_ENABLE();      /* Enable UART clock.                                   */
    
    /* ----------------- SETUP USART3 GPIO ---------------- */
    /* Configure GPIOB.10 as push-pull.                      */
    GPIO_InitStruct.Pin       = GPIO_PIN_10;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    /* Configure GPIOB.11 as input floating.                 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    /* ------------------ SETUP USART3 -------------------- */
    ProbeRS232UartHandle.Instance        = USART3;
    if(HAL_UART_DeInit(&ProbeRS232UartHandle) != HAL_OK)
    {
        while(1);
    }  
    if(HAL_UART_Init(&ProbeRS232UartHandle) != HAL_OK)
    {
        while(1);
    }

    BSP_IntVectSet(BSP_INT_ID_USART3, ProbeRS232_RxTxISRHandler);
    BSP_IntEn(BSP_INT_ID_USART3);
#endif


#if (PROBE_RS232_CFG_COMM_SEL == PROBE_RS232_UART_6)
    __HAL_RCC_GPIOC_CLK_ENABLE();       /* Enable GPIO clock.                                   */
    __HAL_RCC_USART6_CLK_ENABLE();      /* Enable UART clock.                                   */
    
    /* ----------------- SETUP USART3 GPIO ---------------- */
    /* Configure GPIOC.6 as push-pull.                      */
    GPIO_InitStruct.Pin       = GPIO_PIN_6;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    /* Configure GPIOC.7 as input floating.                 */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


    /* ------------------ SETUP USART6 -------------------- */
    ProbeRS232UartHandle.Instance        = USART6;
    if(HAL_UART_DeInit(&ProbeRS232UartHandle) != HAL_OK)
    {
        while(1);
    }  
    if(HAL_UART_Init(&ProbeRS232UartHandle) != HAL_OK)
    {
        while(1);
    }

    BSP_IntVectSet(BSP_INT_ID_USART6, ProbeRS232_RxTxISRHandler);
    BSP_IntEn(BSP_INT_ID_USART6);
#endif

}


/*
*********************************************************************************************************
*                                     ProbeRS232_RxTxISRHandler()
*
* Description : Handle Rx and Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) If this port is used in an RTOS, the interrupt entrance/exit procedure should be
*                   performed by the ISR that calls this handler.
*********************************************************************************************************
*/

void  ProbeRS232_RxTxISRHandler (void)
{
    CPU_INT08U      rx_data;

    if (__HAL_UART_GET_FLAG(&ProbeRS232UartHandle, UART_FLAG_RXNE) != RESET) {
        rx_data = ProbeRS232UartHandle.Instance->DR & 0xFF;              /* Read one byte from the receive data register.        */
        ProbeRS232_RxHandler(rx_data);
        __HAL_UART_CLEAR_FLAG(&ProbeRS232UartHandle, UART_FLAG_RXNE);          /* Clear the USART3 receive interrupt.                  */
    }

    if (__HAL_UART_GET_FLAG(&ProbeRS232UartHandle, UART_FLAG_TXE) != RESET) {
        ProbeRS232_TxHandler();
//        USART_ClearITPendingBit(usart, USART_IT_TXE);           /* Clear the USART3 transmit interrupt.                 */
    }
}

/*
*********************************************************************************************************
*                                      ProbeRS232_RxISRHandler()
*
* Description : Handle Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) This function is empty because receive interrupts are handled by ProbeRS232_RxTxISRHandler().
*********************************************************************************************************
*/

void  ProbeRS232_RxISRHandler (void)
{
}


/*
*********************************************************************************************************
*                                        ProbeRS232_RxIntDis()
*
* Description : Disable Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The application should call this function to stop communication.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntDis (void)
{
    __HAL_UART_DISABLE_IT(&ProbeRS232UartHandle, UART_IT_RXNE);
}


/*
*********************************************************************************************************
*                                        ProbeRS232_RxIntEn()
*
* Description : Enable Rx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The application should call this function to start communication.
*********************************************************************************************************
*/

void  ProbeRS232_RxIntEn (void)
{
    __HAL_UART_ENABLE_IT(&ProbeRS232UartHandle, UART_IT_RXNE);
}


/*
*********************************************************************************************************
*                                      ProbeRS232_TxISRHandler()
*
* Description : Handle Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : This function is empty because transmit interrupts are handled by ProbeRS232_RxTxISRHandler().
*********************************************************************************************************
*/

void  ProbeRS232_TxISRHandler (void)
{
}


/*
*********************************************************************************************************
*                                          ProbeRS232_Tx1()
*
* Description : Transmit one byte.
*
* Argument(s) : c           The byte to transmit.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_Tx1 (CPU_INT08U c)
{
    ProbeRS232UartHandle.Instance->DR = c;
}


/*
*********************************************************************************************************
*                                        ProbeRS232_TxIntDis()
*
* Description : Disable Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntDis (void)
{
    __HAL_UART_DISABLE_IT(&ProbeRS232UartHandle, USART_IT_TXE);
}

/*
*********************************************************************************************************
*                                        ProbeRS232_TxIntEn()
*
* Description : Enable Tx interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeRS232_TxStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeRS232_TxIntEn (void)
{
    __HAL_UART_ENABLE_IT(&ProbeRS232UartHandle, USART_IT_TXE);
}


/*
*********************************************************************************************************
*                                              ENABLE END
*
* Note(s) : See 'ENABLE  Note #1'.
*********************************************************************************************************
*/

#endif
