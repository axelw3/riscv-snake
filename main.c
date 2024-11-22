#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "DPAD_STATE.h"
#include "vga.h"

void handle_interrupt(unsigned int cause){}

void set_leds(int led_mask){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_mask & 0b1111111111;
}

/* Get switch state. */
int get_sw(){
    return *((volatile int*) 0x04000010) & 0b1111111111;
}

/*
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
*/

int main(){
  resetAllPixels();
  fillSquare(2, 1, 2, 2, 0x2);
  swap();

  while(1){
      enum DPAD_STATE state = get_dpad_state();
      switch(state) {
        case UP:
          set_leds(0b1101);
          break;
        case DOWN:
          set_leds(0b0111);
          break;
        case LEFT:
          set_leds(0b1011);
          break;
        case RIGHT:
          set_leds(0b1110);
          break;
        default:
      }
  }

  return 0;
};