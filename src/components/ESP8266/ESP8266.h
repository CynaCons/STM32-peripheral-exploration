/*
 * ESP8266.h
 *
 *  Created on: Jun 7, 2017
 *      Author: cynako
 */

#ifndef COMPONENTS_ESP8266_ESP8266_H_
#define COMPONENTS_ESP8266_ESP8266_H_

#include "components/util.h"

bool ESP_HandleRequest_GET(void);
bool ESP_Setup(void);
bool ESP_SetRequestData(const char *format, ...);

#endif /* COMPONENTS_ESP8266_ESP8266_H_ */
