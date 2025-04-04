#include "NVIC.h"

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    IRQ_Num - Interrupt Request (IRQ) number from the vector table.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Enables the interrupt request for a specific IRQ by setting the
*    corresponding bit in the NVIC Enable register. This function
*    supports IRQ numbers less than 32.
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < 32)
    {
        NVIC_EN0_REG |= (1 << IRQ_Num);
    }
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    IRQ_Num - Interrupt Request (IRQ) number from the vector table.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Disables the interrupt request for a specific IRQ by clearing the
*    corresponding bit in the NVIC Enable register. This function
*    supports IRQ numbers less than 32.
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < 32)
    {
        NVIC_EN0_REG &= ~(1 << IRQ_Num);
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    IRQ_Num - Interrupt Request (IRQ) number from the vector table.
*    IRQ_Priority - Priority value to be assigned to the IRQ.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Sets the priority for a specific IRQ by updating the corresponding
*    priority register. The function calculates the register and field
*    position based on the IRQ number.
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    volatile uint32 *priority_reg = &NVIC_PRI0_REG + (IRQ_Num / 4);
    uint8_t priority_field_pos = (IRQ_Num % 4) * 8 + 5;
    *priority_reg = (*priority_reg & ~(0x07 << priority_field_pos)) | (IRQ_Priority << priority_field_pos);
}

/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    exception_type - Exception type to be configured.
*    priority - Priority value to be assigned to the exception.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Sets the priority for a specific system or fault exception by
*    updating the corresponding priority register. The function handles
*    various exception types including Bus Fault and SysTick.
**********************************************************************/
void NVIC_SetPriorityException(uint8_t exception_type, uint8_t priority)
{
    switch (exception_type)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (priority << MEM_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (priority << BUS_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (priority << USAGE_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SVC_TYPE:
            NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (priority << SVC_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_DEBUG_MONITOR_TYPE:
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_PEND_SV_TYPE:
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (priority << PENDSV_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SYSTICK_TYPE:
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (priority << SYSTICK_PRIORITY_BITS_POS);
            break;
        default:
            break;
    }
}

/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    exception_type - Exception type to be enabled.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Enables a specific system or fault exception by setting the
*    corresponding bit in the NVIC System Handler Control register.
**********************************************************************/
void NVIC_EnableException(uint8_t exception_type)
{
    switch (exception_type)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):
*    exception_type - Exception type to be disabled.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*    Disables a specific system or fault exception by clearing the
*    corresponding bit in the NVIC System Handler Control register.
**********************************************************************/
void NVIC_DisableException(uint8_t exception_type)
{
    switch (exception_type)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            break;
    }
}
