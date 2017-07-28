/*
 * UartTx.h
 *
 *  Created on: Jun 7, 2017
 *      Author: cynako
 */

#ifndef COMPONENTS_UART_UARTTX_H_
#define COMPONENTS_UART_UARTTX_H_

#include "components/util.h"

#define UART_TX_BUFFER_SIZE 1024

#define UART_TX_TIMEOUT 100

typedef struct UartTx_TypeDef UartTx_TypeDef;
struct UartTx_TypeDef {
	uint16_t head;
	uint8_t buffer[UART_TX_BUFFER_SIZE];
};

bool UartTx_Send(UartTx_TypeDef *this, const char *format, ...);

#endif /* COMPONENTS_UART_UARTTX_H_ */
