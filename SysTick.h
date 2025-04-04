/* SysTick.h */
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
#include <stdint.h>

/* Function prototypes */
void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_Start(void);
void SysTick_Stop(void);
void SysTick_SetCallBack(void (*Ptr2Func)(void));
void SysTick_StartBusyWait(uint32_t delay_ms);
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
