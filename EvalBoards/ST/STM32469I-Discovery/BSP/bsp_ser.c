/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2012; Micrium, Inc.; Weston, FL
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
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                       SERIAL (UART) INTERFACE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3220G-EVAL
*                                         Evaluation Board
*
* Filename      : bsp_ser.c
* Version       : V1.00
* Programmer(s) : SL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#define  BSP_SER_MODULE
#include <bsp.h>
#include <bsp_os.h>
#include <bsp_ser.h>
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery_lcd.h"
#include "bmd.h"
#include "stdio.h"
#include "string.h"
#include "shell.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/



/* USART3 is directly available as a virtual COM port of the PC connected
*  to the ST-LINK/V2-1 USB connector CN1.
*  USART6 is connected to Extension connector CN12.
*/
//#define  USE_USART6
#define  USE_USART3



/* Define USE_BUF_PRINTF to enable printf function write message to memory fifo that
*  will be handled in BSP_Ser_RxHandle().
*  This macro is useful when you want printf function is non-blocking.
*/
#define USE_BUF_PRINTF


/*serial baudrate*/
#define  BSP_SER_COMM_BAUDRATE            115200


#define  SERIAL_RX_BUFFER_SIZE            80
#define  SERIAL_TX_BUFFER_SIZE            4*1024


#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_CMD_SIZE      160
#define FINSH_PROMPT      ">"
#define rt_kprintf printf
#define rt_strlen strlen


static BSP_OS_SEM   BSP_SerTxWait;
static BSP_OS_SEM   BSP_SerRxWait;


UART_HandleTypeDef UartHandle;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static BUFFER_INFO rx_buf_ring;
static CPU_INT08U rx_buffer[SERIAL_RX_BUFFER_SIZE];

static OS_TCB   BspSerTaskTCB;
static CPU_STK  BspSerTaskStk[BSP_SER_TASK_STK_SIZE];

#ifdef USE_BUF_PRINTF
static BUFFER_INFO tx_buf_ring;
static CPU_INT08U tx_buffer[SERIAL_TX_BUFFER_SIZE];
#endif

static OS_TCB   SerShellExecTaskTCB;
static CPU_STK  SerShellExecTaskStk[SER_SHELL_EXEC_TASK_STK_SIZE];

static int SerRxDisable;
/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/




extern DMA2D_HandleTypeDef hdma2d_eval;
extern LTDC_HandleTypeDef  hltdc_eval;


OS_MUTEX dma2d_mutex_lock;
OS_SEM dma2d_complete_sem;

struct
{
    int window_x;
    int window_y;
    int window_width;
    int window_height;

    int cursor_x;
    int cursor_y;
    
    char line[FINSH_CMD_SIZE + sizeof(FINSH_PROMPT)];
    int char_index;

    BSP_OS_SEM lock;
} lcd_terminal;


static void dma2d_complete_callback(struct __DMA2D_HandleTypeDef * hdma2d)
{
    OS_ERR err;
    OSSemPost(&dma2d_complete_sem, OS_OPT_POST_1, &err);
}

static void dma2d_error_callback(struct __DMA2D_HandleTypeDef * hdma2d)
{
    OS_ERR err;
    OSSemPost(&dma2d_complete_sem, OS_OPT_POST_1, &err);
}

void dma2d_wait_complete()
{
    OS_ERR err;
    OSSemPend(&dma2d_complete_sem, 0, OS_OPT_PEND_BLOCKING, NULL, &err);
}

//clear terminal sreen
void lcd_terminal_clear()
{
    uint32_t Address;
    int lcd_x_size;
    OS_ERR err;
    
    BSP_OS_SemWait(&lcd_terminal.lock, 0);

    OSMutexPend(&dma2d_mutex_lock, 0, OS_OPT_PEND_BLOCKING, NULL, &err);
  

    lcd_terminal.cursor_x = 0;
    lcd_terminal.cursor_y = 0;

    lcd_x_size = BSP_LCD_GetXSize();
    Address = hltdc_eval.LayerCfg[/*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND].FBStartAdress \
                 + ((lcd_x_size*(lcd_terminal.window_y) + lcd_terminal.window_x)*(4));

    /* Register to memory mode with ARGB8888 as color Mode */
    hdma2d_eval.Init.Mode         = DMA2D_R2M;
    hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888;
    hdma2d_eval.Init.OutputOffset = (lcd_x_size - lcd_terminal.window_width);

    hdma2d_eval.Instance = DMA2D;

    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
    {
        if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, /*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND) == HAL_OK)
        {
            if (HAL_DMA2D_Start_IT(&hdma2d_eval, BSP_LCD_GetBackColor(), (uint32_t)Address, lcd_terminal.window_width, lcd_terminal.window_height) == HAL_OK)
            {
                /* Polling For DMA transfer */
                dma2d_wait_complete();
//                HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
            }
        }
    }
    

    OSMutexPost(&dma2d_mutex_lock, OS_OPT_POST_NONE, &err);   

    BSP_OS_SemPost(&lcd_terminal.lock);
}



