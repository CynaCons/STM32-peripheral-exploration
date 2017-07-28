/**
 ******************************************************************************
 * @file    LightSensor.c
 * @author  Constantin CHABIRAND
 * @version V0.1
 * @brief   Source file for the LightSensor component
 *
 ******************************************************************************
 */

/**********************************************************************
 *
 * Includes, Defines and Globals
 *
 **********************************************************************/
#include "LightSensor.h"

extern ADC_HandleTypeDef hadc1;

/**********************************************************************
 *
 * Global Functions
 *
 **********************************************************************/
bool LightSensor_Setup(void)
{
	bool retval = TRUE;

	/**
	 *  Hardware init
	 */
	GPIO_InitTypeDef GPIO_InitStruct;
	/* Peripheral clock enable */
	__HAL_RCC_ADC1_CLK_ENABLE();

	/**ADC1 GPIO Configuration
				    PA0-WKUP     ------> ADC1_IN0
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/**
	 * Peripheral Initialization
	 */
	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		retval = FALSE;
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		retval = FALSE;
	}

	return retval;
}


uint32_t LightSensor_GetValue(void)
{
	uint32_t light_value = 0;
	HAL_ADC_Start(&hadc1);
	while (HAL_ADC_PollForConversion(&hadc1, 1000) != HAL_OK);
	light_value = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return light_value;
}
