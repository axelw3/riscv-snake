#include "gpio_state.h"
#include "dpad_state.h"

unsigned char DPAD_RAW_STATE = 0b0001;
volatile int* gpio_pointer = (volatile int*) 0x040000e0;

// Determine next direction to move.
enum Direction get_dpad_state() {
    unsigned char new_dpad_state = ~(*gpio_pointer & 0b1111);
    unsigned char new_heading = (new_dpad_state ^ DPAD_RAW_STATE) & new_dpad_state;

    switch((enum Direction) new_heading){
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            // update state if new heading is ok
            DPAD_RAW_STATE = new_heading;
    }

    return (enum Direction) new_heading;
}