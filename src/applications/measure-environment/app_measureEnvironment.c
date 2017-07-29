/**
 ******************************************************************************
 * @file    main.c
 * @author  Constantin CHABIRAND
 * @version V0.1
 * @brief   Core file for the application
 *
 * DONE Make a macro for UART Sending.
 * DONE Modularize all peripheral components
 * DODONEE Clean all the ESP Code
 * DONE Implement the error checking for all function related to Init or ESP.
 * DONE Make an ErrorMemory module.
 * TODO Clarify the GPIO configuration for each component
 * TODO Beautify and comment the header files.
 * TODO Make the UartTx use TxComplete interrupt to prevent errors and overflow
 *
 *
 ******************************************************************************
 */

#include <applications/measure-environment/app_measureEnvironment.h>
#include <applications/measure-environment/stm32f4xx_it.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "components/dht22/dht22.h"
#include "components/util.h"
#include "components/Uart/UartRx.h"
#include "components/Uart/UartTx.h"
#include "components/Error/ErrorMemory.h"
#include "components/ESP8266/ESP8266.h"
#include "components/LightSensor/LightSensor.h"

#include <string.h>

void SystemClock_Config(void);
void HAL_MspInit(void);


extern DHT22_HandleTypeDef dht;
UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc1;


extern UartRx_TypeDef UartRx_Esp;


int app_measureEnvironment(void)
{
	uint32_t light_value;

	ErrorMemory_SetupLED();

	if (FALSE == DHT22_Setup())
		EM_ADD();

	if (FALSE == UartRx_Setup_Esp())
		EM_ADD();

	if (FALSE == ESP_Setup())
		EM_ADD();

	if (FALSE == LightSensor_Setup())
		EM_ADD();

	while (1){
		DHT22_ReadData(&dht);
		light_value = LightSensor_GetValue();
		ESP_SetRequestData("HTTP/1.1 200 OK\r\n\r\nTemperature: %.1f\nHumidity: %.1f\nLight: %.1lu",dht.temp, dht.hum, light_value);

		/* Check the buffer for a GET request */
		if ((HAL_GetTick() - UartRx_Esp.last_update) > 500) {
			if (TRUE == UartRx_Find(&UartRx_Esp, "GET")) {
				/* Clean UartRx first */
				UartRx_Reset(&UartRx_Esp);
				ESP_HandleRequest_GET();
			}
		}
	}

	for(;;);

}
