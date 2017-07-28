/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f4xx_it.h"

#include "components/dht22/dht22.h"
#include "stm32f4xx_hal_uart.h"
#include "components/Uart/UartRx.h"

extern DHT22_HandleTypeDef dht;
extern UART_HandleTypeDef huart2;

extern UartRx_TypeDef UartRx_Esp;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void TIM3_IRQHandler(void){
	DHT22_InterruptHandler(&dht);

	  /* Capture compare 1 event */
	  if(__HAL_TIM_GET_FLAG(&dht.timHandle, TIM_FLAG_CC1) != RESET)
	  {
	    if(__HAL_TIM_GET_IT_SOURCE(&dht.timHandle, TIM_IT_CC1) !=RESET)
	    {
	      {
	        __HAL_TIM_CLEAR_IT(&dht.timHandle, TIM_IT_CC1);
	      }
	    }
	  }
}


void USART2_IRQHandler(void)
{
	 HAL_UART_IRQHandler(&huart2);
	 UartRx_Esp.interrupt_flag = 1;
	 UartRx_Esp.head++;
	 UartRx_Esp.last_update = HAL_GetTick();
}


/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}
