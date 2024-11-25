#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "dpad_state.h"
#include "vga.h"
#include "gamemap.h"

void handle_interrupt(unsigned int cause){}

void set_leds(int led_state){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_state & 0b1111111111;
}

int main(){
    signed char sh[2],  // position of the snake's head
                st[2],  // position of the snake's tail
                snh[2]; // nästa position för snake-huvud (temporär användning)

    const unsigned short sz = MAP_W * MAP_H;

    for(unsigned short i = 0; i < sz; i++){
        map[i] = EMPTY; // reset map
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

    while(1){
        move_direction = get_dpad_state();

        if(t++ == 10000){
            t = 0;

            switch(move_direction) {
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

            mSet(snh[0], snh[1], SHEAD); // add new head
            mSet(sh[0], sh[1], mTrDir(move_direction)); // set old head to a tail piece pointing forward

            sh[0] = snh[0]; sh[1] = snh[1]; // updatera huvudposition

            if(atNextPos == APPLE){
                // öka längden, dvs. vi behåller sista svansbiten denna gång
                snakeLength++;
                set_displays(0, snakeLength / 10);
                set_displays(1, snakeLength % 10);
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
                }

                mSet(st, EMPTY); // ta bort gammal svans
            }
        }
    }

    return 0;
};