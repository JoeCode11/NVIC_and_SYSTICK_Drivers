/*
 * systick.c
 *
 *  Created on: 7 Mar 2025
 *      Author: 79254
 */


#include "systick.h"
#include "tm4c123gh6pm_registers.h"

#include <stdint.h>
#include <stddef.h>

#define SYSTICK_FLAG 1<<16
#define CTRL_BITS 0x7
#define TICKS 15999999

void (*Ptr2Func) (void) = NULL;


/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): a_TimeInMilliSeconds - Time for systick to countdown in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Function to initialize Systick
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;
    SYSTICK_RELOAD_REG  = ((a_TimeInMilliSeconds * TICKS)/ 1000);
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_CTRL_REG |= 0x7;
}


/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): a_TimeInMilliSeconds - Time for systick to countdown in milliseconds, we pass this parameter to init function within this function
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Function to detect successful countdown using polling. Systick is stopped at the end
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    SysTick_Init(a_TimeInMilliSeconds);
    SYSTICK_CTRL_REG = (SYSTICK_CTRL_REG & ~(0x2));
    while(!(SYSTICK_CTRL_REG & SYSTICK_FLAG)){ //polling, wait for flag to be set in the ctrl register, notifying about countdown
    }
    SYSTICK_CTRL_REG = (SYSTICK_CTRL_REG & ~(CTRL_BITS)); //exit and stop the timer at the end
    return;
}


/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Asynchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: SysTick interrupt handler that executes the function
*              pointed to by Ptr2Func if it is not NULL
**********************************************************************/
void SysTick_Handler(void){
    if (Ptr2Func!= NULL) Ptr2Func();
}

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): FuncPtr - points to the callback function address that is passed to this function in the main program
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: To set the Ptr2Func that the handler uses, so that the handler calls the callback function
**********************************************************************/

void SysTick_SetCallBack( void (*FuncPtr)(void)){
    Ptr2Func = FuncPtr;
}

//void Callback_Func(void){
//    GPIO_PORTF_AMSEL_REG &= ~(1<<1);      /* Disable Analog on PF1 */
//    GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
//    GPIO_PORTF_DIR_REG   |= (1<<1);       /* Configure PF1 as output pin */
//    GPIO_PORTF_AFSEL_REG &= ~(1<<1);      /* Disable alternative function on PF1 */
//    GPIO_PORTF_DEN_REG   |= (1<<1);       /* Enable Digital I/O on PF1 */
//    GPIO_PORTF_DATA_REG  = 0x1;           /* Enable the red LED when the handler occurs using this callback function */
//}


/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Stops systick
**********************************************************************/

void SysTick_Stop(void){
    SYSTICK_CTRL_REG = (SYSTICK_CTRL_REG & ~(1)) ;
}


/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Starts systick
**********************************************************************/

void SysTick_Start(void){
    SYSTICK_CTRL_REG |= 0x1;
}
/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: De-initialize systick
**********************************************************************/

void SysTick_DeInit(void){
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_RELOAD_REG = 0;
}



/*end of code



*/







