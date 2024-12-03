#include "gameinput.h"
#include "dpad_state.h"

unsigned char DPAD_RAW_STATE = 0b0001;
volatile int* gpio_pointer = (volatile int*) 0x040000e0;

enum Direction updateDirection() {
    unsigned char new_dpad_state = 0b1111 & (~(*gpio_pointer));
    unsigned char new_heading = (new_dpad_state ^ DPAD_RAW_STATE) & new_dpad_state;

    switch(new_heading){
        case 0b1000:
        case 0b100:
        case 0b10:
        case 0b1:
            // update state if new heading is ok
            DPAD_RAW_STATE = new_heading;
    }

    return (enum Direction) DPAD_RAW_STATE;
}