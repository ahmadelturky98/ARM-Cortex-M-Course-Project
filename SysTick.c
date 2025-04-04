#include "SysTick.h"

static void (*g_SysTickCallBackPtr)(void) = NULL_PTR;

/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Time in milliseconds for SysTick
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to initialize the SysTick timer with the specified
*              time in milliseconds and enable interrupts.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0; // Disable SysTick during setup
    uint32 reload_value = (16000 * a_TimeInMilliSeconds) - 1;
    SYSTICK_RELOAD_REG = reload_value;
    SYSTICK_CURRENT_REG = 0; // Clear current value
    SYSTICK_CTRL_REG = 0x07; // Enable SysTick with core clock and interrupt
}

/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to start or resume the SysTick timer.
**********************************************************************/
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |= 0x01; // Enable SysTick timer
}

/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the SysTick timer.
**********************************************************************/
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG &= ~(0x01); // Disable SysTick
}

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Ptr2Func - Pointer to the callback function
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to set the callback function to be executed
*              in the SysTick interrupt handler.
**********************************************************************/
void SysTick_SetCallBack(void (*Ptr2Func)(void))
{
    g_SysTickCallBackPtr = Ptr2Func;
}

/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Asynchronous
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Interrupt handler for the SysTick timer to execute the
*              callback function if set.
**********************************************************************/
void SysTick_Handler(void)
{
    if (g_SysTickCallBackPtr != NULL_PTR)
    {
        (*g_SysTickCallBackPtr)();
    }
}

/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): delay_ms - Time in milliseconds for busy-wait
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to start the SysTick timer in busy-wait mode
*              for the specified time in milliseconds.
**********************************************************************/
void SysTick_StartBusyWait(uint32_t delay_ms)
{
    /* Disable SysTick */
    SYSTICK_CTRL_REG = 0;

    /* Load the reload value */
    SYSTICK_RELOAD_REG = (16000 * delay_ms) - 1; /* Assuming 16 MHz clock */

    /* Clear the current value */
    SYSTICK_CURRENT_REG = 0;

    /* Enable SysTick with system clock */
    SYSTICK_CTRL_REG = 0x05;

    /* Wait until the COUNT flag is set */
    while ((SYSTICK_CTRL_REG & 0x10000) == 0);
}

/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (input): None
* Parameters (out): None
* Return value: None
* Description: Function to de-initialize the SysTick timer and reset
*              its registers to default values.
**********************************************************************/
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0;       // Disable SysTick
    SYSTICK_RELOAD_REG = 0;     // Clear reload value
    SYSTICK_CURRENT_REG = 0;    // Clear current value
}
