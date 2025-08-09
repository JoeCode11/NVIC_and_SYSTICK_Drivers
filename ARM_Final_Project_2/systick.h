/*
 * systick.h
 *
 *  Created on: 7 Mar 2025
 *      Author: 79254
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"

void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack( void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);


#endif /* SYSTICK_H_ */