//scroll up a line
void lcd_scroll_up()
{
    OS_ERR err;
    int line_num;
    sFONT *font;
    int lcd_x_size;
    int SrcAddress;
    int DstAddress;

    font = BSP_LCD_GetFont();
    lcd_x_size = BSP_LCD_GetXSize();  
    line_num = lcd_terminal.window_height/font->Height;


    OSMutexPend(&dma2d_mutex_lock, 0, OS_OPT_PEND_BLOCKING, NULL, &err);
  
    /* Set the address */
    DstAddress = hltdc_eval.LayerCfg[/*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND].FBStartAdress + (((lcd_x_size*lcd_terminal.window_y) + lcd_terminal.window_x)*(4));
    SrcAddress = DstAddress + 4*lcd_x_size*font->Height;

    /* Configure the DMA2D Mode, Color Mode and output offset */
    hdma2d_eval.Init.Mode         = DMA2D_M2M;
    hdma2d_eval.Init.ColorMode    = CM_ARGB8888;
    hdma2d_eval.Init.OutputOffset = (lcd_x_size - lcd_terminal.window_width);

    /* Foreground Configuration */
    hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
    hdma2d_eval.LayerCfg[1].InputColorMode = CM_ARGB8888;
    hdma2d_eval.LayerCfg[1].InputOffset = (lcd_x_size - lcd_terminal.window_width);

    hdma2d_eval.Instance = DMA2D;

    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
    {
        if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
        {
            if (HAL_DMA2D_Start_IT(&hdma2d_eval, (uint32_t)SrcAddress, (uint32_t)DstAddress, lcd_terminal.window_width, (line_num - 1)*font->Height) == HAL_OK)
            {
                /* Polling For DMA transfer */
                dma2d_wait_complete();
//                HAL_DMA2D_PollForTransfer(&hdma2d_eval, 30);
            }
        }
    }
    

    //clear the last line
    DstAddress = hltdc_eval.LayerCfg[/*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND].FBStartAdress \
                 + (((lcd_x_size*(lcd_terminal.window_y + (line_num - 1)*font->Height)) + lcd_terminal.window_x)*(4));

    /* Register to memory mode with ARGB8888 as color Mode */
    hdma2d_eval.Init.Mode         = DMA2D_R2M;
    hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888;
    hdma2d_eval.Init.OutputOffset = (lcd_x_size - lcd_terminal.window_width);

    hdma2d_eval.Instance = DMA2D;

    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
    {
        if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, /*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND) == HAL_OK)
        {
            if (HAL_DMA2D_Start_IT(&hdma2d_eval, BSP_LCD_GetBackColor(), (uint32_t)DstAddress, lcd_terminal.window_width, font->Height) == HAL_OK)
            {
                /* Polling For DMA transfer */
                dma2d_wait_complete();
//                HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
            }
        }
    }

    OSMutexPost(&dma2d_mutex_lock, OS_OPT_POST_NONE, &err);   
}


