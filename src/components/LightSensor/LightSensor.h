/*
 * LightSensor.h
 *
 *  Created on: Jun 7, 2017
 *      Author: cynako
 */

#ifndef COMPONENTS_LIGHTSENSOR_LIGHTSENSOR_H_
#define COMPONENTS_LIGHTSENSOR_LIGHTSENSOR_H_
#include "stm32f4xx.h"
#include "stm32f4xx_hal_adc.h"
#include "components/util.h"


bool LightSensor_Setup(void);
uint32_t LightSensor_GetValue(void);


#endif /* COMPONENTS_LIGHTSENSOR_LIGHTSENSOR_H_ */
