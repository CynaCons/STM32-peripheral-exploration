/**
 ******************************************************************************
 * @file    UartRx.c
 * @author  Constantin CHABIRAND
 * @version V0.1
 * @brief   Source file for the UartReception component
 *
 ******************************************************************************
 */

/**********************************************************************
 *
 * Includes and Globals
 *
 **********************************************************************/
#include "UartRx.h"
#include "components/Error/ErrorMemory.h"

extern UART_HandleTypeDef huart2;


/**********************************************************************
 *
 * Global instances
 *
 **********************************************************************/
UartRx_TypeDef UartRx_Esp = {0};


/**********************************************************************
 *
 * HAL Callback Functions
 *
 **********************************************************************/
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		HAL_UART_Receive_IT(&huart2, UartRx_Esp.buffer, UART_RX_BUFFER_SIZE);
	}
}


/**********************************************************************
 *
 * Global Functions
 *
 **********************************************************************/
void UartRx_Reset (UartRx_TypeDef *this)
{
	if (HAL_OK != HAL_UART_AbortReceive_IT(&huart2))
		EM_ADD();
	this->head = 0;
	this->base = 0;
	this->last_update = 0;
	this->interrupt_flag = 0;
	memset(this->buffer, 0, sizeof(this->buffer));
	if (HAL_OK!=HAL_UART_Receive_IT(&huart2, UartRx_Esp.buffer, UART_RX_BUFFER_SIZE))
		EM_ADD();
}


bool UartRx_Find (UartRx_TypeDef *this, const char * needle)
{
	uint8_t retval = FALSE;
	if( NULL != strstr((const char *)this->buffer, needle) ){
		retval = TRUE;
	}
	return retval;
}


bool UartRx_BlockingFind (UartRx_TypeDef *this, const char *needle, uint32_t tick_timeout)
{
	bool retval = FALSE;
	uint32_t start_tick = HAL_GetTick();
	while( (HAL_GetTick() - start_tick) < tick_timeout ){
		if( NULL != strstr((const char *)this->buffer, needle) ){
			retval = TRUE;
		}
	}
	return retval;
}


bool UartRx_Setup_Esp(void)
{

	bool retval = TRUE;

	/* GPIO Init */
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_Init_st;
	GPIO_Init_st.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_Init_st.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_st.Pull = GPIO_PULLUP;
	GPIO_Init_st.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init_st.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_st);

	/**
	 * PIN description:
	 * 		 PA2     ------> USART2_TX
	 * 		 PA3     ------> USART2_RX
	 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK){
		retval = FALSE;
	}
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	if ( HAL_UART_Receive_IT(&huart2, UartRx_Esp.buffer, UART_RX_BUFFER_SIZE) != HAL_OK ){
		retval = FALSE;
	}

	return retval;
}