void lcd_show_cursor()
{
    uint32_t i = 0, j = 0, x_pos, y_pos;
    uint16_t height, width;
    uint8_t  offset;
    uint8_t  *pchar;
    uint32_t line;
    __IO uint32_t* address;
    const uint8_t *c;
    sFONT *font;
    int lcd_x_size;
    uint32_t BackColor,TextColor;
    

    font = BSP_LCD_GetFont();
    lcd_x_size = BSP_LCD_GetXSize();
    BackColor = BSP_LCD_GetBackColor();
    TextColor = BSP_LCD_GetTextColor();

    x_pos = lcd_terminal.window_x + lcd_terminal.cursor_x * font->Width;
    y_pos = lcd_terminal.window_y + lcd_terminal.cursor_y * font->Height;
    c = &font->table[(lcd_terminal.line[lcd_terminal.char_index] - ' ') * font->Height * ((font->Width + 7) / 8)];

    
    height = font->Height;
    width  = font->Width;
    
    offset =  8 *((width + 7)/8) -  width ;
    address = (__IO uint32_t*) (hltdc_eval.LayerCfg[/*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND].FBStartAdress + (4*(y_pos*lcd_x_size + x_pos)));
           
    for(i = 0; i < height; i++)
    {
      pchar = ((uint8_t *)c + (width + 7)/8 * i);
    
      switch(((width + 7)/8))
      {
    
      case 1:
        line =  pchar[0];
        break;
    
      case 2:
        line =  (pchar[0]<< 8) | pchar[1];
        break;
    
      case 3:
      default:
        line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
        break;
      }
    
      for (j = 0; j < width; j++)
      {
        if(line & (1 << (width- j + offset- 1)))
        {
            *address = BackColor;
        }
        else
        {
            *address = TextColor;
        }

        address++; 
      }

      address += lcd_x_size - width;
    }
}



void lcd_put_char_unlock(char ch)
{;
    sFONT *font = BSP_LCD_GetFont();


    int x_pos = lcd_terminal.window_x + lcd_terminal.cursor_x * font->Width;
    int y_pos = lcd_terminal.window_y + lcd_terminal.cursor_y * font->Height;


    if(lcd_terminal.window_width < font->Width
        || lcd_terminal.window_height < font->Height)
        return;


    if(ch == '\r')
    {
        //clear cursor flicker          
        BSP_LCD_DisplayChar(x_pos, y_pos, lcd_terminal.line[lcd_terminal.char_index]);  

        lcd_terminal.char_index -= lcd_terminal.cursor_x;
        lcd_terminal.cursor_x = 0;
        return;
    }
    else if(ch == '\n')
    {
        //clear cursor flicker          
        BSP_LCD_DisplayChar(x_pos, y_pos, lcd_terminal.line[lcd_terminal.char_index]);
        
        if((lcd_terminal.cursor_y + 1 + 1)* font->Height > lcd_terminal.window_height)
            lcd_scroll_up();
        else
            lcd_terminal.cursor_y ++;

        lcd_terminal.cursor_x = 0;
        lcd_terminal.char_index = 0;
        memset(lcd_terminal.line, ' ', sizeof(lcd_terminal.line));
        return;
    }
    else if(ch == '\b')
    {
        //clear cursor flicker          
        BSP_LCD_DisplayChar(x_pos, y_pos, lcd_terminal.line[lcd_terminal.char_index]);   

        lcd_terminal.char_index --;
        if(lcd_terminal.char_index < 0) 
            lcd_terminal.char_index = 0;   

        if(lcd_terminal.char_index == lcd_terminal.window_width/font->Width - 1)
            lcd_terminal.cursor_y = lcd_terminal.cursor_y - 1;
        
        lcd_terminal.cursor_x = lcd_terminal.char_index % (lcd_terminal.window_width/font->Width); 

        lcd_show_cursor();
        return;
    }
    else if(ch < ' ')
    {
        return;
    }

    if(lcd_terminal.char_index >= sizeof(lcd_terminal.line) - 1)
        return;


    /* Display one character on LCD */
    BSP_LCD_DisplayChar(x_pos, y_pos, ch);
    lcd_terminal.line[lcd_terminal.char_index] = ch;
    lcd_terminal.char_index++;
    lcd_terminal.cursor_x++;

    /*Check if out of the range of window*/
    if((lcd_terminal.cursor_x + 1) * font->Width > lcd_terminal.window_width)
    {
        if((lcd_terminal.cursor_y + 1 + 1) * font->Height > lcd_terminal.window_height)
            lcd_scroll_up();
        else
            lcd_terminal.cursor_y ++;

        lcd_terminal.cursor_x = 0;
        return;             
    }
}


void lcd_put_char(char ch)
{
    static char buf[4] = {0};
    static int buf_index = -1;
    static char pre_ch = '\0';
    static OS_TICK pre_time = 0;
    
    OS_ERR err;
    int len = 0, i, x_pos, y_pos;
    
    if (OSIntNestingCtr > (OS_NESTING_CTR)0) {              /* Not allowed to call from an ISR                        */
        return;
    }

    if (OSSchedLockNestingCtr > (OS_NESTING_CTR)0) {              /* Not allowed to call from an ISR                        */
        return;
    }
    
    BSP_OS_SemWait(&lcd_terminal.lock, 0);

    if(pre_ch == '\033' && ch == '[')
        buf_index = 0;
    

    if(buf_index >= 0)
    {
        buf[buf_index++] = ch;

        if(buf_index == 3 && !strncmp(buf, "[2K", buf_index))
        {
            sFONT *font = BSP_LCD_GetFont();
            //erases everything written on line before this        
            for ( i = lcd_terminal.cursor_x ; i >= 0; i-- )
            {
                x_pos = lcd_terminal.window_x + i * font->Width;
                y_pos = lcd_terminal.window_y + lcd_terminal.cursor_y * font->Height;            
                BSP_LCD_DisplayChar(x_pos, y_pos, ' ');   
            }  
            lcd_terminal.cursor_x = 0;
            lcd_terminal.char_index = 0;
            memset(lcd_terminal.line, ' ', sizeof(lcd_terminal.line));
            len  = buf_index;
        }

        if(len || buf_index == sizeof(buf))
        {
            //show other char in buf.
            for ( i = len ; i < buf_index; i++ )
            {
                lcd_put_char_unlock(buf[i]);
            }
            buf_index = -1;
        }

        BSP_OS_SemPost(&lcd_terminal.lock);
        return;
    }

    
    lcd_put_char_unlock(ch); 
    if(OSTimeGet(&err) - pre_time >= 15)
        lcd_show_cursor();

    pre_ch = ch;  
    pre_time = OSTimeGet(&err);
    BSP_OS_SemPost(&lcd_terminal.lock);
}

void lcd_cursor_flicker()
{
    __IO uint32_t*address;
    int i,j,x_pos,y_pos;
    uint32_t pixel;
    int lcd_x_size;
    sFONT *font;
    uint32_t BackColor,TextColor;


    BSP_OS_SemWait(&lcd_terminal.lock, 0);

    lcd_x_size = BSP_LCD_GetXSize();    
    font = BSP_LCD_GetFont();
    BackColor = BSP_LCD_GetBackColor();
    TextColor = BSP_LCD_GetTextColor();

    x_pos = lcd_terminal.window_x + lcd_terminal.cursor_x * font->Width;
    y_pos = lcd_terminal.window_y + lcd_terminal.cursor_y * font->Height;


    for(j = y_pos; j < font->Height + y_pos; j++)
    {
        for(i = x_pos; i < font->Width + x_pos; i ++)
        {     
            address = (__IO uint32_t*) (hltdc_eval.LayerCfg[/*ActiveLayer*/LTDC_ACTIVE_LAYER_BACKGROUND].FBStartAdress + (4*(j*lcd_x_size + i)));
            pixel = *address;
     
            if(pixel == BackColor)
                *address = TextColor;
            else
                *address = BackColor;
        }
    }

    BSP_OS_SemPost(&lcd_terminal.lock);
}



void lcd_terminal_init(int window_x, int window_y, int window_width, int window_height)
{
    OS_ERR err;
    
    lcd_terminal.window_x = window_x;
    lcd_terminal.window_y = window_y;
    lcd_terminal.window_width = window_width;
    lcd_terminal.window_height = window_height;

    lcd_terminal.cursor_x = 0;
    lcd_terminal.cursor_y = 0;
    lcd_terminal.char_index = 0;
    memset(lcd_terminal.line, ' ', sizeof(lcd_terminal.line));
    BSP_OS_SemCreate(&lcd_terminal.lock,   1, "lcd terminal lock");


    OSSemCreate(&dma2d_complete_sem, "dma2d_complete_sem", 0, &err);
    hdma2d_eval.XferCpltCallback = dma2d_complete_callback;
    hdma2d_eval.XferErrorCallback = dma2d_error_callback;
    OSMutexCreate(&dma2d_mutex_lock, "DMA2D_MutexLock", &err);
}





struct finsh_shell
{
    CPU_INT08U use_history:1;
    CPU_INT08U stat;
#ifdef FINSH_USING_HISTORY
    CPU_INT08U current_history;
    CPU_INT16U history_count;

    char cmd_history[FINSH_HISTORY_LINES][FINSH_CMD_SIZE];
#endif

    char line[FINSH_CMD_SIZE];
    CPU_INT08U line_position;
    CPU_INT08U line_curpos;
};


struct finsh_shell _shell;

#define WAIT_NORMAL     0
#define WAIT_SPEC_KEY   1
#define WAIT_FUNC_KEY   2





static int str_is_prefix(const char *prefix, const char *str)
{
    while ((*prefix) && (*prefix == *str))
    {
        prefix ++;
        str ++;
    }

    if (*prefix == 0)
        return 0;

    return -1;
}


static int str_common(const char *str1, const char *str2)
{
    const char *str = str1;

    while ((*str != 0) && (*str2 != 0) && (*str == *str2))
    {
        str ++;
        str2 ++;
    }

    return (str - str1);
}





void shell_auto_complete(char* prefix)
{
    SHELL_MODULE_CMD  *module_cmd;
    CPU_INT16U func_cnt ,index;
    int length, min_length=0;
    char *name_ptr;


    rt_kprintf("\n");

    func_cnt = 0;
    module_cmd = Shell_ModuleCmdUsedPoolPtr;
    name_ptr = NULL;


    while (module_cmd)
    {

        for (index = 0; module_cmd->CmdTblPtr[index].Name != NULL; index ++)
        {
            if (str_is_prefix(prefix, module_cmd->CmdTblPtr[index].Name) == 0)
            {
                if (func_cnt == 0)
                {
                    rt_kprintf("--function:\n");

                    if (*prefix != 0)
                    {
                        /* set name_ptr */
                        name_ptr = module_cmd->CmdTblPtr[index].Name;

                        /* set initial length */
                        min_length = strlen(name_ptr);
                    }
                }

                func_cnt ++;

                if (*prefix != 0)
                {
                    length = str_common(name_ptr, module_cmd->CmdTblPtr[index].Name);
                    if (length < min_length)
                        min_length = length;
                }

//#ifdef FINSH_USING_DESCRIPTION
//                        rt_kprintf("%-16s -- %s\n", index->name, index->desc);
//#else
                rt_kprintf("%s\n", module_cmd->CmdTblPtr[index].Name);
//#endif
            }
        }
        module_cmd = module_cmd->NextModuleCmdPtr;
    }


    if (name_ptr != NULL)
    {
        strncpy(prefix, name_ptr, min_length);
    }

    rt_kprintf("%s%s", FINSH_PROMPT, prefix);
}


#ifdef FINSH_USING_HISTORY
static CPU_INT08U shell_handle_history(struct finsh_shell* shell)
{

    rt_kprintf("\033[2K\r");

    rt_kprintf("%s%s", FINSH_PROMPT, shell->line);
    return 0;
}

static void shell_push_history(struct finsh_shell* shell)
{
    if (shell->line_position != 0)
    {
        /* push history */
        if (shell->history_count >= FINSH_HISTORY_LINES)
        {
            /* move history */
            int index;
            for (index = 0; index < FINSH_HISTORY_LINES - 1; index ++)
            {
                memcpy(&shell->cmd_history[index][0],
                       &shell->cmd_history[index + 1][0], FINSH_CMD_SIZE);
            }
            memset(&shell->cmd_history[index][0], 0, FINSH_CMD_SIZE);
            memcpy(&shell->cmd_history[index][0], shell->line, shell->line_position);

            /* it's the maximum history */
            shell->history_count = FINSH_HISTORY_LINES;
        }
        else
        {
            memset(&shell->cmd_history[shell->history_count][0], 0, FINSH_CMD_SIZE);
            memcpy(&shell->cmd_history[shell->history_count][0], shell->line, shell->line_position);

            /* increase count and set current history position */
            shell->history_count ++;
        }
    }
    shell->current_history = shell->history_count;
}
#endif




/*
*********************************************************************************************************
*                                         BSP_Ser_ISR_Handler()
*
* Description : Serial ISR
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_ISR_Handler (void)
{
    CPU_REG32  status;
    CPU_INT08U ret,rx_byte;


    status = UartHandle.Instance->SR;

    if (DEF_BIT_IS_SET(status, DEF_BIT_05))
    {
        rx_byte = UartHandle.Instance->DR & 0xFF;       /* Read one byte from the receive data register.      */
        Buf_IsFull(&rx_buf_ring, ret);
        if(ret == Buff_notFull)
            Buf_Push(&rx_buf_ring, rx_byte);

        __HAL_UART_CLEAR_FLAG(&UartHandle, UART_FLAG_RXNE);
        BSP_OS_SemPost(&BSP_SerRxWait);                         /* Post to the sempahore                              */
    }

    if (DEF_BIT_IS_SET(status, DEF_BIT_07))
    {
        __HAL_UART_DISABLE_IT(&UartHandle, USART_IT_TXE);
        BSP_OS_SemPost(&BSP_SerTxWait);                         /* Post to the semaphore                              */
    }

}


