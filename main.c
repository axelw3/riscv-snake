// Other files
#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gpio_state.h"
#include "dpad_state.h"
#include "vga.h"
#include "timer.h"
#include "gamemap.h"

/*void set_leds(int led_state){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_state & 0b1111111111;
}*/

volatile short TIMER_TIMEOUT = 0;
int timeout_count = 0;

/* Called from assembly code. */
void handle_interrupt(unsigned int cause){
    if(cause == 16){
        // bekräfta IRQ genom att nollställa TO-biten (avsnitt 23.4.4 i dokumentationen)
        *((volatile unsigned short*) 0x04000020) &= (unsigned short int) !0b1; //0b1111111111111110; // reset

        timeout_count++;
        if((timeout_count %= 10) == 0){
            TIMER_TIMEOUT = 1;
        }
    }
}

void randomPosition(unsigned char *position){
    unsigned short left = MAP_S;
    unsigned short pos = getTimeLow() % left;
    while(left-- > 1){
        if(mGetAt(pos) == EMPTY) break;
        pos++;
        pos %= MAP_S;
    }
    position[0] = pos % MAP_W;
    position[1] = pos / MAP_W;
}

void showTitleScreen(){
    drawText(10, 10, "SNAKE", 0xC);
    drawText(10, 24, "PRESS KEY1 TO START", 0xFF);
    while((*((volatile char*) 0x040000d0) & 0b00000001) == 0);
}

void showGameOverScreen(short score){
    drawText(10, 10, "GAME OVER", 0xC);
    drawText(10, 24, "SCORE: ", 0xC);
    
    char scoreStr[4] = "000";
    for(int i = 2; i >= 0; i--){
        scoreStr[i--] = (char) (0x30 + (score % 10));
        score /= 10;
    }

    drawText(10 + 42, 24, scoreStr, 0xC);
    drawText(10, 38, "PRESS KEY1 TO CONTINUE", 0xFF);
    while((*((volatile char*) 0x040000d0) & 0b00000001) == 0);
}

short startGame(){
    timerSetup();

    unsigned char   sh[2],  // position of the snake's head
                    st[2],  // position of the snake's tail
                    snh[2], // nästa position för snake-huvud (temporär användning)
                    snt[2], // nästa position för sista tail-biten (temporär användning)
                    ap[2]; // nuvarande äppel-position

    for(unsigned short i = 0; i < MAP_W * MAP_H; i++){
        map[i] = EMPTY; // reset map
    }

    sh[0] = 5;      sh[1] = 5;      // head at 5,5
    ap[0] = 0;      ap[1] = 0;      // set apple position (will be randomised before use)
    st[0] = sh[0];  st[1] = sh[1];  // tail at same location

    mSet(sh, SHEAD); // mark tile as head on map

    snh[0] = sh[0]; snh[1] = sh[1]; // initial ny huvudposition = aktuell huvudposition (ovan)
    snt[0] = st[0]; snt[1] = st[1]; // initial ny tail-position = aktuell tail-position (ovan)

    short snakeLength = 1; // ej avgörande för spelbarhet, endast för visning av poäng

    enum Direction move_direction = RIGHT;

    enum TileData atNextPos;

    randomPosition(ap); // generera ny äppelposition
    mSet(ap, APPLE); // skapa äpple

    while(1){
        while(TIMER_TIMEOUT == 0){
            move_direction = get_dpad_state();
        }

        TIMER_TIMEOUT = 0;

        // debug
        //set_leds((int) move_direction);

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

        if((atNextPos != EMPTY && atNextPos != APPLE) || snh[0] < 0 || snh[1] < 0 || snh[0] >= MAP_W || snh[1] >= MAP_H){
            // collision with tail or with screen edge
            return snakeLength; // lose game
        }

        mSet(snh, SHEAD); // add new head
        mSet(sh, mTrDir(move_direction)); // set old head to a tail piece pointing forward

        sh[0] = snh[0]; sh[1] = snh[1]; // updatera huvudposition

        if(atNextPos == APPLE){
            // öka längden, dvs. vi behåller sista svansbiten denna gång
            snakeLength++;
            set_displays(0, snakeLength / 10);
            set_displays(1, snakeLength % 10);

            randomPosition(ap); // generera äppelposition
            mSet(ap, APPLE); // skapa äpple
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
        short score = startGame();

        resetAllPixels();
        showGameOverScreen(score);
    }

    return 0;
}