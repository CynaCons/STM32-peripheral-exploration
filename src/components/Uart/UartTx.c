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
#include "UartTx.h"
#include <stdarg.h>
#include <string.h>
#include "components/Error/ErrorMemory.h"

extern UART_HandleTypeDef huart2;


/**********************************************************************
 *
 * Global instances
 *
 **********************************************************************/
UartTx_TypeDef UartTx_Esp;


bool UartTx_Send(UartTx_TypeDef *this, const char *format, ...)
{
	bool retval = TRUE;
	va_list list;
	va_start(list, format);

    int check_value = vsnprintf((char *)this->buffer, UART_TX_BUFFER_SIZE, format, list);
    if (check_value < 0 ){ /* The formatted string is too big and got truncated */
    	ErrorMemory_AddEntry(__FILE__, __LINE__);
    	memset(this->buffer, 0, UART_TX_BUFFER_SIZE);
    	retval = FALSE;
    }else{
    	this->head = check_value;
    }
	va_end(list);

	/* Check that the length of the data is equal to the head value */
	if (this->head != strlen((const char *)this->buffer))
		retval = FALSE;

	if (TRUE == retval){
		HAL_UART_Transmit(&huart2, this->buffer, this->head, UART_TX_TIMEOUT);
	}

	return retval;
}