void BSP_Ser_Rx_Disable()
{
    SerRxDisable = 1;
}

void BSP_Ser_Rx_Enable()
{
    SerRxDisable = 0;
}


int BSP_Ser_Read(unsigned char *buf, int len)
{
    unsigned char ch,*p = buf;
    int ret;

    while(len>0)
    {
        Buf_IsEmpty(&rx_buf_ring, ret);
        if(ret == Buff_isEmpty)
            break;

        Buf_Pop(&rx_buf_ring, ch);
        *p++ = ch;
        len--;
    }

    return p-buf;      
}

int BSP_Ser_Write(unsigned char *buf, int len)
{
    unsigned char *p=buf;

    while(len>0)
    {
#ifdef USE_BUF_PRINTF
        CPU_INT08U ret;
        CPU_SR cpu_sr;
    
        CPU_CRITICAL_ENTER();
    
        Buf_IsFull(&tx_buf_ring, ret);
        if(ret == Buff_isFull){
            CPU_CRITICAL_EXIT();
            break;
        }
        Buf_Push(&tx_buf_ring, ((*p)&0xff));
            
        CPU_CRITICAL_EXIT();
#else        
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TXE) == 0);
        UartHandle.Instance->DR = ch & 0XFF;
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TC) == 0);
    
        lcd_put_char(*p);
