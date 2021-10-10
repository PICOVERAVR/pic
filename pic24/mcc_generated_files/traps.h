#include <stdint.h>
#pragma once

typedef enum  {
    /* ----- Traps ----- */
    TRAPS_OSC_FAIL = 0, /** Oscillator Fail Trap vector */
    TRAPS_STACK_ERR = 1, /** Stack Error Trap Vector */
    TRAPS_ADDRESS_ERR = 2, /** Address error Trap vector */
    TRAPS_MATH_ERR = 3, /** Math Error Trap vector */
    TRAPS_DMAC_ERR = 4, /** DMAC Error Trap vector */
    TRAPS_HARD_ERR = 7, /** Generic Hard Trap vector */
    TRAPS_DAE_ERR = 9, /** Generic Soft Trap vector */
    TRAPS_DOOVR_ERR = 10, /** Generic Soft Trap vector */
} TRAPS_ERROR_CODE;

void __attribute__((naked, noreturn, weak)) TRAPS_halt_on_error(uint16_t code);