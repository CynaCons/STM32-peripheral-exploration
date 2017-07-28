/**
 ******************************************************************************
 * @file    ESP8266.c
 * @author  Constantin CHABIRAND
 * @version V0.1
 * @brief   Source file for the ESP8266 component
 *
 ******************************************************************************
 */

/**********************************************************************
 *
 * Includes, Defines and Globals
 *
 **********************************************************************/
#include "ESP8266.h"
#include "components/Uart/UartRx.h"
#include "components/Uart/UartTx.h"
#include "components/Error/ErrorMemory.h"
#include <string.h>
#include <stdarg.h>

extern UartRx_TypeDef UartRx_Esp;
extern UartTx_TypeDef UartTx_Esp;


/**********************************************************************
 *
 * Static variables
 *
 **********************************************************************/
static uint8_t data_buffer[UART_TX_BUFFER_SIZE];


/**********************************************************************
 *
 * Global Functions
 *
 **********************************************************************/
bool ESP_HandleRequest_GET(void)
{
	bool retval = FALSE;

	/* Sent AT+CIPSEND=0,data length to start the response process */
	if (FALSE == UartTx_Send(&UartTx_Esp, "AT+CIPSEND=0,%d\r\n", strlen(data_buffer)))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "OK", 2000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);


	/* Send the content of the web page */
	if (FALSE == UartTx_Send(&UartTx_Esp, "%s", data_buffer))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "OK", 2000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);


	/* Close the connection and send the data */
	if (FALSE == UartTx_Send(&UartTx_Esp, "AT+CIPCLOSE=0\r\n"))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "OK", 2000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);


	return retval;
}


bool ESP_Setup(void)
{
	bool retval = TRUE;

	/* Send AT+CIPMUX=1 to enable multiple connections */
	if (FALSE == UartTx_Send(&UartTx_Esp, "AT+RST\r\n"))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "ready", 5000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);

	/* Send AT+CIPMUX=1 to enable multiple connections */
	if (FALSE == UartTx_Send(&UartTx_Esp, "AT+CIPMUX=1\r\n"))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "OK", 2000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);


	/* Send AT+CIPSERVER=1,80 to start the web-server */
	if (FALSE == UartTx_Send(&UartTx_Esp, "AT+CIPSERVER=1,80\r\n"))
		retval = FALSE;
	if (FALSE == UartRx_BlockingFind(&UartRx_Esp, "OK", 2000))
		retval = FALSE;
	UartRx_Reset(&UartRx_Esp);


	return retval;
}


bool ESP_SetRequestData(const char *format, ...)
{
	bool retval = TRUE;

	va_list list;

	va_start(list, format);
	int check_value = vsnprintf((char *)data_buffer, UART_TX_BUFFER_SIZE, format, list);
	va_end(list);

	if (check_value < 0){
		EM_ADD();
		memset(data_buffer, 0, sizeof(data_buffer));
		retval = FALSE;
	}

	return retval;
}