#endif
        len--;
        p++;
    }

    return p-buf;
}


void Ser_Shell_Exec_Task(void *p_arg)
{
    int *shell_exec_lock = p_arg;
    SHELL_ERR shell_err;
    char *cmd;
    OS_MSG_SIZE cmd_size;
    OS_ERR err;
    
    while(1)
    {
        cmd = OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &cmd_size, NULL, &err);
        if(err != OS_ERR_NONE)
            continue;

        Shell_Exec(cmd, NULL, NULL, &shell_err);

        rt_kprintf(FINSH_PROMPT);
        *shell_exec_lock = 0;
    }
}


void BSP_Ser_Task(void *p_arg)
{
    OS_ERR err;
    CPU_INT08U ret;
    char ch;
    OS_TICK cur_tick = OSTimeGet(&err);
    OS_TICK timeout = (50 * OSCfg_TickRate_Hz + (1000 - 1))/ 1000;// 50ms
    int shell_exec_lock = 0;
    char shell_exec_cmd[FINSH_CMD_SIZE];

    struct finsh_shell *shell = &_shell;
    memset(shell, 0, sizeof(struct finsh_shell));

    
    OSTaskCreate((OS_TCB       *)&SerShellExecTaskTCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"Serial Shell Exec Task",
                 (OS_TASK_PTR   )Ser_Shell_Exec_Task,
                 (void         *)&shell_exec_lock,
                 (OS_PRIO       )SER_SHELL_EXEC_TASK_PRIO,
                 (CPU_STK      *)&SerShellExecTaskStk[0u],
                 (CPU_STK_SIZE  )SER_SHELL_EXEC_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE  )SER_SHELL_EXEC_TASK_STK_SIZE,
                 (OS_MSG_QTY    )1u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
    

    while(1)
    {
        
        OSSemPend(&BSP_SerRxWait, timeout, OS_OPT_PEND_BLOCKING, NULL, &err);
#ifdef USE_BUF_PRINTF
        while(1)
        {
            Buf_IsEmpty(&tx_buf_ring, ret);
            if(ret == Buff_isEmpty)
                break;

            Buf_Pop(&tx_buf_ring, ch);
            lcd_put_char(ch);
//            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == 0);
            BSP_OS_SemWait(&BSP_SerTxWait, 0);
            OSSemSet(&BSP_SerTxWait, 0, &err);

            UartHandle.Instance->DR = ch;
            __HAL_UART_ENABLE_IT(&UartHandle, USART_IT_TXE);
        }   
#endif
        if(OSTimeGet(&err) - cur_tick >= 500)  //500ms
        {
            lcd_cursor_flicker();
            cur_tick = OSTimeGet(&err);
        }

        if(SerRxDisable) continue;

        Buf_IsEmpty(&rx_buf_ring, ret);
        if(ret == Buff_isEmpty)
            continue;

        if(shell_exec_lock == 1)
            continue;
        
        Buf_Pop(&rx_buf_ring, ch);

        /*
         * handle control key
         * up key  : 0x1b 0x5b 0x41
         * down key: 0x1b 0x5b 0x42
         * right key:0x1b 0x5b 0x43
         * left key: 0x1b 0x5b 0x44
         */
        if (ch == 0x1b)
        {
            shell->stat = WAIT_SPEC_KEY;
            continue;
        }
        else if (shell->stat == WAIT_SPEC_KEY)
        {
            if (ch == 0x5b)
            {
                shell->stat = WAIT_FUNC_KEY;
                continue;
            }

            shell->stat = WAIT_NORMAL;
        }
        else if (shell->stat == WAIT_FUNC_KEY)
        {
            shell->stat = WAIT_NORMAL;

            if (ch == 0x41) /* up key */
            {
#ifdef FINSH_USING_HISTORY
                /* prev history */
                if (shell->current_history > 0)
                    shell->current_history --;
                else
                {
                    shell->current_history = 0;
                    continue;
                }

                /* copy the history command */
                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       FINSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x42) /* down key */
            {
#ifdef FINSH_USING_HISTORY
                /* next history */
                if (shell->current_history < shell->history_count - 1)
                    shell->current_history ++;
                else
                {
                    /* set to the end of history */
                    if (shell->history_count != 0)
                        shell->current_history = shell->history_count - 1;
                    else
                        continue;
                }

                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       FINSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x44) /* left key */
            {
                if (shell->line_curpos)
                {
                    rt_kprintf("\b");
                    shell->line_curpos --;
                }

                continue;
            }
            else if (ch == 0x43) /* right key */
            {
                if (shell->line_curpos < shell->line_position)
                {
                    rt_kprintf("%c", shell->line[shell->line_curpos]);
                    shell->line_curpos ++;
                }

                continue;
            }

        }

        /* handle CR key */
        if (ch == '\r')
        {
//              char next;

//               if (rt_device_read(shell->device, 0, &next, 1) == 1)
//                   ch = next;
//               else ch = '\r';
        }
        /* handle tab key */
        else if (ch == '\t')
        {
            int i;
            /* move the cursor to the beginning of line */
            for (i = 0; i < shell->line_curpos; i++)
                rt_kprintf("\b");

            /* auto complete */
            shell_auto_complete(&shell->line[0]);
            /* re-calculate position */
            shell->line_curpos = shell->line_position = strlen(shell->line);

            continue;
        }
        /* handle backspace key */
        else if (ch == 0x7f || ch == 0x08)
        {
            /* note that shell->line_curpos >= 0 */
            if (shell->line_curpos == 0)
                continue;

            shell->line_position--;
            shell->line_curpos--;

            if (shell->line_position > shell->line_curpos)
            {
                int i;

                memmove(&shell->line[shell->line_curpos],
                        &shell->line[shell->line_curpos + 1],
                        shell->line_position - shell->line_curpos);
                shell->line[shell->line_position] = 0;

                rt_kprintf("\b%s  \b", &shell->line[shell->line_curpos]);

                /* move the cursor to the origin position */
                for (i = shell->line_curpos; i <= shell->line_position; i++)
                    rt_kprintf("\b");
            }
            else
            {
                rt_kprintf("\b \b");
                shell->line[shell->line_position] = 0;
            }

            continue;
        }

        /* handle end of line, break */
        if (ch == '\r' || ch == '\n')
        {
#ifdef FINSH_USING_HISTORY
            shell_push_history(shell);
#endif

#ifdef FINSH_USING_MSH
            if (msh_is_used() == RT_TRUE)
            {
                rt_kprintf("\n");
                msh_exec(shell->line, shell->line_position);
            }
            else
#endif
            {
#ifndef FINSH_USING_MSH_ONLY
                /* add ';' and run the command line */
                shell->line[shell->line_position] = '\0';

                if (shell->line_position != 0)
                {
                    /*Check if shell exec is locked*/
                    rt_kprintf("\n");
                    
                    shell_exec_lock = 1;
                    memcpy(shell_exec_cmd, shell->line, shell->line_position + 1);
                    OSTaskQPost(&SerShellExecTaskTCB, shell_exec_cmd, shell->line_position + 1, OS_OPT_POST_FIFO, &err);
                    
                    memset(shell->line, 0, sizeof(shell->line));
                    shell->line_curpos = shell->line_position = 0;
                    continue;
                }
                else rt_kprintf("\n");
#endif
            }

            rt_kprintf(FINSH_PROMPT);
            memset(shell->line, 0, sizeof(shell->line));
            shell->line_curpos = shell->line_position = 0;
            continue;//break;
        }

        /* it's a large line, discard it */
        if (shell->line_position >= FINSH_CMD_SIZE)
            shell->line_position = 0;

        /* normal character */
        if (shell->line_curpos < shell->line_position)
        {
            int i;

            memmove(&shell->line[shell->line_curpos + 1],
                    &shell->line[shell->line_curpos],
                    shell->line_position - shell->line_curpos);
            shell->line[shell->line_curpos] = ch;
            if (1/*shell->echo_mode*/)
                rt_kprintf("%s", &shell->line[shell->line_curpos]);

            /* move the cursor to new position */
            for (i = shell->line_curpos; i < shell->line_position; i++)
                rt_kprintf("\b");
        }
        else
        {
            shell->line[shell->line_position] = ch;
            rt_kprintf("%c", ch);
        }

        ch = 0;
        shell->line_position ++;
        shell->line_curpos++;
        if (shell->line_position >= 80)
        {
            /* clear command line */
            shell->line_position = 0;
            shell->line_curpos = 0;
        }

    }
}





