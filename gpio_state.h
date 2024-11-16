#ifndef GPIO_STATE_H
#define GPIO_STATE_H

enum DPAD_STATE;

static unsigned char DPAD_RAW_STATE;
static volatile int* gpio_pointer;

enum DPAD_STATE get_dpad_state();

#endif // GPIO_STATE_H