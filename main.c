// Other files
#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "dpad_state.h"
#include "vga.h"
#include "timer_clock.h"
#include "gamemap.h"

void set_leds(int led_state){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_state & 0b1111111111;
}

/*
* Used to communicate with main() (or anytime the program should rest).
* Take care to ensure that only one if statment waits for TIMER_TIMEOUT = 1,
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

/**
 * Starts timer.
*/
unsigned char timer_start(){
  TIMER_TIMEOUT = 0;
}

/**
 * Hold cpu in while-loop until TIMER_TIMEOUT = 1 (i.e a harware clock interrupt occurs)
 */
void timer_cpu_hold_wait(){
  while(1){
    if(TIMER_TIMEOUT == 1){
      return;
    }
  }
}

/* Get switch state. */
int get_sw(){
    return *((volatile int*) 0x04000010) & 0b1111111111;
}

int main(){
    timer_start();

    signed char sh[2],  // position of the snake's head
                st[2],  // position of the snake's tail
                snh[2]; // nästa position för snake-huvud (temporär användning)

    const unsigned short sz = MAP_W * MAP_H;

    for(unsigned short i = 0; i < sz; i++){
        *((unsigned char*) map + i) = EMPTY; // reset map
    }

    sh[0] = 5;      sh[1] = 5; // head at 5,5
    st[0] = sh[0];  st[1] = sh[1]; // tail at same location
    mSet(sh, SHEAD); // mark tile as head on map

    snh[0] = sh[0]; snh[1] = sh[1]; // initial ny huvudposition = aktuell huvudposition (ovan)

    short snakeLength = 1; // ej betydande för spelbarhet, endast för visning av poäng
    set_displays(0, snakeLength / 10);
    set_displays(1, snakeLength % 10);

    enum Direction move_direction;

    unsigned int t = 0;
    signed char atNextPos;

    // TODO: Generera ett äpple här

    while(1){
      move_direction = get_dpad_state();

      if(t++ == 10000){
          t = 0;

          switch(move_direction){
          case RIGHT:
              snh[0]++;
              break;
          case LEFT:
              snh[0]--;
              break;
          case DOWN:
              snh[1]++;
              break;
          case UP:
              snh[1]--;
              break;
          }

          atNextPos = mGet(snh);

          if(atNextPos > 0 || snh[0] < 0 || snh[1] < 0 || snh[0] >= MAP_W || snh[1] >= MAP_H){
              // collision with tail or with screen edge
              // TODO: lose game
          }

          mSet(snh, SHEAD); // add new head
          mSet(sh, mTrDir(move_direction)); // set old head to a tail piece pointing forward

          sh[0] = snh[0]; sh[1] = snh[1]; // updatera huvudposition

          if(atNextPos == APPLE){
              // öka längden, dvs. vi behåller sista svansbiten denna gång
              snakeLength++;
              set_displays(0, snakeLength / 10);
              set_displays(1, snakeLength % 10);

              // TODO: Generera ett äpple här
          }else{
              // no collision, no apple

              // flytta svansposition ett steg framåt (mot huvudet)
              switch(mGet(st)){
                  case SBONL:
                      st[0]--;
                      break;
                  case SBONU:
                      st[1]--;
                      break;
                  case SBONR:
                      st[0]++;
                      break;
                  case SBOND:
                      st[1]++;
                      break;
                  default:
              }

              mSet(st, EMPTY); // ta bort gammal svans
          }

          // TODO: Rendera allt
          for(short x = 0; x < MAP_W; x++){
            for(short y; y < MAP_H; y++){
              if(map_get((MAP_W * MAP_H) != 0)){
                fillSquare(0, 0, MAP_W, MAP_H, 0x1);
              }
            }
          }
          
      }
      timer_cpu_hold_wait();
    }


    return 0;
};