/*
*********************************************************************************************************
*                                          BSP_Ser_Init()
*
* Description : Initialize a serial port for communication.
*
* Argument(s) : baud_rate           The desire RS232 baud rate.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_Init ()
{
    GPIO_InitTypeDef        GPIO_InitStruct;
    OS_ERR err;


    lcd_terminal_init(0,0,800,480);

    SerRxDisable=0;
    
    Buf_init(&rx_buf_ring,rx_buffer,sizeof(rx_buffer));


    /* ------------------ INIT OS OBJECTS ----------------- */
    BSP_OS_SemCreate(&BSP_SerTxWait,   1, "Serial Tx Wait");
    BSP_OS_SemCreate(&BSP_SerRxWait,   0, "Serial Rx Wait");

    /* ----------------- INIT USART STRUCT ---------------- */
    UartHandle.Init.BaudRate   = BSP_SER_COMM_BAUDRATE;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

#ifdef USE_USART3
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
    UartHandle.Instance        = USART3;
    if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
    {
        while(1);
    }
    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        while(1);
    }
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);


    BSP_IntVectSet(BSP_INT_ID_USART3, BSP_Ser_ISR_Handler);
    BSP_IntEn(BSP_INT_ID_USART3);
#endif

#ifdef USE_USART6
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
    UartHandle.Instance        = USART6;
    if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
    {
        while(1);
    }
    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        while(1);
    }
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);


    BSP_IntVectSet(BSP_INT_ID_USART6, BSP_Ser_ISR_Handler);
    BSP_IntEn(BSP_INT_ID_USART6);
