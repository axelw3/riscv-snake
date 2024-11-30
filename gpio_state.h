#ifndef GPIO_STATE_H
#define GPIO_STATE_H

#include "dpad_state.h"

static unsigned char DPAD_RAW_STATE = 0b0001;
static volatile int* gpio_pointer = (volatile int*) 0x040000e0;

enum Direction get_dpad_state();

#endif