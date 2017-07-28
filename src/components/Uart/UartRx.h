/*
 * UartRx.h
 *
 *  Created on: Jun 6, 2017
 *      Author: cynako
 */

#ifndef UARTRX_H_
#define UARTRX_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>
#include "components/util.h"

#define UART_RX_BUFFER_SIZE 1024


typedef struct UartRx_TypeDef UartRx_TypeDef;
struct UartRx_TypeDef {
	uint16_t head;
	uint16_t base;
	uint32_t last_update;
	uint8_t interrupt_flag;
	uint8_t buffer[UART_RX_BUFFER_SIZE];
};

void UartRx_Reset(UartRx_TypeDef *this);
bool UartRx_Find(UartRx_TypeDef *this, const char *needle);
bool UartRx_BlockingFind(UartRx_TypeDef *this, const char *needle, uint32_t tick_timeout);
bool UartRx_Setup_Esp(void);

#endif /* UARTRX_H_ */
