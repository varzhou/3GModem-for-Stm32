/**
  ******************************************************************************
  * @file    usb_bsp.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   This file implements the board support package for the USB host library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "bsp.h"
#include "usb_conf.h"
#include "usbh_linux.h"
#include "usb_hcd_int.h"
#include "usb_bsp.h"
#include "stm32f4xx_hal.h"

/** @addtogroup USBH_USER
* @{
*/

/** @defgroup USB_BSP
  * @brief This file is responsible to offer board support package
  * @{
  */

/** @defgroup USB_BSP_Private_Defines
  * @{
  */


#ifdef USE_USB_OTG_FS
#define HOST_POWERSW_PORT_RCC_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define HOST_POWERSW_PORT                GPIOB
#define HOST_POWERSW_VBUS                GPIO_PIN_2
#define HOST_POWERSW_ACTIVE              GPIO_PIN_SET
#define HOST_POWERSW_INACTIVE            GPIO_PIN_RESET
#endif


/**
  * @}
  */


/** @defgroup USB_BSP_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */



/** @defgroup USB_BSP_Private_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_BSP_Private_Variables
  * @{
  */
ErrorStatus HSEStartUpStatus;

/**
  * @}
  */

/** @defgroup USBH_BSP_Private_FunctionPrototypes
  * @{
  */


/**
  * @}
  */

/** @defgroup USB_BSP_Private_Functions
  * @{
  */

/**
  * @brief  USB_OTG_BSP_Init
  *         Initilizes BSP configurations
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_Init(int coreID)
{
    GPIO_InitTypeDef GPIO_InitStruct;

#ifdef USB_OTG_FS_CORE    
    if(coreID == USB_OTG_FS_CORE_ID)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* Configure DM DP Pins */
        GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

        /* Enable USB FS Clocks */ 
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    }
#endif

#ifdef USB_OTG_HS_CORE       
    if(coreID == USB_OTG_HS_CORE_ID) 
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /* Configure DM DP Pins */
        GPIO_InitStruct.Pin = (GPIO_PIN_14 | GPIO_PIN_15);
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 

        /* Enable USB HS Clocks */ 
        __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    }
#endif
    /* Intialize Timer for delay function */
//   USB_OTG_BSP_TimeInit();
}

void OTG_ISR_Handler(void *p_obj)
{
    USBH_OTG_ISR_Handler(p_obj);
}

/**
  * @brief  USB_OTG_BSP_EnableInterrupt
  *         Configures USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_EnableInterrupt(void *otg_handle, int coreID)
{

#ifdef USB_OTG_FS_CORE     
    if(coreID == USB_OTG_FS_CORE_ID)
    {
        BSP_IntVectSetEx(BSP_INT_ID_OTG_FS,OTG_ISR_Handler, otg_handle);
        BSP_IntEn(BSP_INT_ID_OTG_FS);
    }
#endif
    
#ifdef USB_OTG_HS_CORE  
    if(coreID == USB_OTG_HS_CORE_ID)
    {
        BSP_IntVectSetEx(BSP_INT_ID_OTG_HS,OTG_ISR_Handler, otg_handle);
        BSP_IntEn(BSP_INT_ID_OTG_HS);
    }
#endif
}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */

void USB_OTG_BSP_DriveVBUS(uint8_t state, int coreID)
{
    /*
    On-chip 5 V VBUS generation is not supported. For this reason, a charge pump
    or, if 5 V are available on the application board, a basic power switch, must
    be added externally to drive the 5 V VBUS line. The external charge pump can
    be driven by any GPIO output. When the application decides to power on VBUS
    using the chosen GPIO, it must also set the port power bit in the host port
    control and status register (PPWR bit in OTG_FS_HPRT).

    Bit 12 PPWR: Port power
    The application uses this field to control power to this port, and the core
    clears this bit on an overcurrent condition.
    */
#ifdef USB_OTG_FS_CORE 
    if(coreID == USB_OTG_FS_CORE_ID)
    {
        if (0 == state)
        {
            /* DISABLE is needed on output of the Power Switch */
            HAL_GPIO_WritePin(HOST_POWERSW_PORT, HOST_POWERSW_VBUS, HOST_POWERSW_INACTIVE);
        }
        else
        {
            /*ENABLE the Power Switch by driving the Enable LOW */
            HAL_GPIO_WritePin(HOST_POWERSW_PORT, HOST_POWERSW_VBUS, HOST_POWERSW_ACTIVE);
        }
    }
#endif    
}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  None
  * @retval None
  */

void  USB_OTG_BSP_ConfigVBUS(int coreID)
{
#ifdef USB_OTG_FS_CORE     
    if(coreID == USB_OTG_FS_CORE_ID)
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        /* Configure POWER_SWITCH IO pin */
        HOST_POWERSW_PORT_RCC_ENABLE();
        GPIO_InitStruct.Pin = HOST_POWERSW_VBUS;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(HOST_POWERSW_PORT, &GPIO_InitStruct); 


        /* By Default, DISABLE is needed on output of the Power Switch */
        HAL_GPIO_WritePin(HOST_POWERSW_PORT, HOST_POWERSW_VBUS, HOST_POWERSW_INACTIVE);

        USB_OTG_BSP_mDelay(200);   /* Delay is need for stabilising the Vbus Low
         in Reset Condition, when Vbus=1 and Reset-button is pressed by user */

    }
#endif    
}



void USB_OTG_BSP_uDelay (const uint32_t usec)
{


    __IO uint32_t count = 0;
    const uint32_t utime = (120 * usec / 7);
    do
    {
        if ( ++count > utime )
        {
            return ;
        }
    }
    while (1);


}

#include "delay.h"

/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void USB_OTG_BSP_mDelay (const uint32_t msec)
{
    delay_ms(msec);
//    BSP_OS_TimeDlyMs(msec);
}



/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
