#include <stdio.h>
#include "accele.h"
#include "dtekv_lib.h"

//#include "accele.c"

void handle_interrupt(unsigned cause) 
{}

void set_leds(int led_mask){
  volatile int* led_pointer = (volatile int*) 0x04000000;
  (*led_pointer) = led_mask & 0b1111111111;
}

/* Get switch state. */
int get_sw( void ){
  return *((volatile int*) 0x04000010) & 0b1111111111;
}

int main() {
    while(1) {
        volatile short* accelePointer = (short*) 0x32;
        //display_2_dig_short((short) 0, (short) ((*accelePointer & 0b11111111) % 100));
        set_leds(1);
    }
    return 0;
};