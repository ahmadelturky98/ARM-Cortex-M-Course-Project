/* NVIC.h */
#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

#define Enable_Exceptions()    __asm(" CPSIE I ")
#define Disable_Exceptions()   __asm(" CPSID I ")
#define Enable_Faults()        __asm(" CPSIE F ")
#define Disable_Faults()       __asm(" CPSID F ")

typedef uint8_t NVIC_IRQType;
typedef uint8_t NVIC_IRQPriorityType;

typedef enum {
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
} NVIC_ExceptionType;

typedef uint8_t NVIC_ExceptionPriorityType;

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);
void NVIC_EnableException(uint8_t exception_type);
void NVIC_DisableException(uint8_t exception_type);

#endif /* NVIC_H_ */
