#ifdef DEBUG

#include "debug.h"

#include "dtekv_lib.h"

volatile unsigned int   mcycle,         // Elapsed cycles
                        minstret,       // Instructions retired
                        mhpmcounter3,   // Memory instruction retired
                        mhpmcounter4,   // Instruction I-cache misses
                        mhpmcounter5,   // Memory D-cache misses
                        mhpmcounter6,   // Stalls due to I-cache misses
                        mhpmcounter7,   // Stalls due to D-cache misses
                        mhpmcounter8,   // Stalls due to data hazards not forwarded
                        mhpmcounter9;   // Stalls due to expensive ALU ops

// All counters has high register, storing remaining 32 MSb (not used). 
// OBS! mcycle will overflow after ~2min.
// Documentation used:  DTEK-V Hardware Counter Introduction (Literature and Resources).
//                      DTEK-V Processor Overview Sheet (Literature and Resources).
// Registers are writable.
void printHardwareCounters(){
    asm volatile ("csrr %0, mcycle" : "=r"(mcycle));
    asm volatile ("csrr %0, minstret" : "=r"(minstret));
    asm volatile ("csrr %0, mhpmcounter3" : "=r"(mhpmcounter3));
    asm volatile ("csrr %0, mhpmcounter4" : "=r"(mhpmcounter4));
    asm volatile ("csrr %0, mhpmcounter5" : "=r"(mhpmcounter5));
    asm volatile ("csrr %0, mhpmcounter6" : "=r"(mhpmcounter6));
    asm volatile ("csrr %0, mhpmcounter7" : "=r"(mhpmcounter7));
    asm volatile ("csrr %0, mhpmcounter8" : "=r"(mhpmcounter8));
    asm volatile ("csrr %0, mhpmcounter9" : "=r"(mhpmcounter9));

    printc('\n');
    print_dec(mcycle); printc(',');
    print_dec(minstret); printc(',');
    print_dec(mhpmcounter3); printc(',');
    print_dec(mhpmcounter4); printc(',');
    print_dec(mhpmcounter5); printc(',');
    print_dec(mhpmcounter6); printc(',');
    print_dec(mhpmcounter7); printc(',');
    print_dec(mhpmcounter8); printc(',');
    print_dec(mhpmcounter9);
}

void resetHardwareCounters(){
    asm ("csrw mcycle, x0");
    asm ("csrw minstret, x0");
    asm ("csrw mhpmcounter3, x0");
    asm ("csrw mhpmcounter4, x0");
    asm ("csrw mhpmcounter5, x0");
    asm ("csrw mhpmcounter6, x0");
    asm ("csrw mhpmcounter7, x0");
    asm ("csrw mhpmcounter8, x0");
    asm ("csrw mhpmcounter9, x0");
}

#endif