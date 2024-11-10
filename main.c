#include <stdio.h>
#include "seven_seg.h"
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

int get_gpio(){
  volatile int* gpio_pointer = (volatile int*) 0x040000e0;
  return *gpio_pointer;
}

void set_gpio(int value){
  volatile int* gpio_pointer = (volatile int*) 0x040000e0;
  *gpio_pointer = value;
}

int get_button_state(){
  int gpio_state = get_gpio();
  if(gpio_state == 1 || gpio_state == 2 || gpio_state == 4 || gpio_state == 8) {
    return gpio_state;
  }
  else{
    return 0;
  }
}

int main() {
    unsigned char current_state = 0;
    while(1) {
        if (get_button_state_change() != 0) {
          current_state = get_button_state_change();
        }

        set_leds(current_state);
    }
    return 0;
};