#endif


#ifdef USE_BUF_PRINTF
    Buf_init(&tx_buf_ring,tx_buffer,sizeof(tx_buffer));
#endif

    OSTaskCreate((OS_TCB       *)&BspSerTaskTCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"BSP Serial Task",
                 (OS_TASK_PTR   )BSP_Ser_Task,
                 (void         *)0u,
                 (OS_PRIO       )BSP_SER_TASK_PRIO,
                 (CPU_STK      *)&BspSerTaskStk[0u],
                 (CPU_STK_SIZE  )BSP_SER_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE  )BSP_SER_TASK_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

}









#if 1
#pragma import(__use_no_semihosting)
// struct __FILE
// {
//     int handle;
//     /* Whatever you require here. If the only file you are using is */
//     /* standard output using printf() for debugging, no file handling */
//     /* is required. */
// };
/* FILE is typedef’ d in stdio.h. */
//FILE __stdout;

struct __FILE
{
    int handle;
} ;

FILE __stdout;
FILE __stdin;
FILE __stderr;

void _sys_exit(int x)
{
    x = x;
}


// int fclose(FILE* f) {
//   return (0);
// }


// int fseek (FILE *f, long nPos, int nMode)  {
//   return (0);
// }


int fflush (FILE *f)
{
    return (0);
}

