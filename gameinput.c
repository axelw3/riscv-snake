#include "gameinput.h"

unsigned char DPAD_RAW_STATE = 0b0001;
volatile int* gpio_pointer = (volatile int*) 0x040000e0;

enum Direction updateDirection() {
    unsigned char new_dpad_state = 0b1111 & (~(*gpio_pointer));
    unsigned char new_heading = (new_dpad_state ^ DPAD_RAW_STATE) & new_dpad_state;

    switch(new_heading){
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            // update state if new heading is ok
            DPAD_RAW_STATE = new_heading;
    }

    return (enum Direction) DPAD_RAW_STATE;
}