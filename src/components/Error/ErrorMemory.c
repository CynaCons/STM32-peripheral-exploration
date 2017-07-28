/**
 ******************************************************************************
 * @file    ErrorMemory.c
 * @author  Constantin CHABIRAND
 * @version V0.1
 * @brief   Source file for the ErrorMemory component
 *
 ******************************************************************************
 */

/**********************************************************************
 *
 * Includes, Defines and Globals
 *
 **********************************************************************/

#include "stm32f4xx.h"
#include <string.h>
#include "ErrorMemory.h"

#define MAX_SIZE_ENTRY 128
#define MAX_NUMBER_ENTRY 8

#define LED_OFF GPIO_PIN_RESET
#define LED_ON GPIO_PIN_SET

#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_14

/**********************************************************************
 *
 * Static variables
 *
 **********************************************************************/
static uint8_t entry_table[MAX_NUMBER_ENTRY][MAX_SIZE_ENTRY] = {0};
static uint8_t entry_index = 0;
static uint8_t led_status = LED_OFF;



/**********************************************************************
 *
 * Global Functions
 *
 **********************************************************************/
void ErrorMemory_AddEntry(const char *file_name, int line)
{
	uint8_t data_len = strlen(file_name) + sizeof(line);

	/* Truncate the data if it's length is greater than the allowed length */
	if(data_len > MAX_SIZE_ENTRY){
		data_len = MAX_SIZE_ENTRY - 1;
	}

	snprintf((char *)entry_table[entry_index], data_len, "%s,%d",file_name, line);
	entry_table[entry_index][MAX_SIZE_ENTRY] = '\0';
	entry_index++;

	if (GPIO_PIN_RESET == led_status){
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_ON);
	}
}


void ErrorMemory_SetupLED(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}
