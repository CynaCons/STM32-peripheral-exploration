/*
 * ErrorMemory.h
 *
 *  Created on: Jun 7, 2017
 *      Author: cynako
 */

#ifndef COMPONENTS_ERROR_ERRORMEMORY_H_
#define COMPONENTS_ERROR_ERRORMEMORY_H_

#define EM_ADD() ErrorMemory_AddEntry(__FILE__, __LINE__)

void ErrorMemory_AddEntry(const char * file_name, int line);
void ErrorMemory_SetupLED(void);

#endif /* COMPONENTS_ERROR_ERRORMEMORY_H_ */