// int ferror(FILE *f) {
//   /* Your implementation of ferror */
//   return (EOF);
// }

void _ttywrch(int ch)
{
//  fputc(ch, NULL);
}


int fputc(int ch, FILE *f)
{
#ifdef USE_BUF_PRINTF
    CPU_INT08U ret;
    CPU_SR cpu_sr;

    CPU_CRITICAL_ENTER();

    if(ch == '\n')
    {
        Buf_IsFull(&tx_buf_ring, ret);
        if(ret == Buff_notFull)
            Buf_Push(&tx_buf_ring, '\r');
    }

    Buf_IsFull(&tx_buf_ring, ret);
    if(ret == Buff_notFull)
    {
        Buf_Push(&tx_buf_ring, (ch&0xff));

        CPU_CRITICAL_EXIT();
        return ch;
    }
    CPU_CRITICAL_EXIT();
#else
    if(ch == '\n')
    {
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TXE) == 0);
        UartHandle.Instance->DR = '\r';
        while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TC) == 0);
    }

    while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TXE) == 0);
    UartHandle.Instance->DR = ch & 0XFF;
    while(__HAL_UART_GET_FLAG(&UartHandle,USART_FLAG_TC) == 0);

    lcd_put_char(ch);
#endif

    return ch;
}
#endif



#if defined(USE_USART3) && defined(USE_USART6)
#error "Multi USART is defined"
#endif

#if !defined(USE_USART3) && !defined(USE_USART6)
#error "USART is not defined"
#endif
