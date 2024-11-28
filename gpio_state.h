#ifndef GPIO_STATE_H
#define GPIO_STATE_H

#include "dpad_state.h"

static unsigned char DPAD_RAW_STATE;
static volatile int* gpio_pointer;

enum Direction get_dpad_state();

#endif