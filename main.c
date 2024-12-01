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

/* Get switch state. */
int get_sw(){
    return *((volatile int*) 0x04000010) & 0b1111111111;
}

void showTitleScreen(){
    drawText(10, 10, "SNAKE", 0xC);
    while(1){
        // do nothing
    }
}

void startGame(){
    timerSetup();

    signed char sh[2],  // position of the snake's head
                st[2],  // position of the snake's tail
                snh[2], // nästa position för snake-huvud (temporär användning)
                snt[2]; // nästa position för sista tail-biten (temporär användning)

    for(unsigned short i = 0; i < MAP_W * MAP_H; i++){
        map[i] = EMPTY; // reset map
    }

    sh[0] = 5;      sh[1] = 5; // head at 5,5
    st[0] = sh[0];  st[1] = sh[1]; // tail at same location
    mSet(sh, SHEAD); // mark tile as head on map

    snh[0] = sh[0]; snh[1] = sh[1]; // initial ny huvudposition = aktuell huvudposition (ovan)
    snt[0] = st[0]; snt[1] = st[1]; // initial ny tail-position = aktuell tail-position (ovan)

    short snakeLength = 1; // ej avgörande för spelbarhet, endast för visning av poäng
    set_displays(0, snakeLength / 10);
    set_displays(1, snakeLength % 10);

    enum Direction move_direction = RIGHT;

    signed char atNextPos;

    // TODO: Generera ett äpple här

    while(1){
        while(TIMER_TIMEOUT == 0){
            move_direction = get_dpad_state();
        }

        TIMER_TIMEOUT = 0;

        // debug
        // TODO: ta bort denna rad
        set_leds((int) move_direction);

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
                    snt[0]--;
                    break;
                case SBONU:
                    snt[1]--;
                    break;
                case SBONR:
                    snt[0]++;
                    break;
                case SBOND:
                    snt[1]++;
                    break;
                default:
            }

            mSet(st, EMPTY); // ta bort gammal svans

            st[0] = snt[0]; st[1] = snt[1]; // spara ny svansposition
        }
    }
}

int main(){
    while(1){
        resetAllPixels();
        showTitleScreen();

        resetAllPixels();
        startGame();
    }

    return 0;
}