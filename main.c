// Other files
#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "DPAD_STATE.h"
#include "vga.h"
#include "timer_clock.h"

void set_leds(int led_mask){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_mask & 0b1111111111;
}

/*
* Used to communicate with main() (or anytime the program should rest).
* Take care to ensure that only one if statment waints for TIMER_TIMEOUT = 1,
* as to maintain consistency in execution.
*/
volatile short TIMER_TIMEOUT = 0;
int timeout_count = 0;

/* Called from assembly code. */
void handle_interrupt(unsigned int cause){
  if(cause == 16){
    // bekräfta IRQ genom att nollställa TO-biten (avsnitt 23.4.4 i dokumentationen)
    *((volatile unsigned short*) 0x04000020) &= (unsigned short int) !0b1; //0b1111111111111110; // reset

    if(timeout_count++ % 10 == 0) {
      TIMER_TIMEOUT = 1;
    }
  }
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
  TIMER_TIMEOUT = 1;
  timer_setup();

  resetAllPixels();
  fillSquare(0, 0, 24, 24, 0xcc);
  swap();

  unsigned short x_offset = 8;
  unsigned short y_offset = 8;

  while(1) {
    set_leds(TIMER_TIMEOUT);
    if(TIMER_TIMEOUT) {
      resetAllPixels();
      fillSquare(x_offset, y_offset, 12, 12, 0x1);
      swap();
      x_offset += 4;
      y_offset += 4;
      TIMER_TIMEOUT = 0;
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