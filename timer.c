#include "timer.h"
#include "dtekv_lib.h"

extern void enable_interrupt( void );

/*
* Enable interrupts in DTEK-V board.
* Oscillator frequency = 30 MHz
*/
void timerSetup(){
    volatile unsigned short* PERIOD_LOW = (volatile unsigned short*) 0x04000028;    // Timer first half
    volatile unsigned short* PERIOD_HIGH = (volatile unsigned short*) 0x0400002c;   // Timer second half

    // Timeout every TIMER_PERIOD milliseconds
    *PERIOD_LOW = (3000 * TIMER_PERIOD) & 0xFFFF; // 16 lsb
    *PERIOD_HIGH = (3000 * TIMER_PERIOD) >> 16; // 16 msb

    // allow interrupts
    enable_interrupt();

    volatile unsigned short* CONTROL = (unsigned short*) 0x04000024;
    // configure timer to generate interrupts
    *(CONTROL) = 0b111; // bits START, CONT & ITO (respectively)
}

unsigned short getTimeLow(){
    volatile unsigned short *SNAPL = (volatile unsigned short*) 0x04000030;
    *SNAPL = 1;
    return *SNAPL;
}