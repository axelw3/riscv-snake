// Other files
#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "DPAD_STATE.h"
#include "vga.h"

/*
* Used to communicate with main() (or anytime the program should rest).
* Since the program will keep CPU, there is no need to allow 
* for multiple users of the TIMER_TIMOUT variable.
*/
unsigned short TIMER_TIMEOUT = 0;

/* Called from assembly code. */
void handle_interrupt(unsigned int cause){
  if(cause == 16){
    TIMER_TIMEOUT = 1;
    // bekräfta IRQ genom att nollställa TO-biten (avsnitt 23.4.4 i dokumentationen)
    *((volatile unsigned short*) 0x04000020) &= (unsigned short int) !0b1; //0b1111111111111110; // reset
  }
}

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

int x_offset, y_offset = 0;
  while(1) {
    if(TIMER_TIMEOUT == 1) {
      resetAllPixels();
      fillsquare(4, 4, x_offset, y_offset, 0x2);
      x_offset++;
      y_offset++;
    }
  }

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