#include "dtekv_lib.h"
#include "seven_seg.h"
#include "gameinput.h"
#include "dpad_state.h"
#include "vga.h"
#include "timer.h"
#include "gamemap.h"
#include "debug.h"

#define ERROR_INVALID_GAME_STATE 0
#define ERROR_NO_EMPTY_TILE 1

#ifdef DEBUG
void set_leds(int led_state){
    volatile int* led_pointer = (volatile int*) 0x04000000;
    (*led_pointer) = led_state & 0b1111111111;
}
#endif

/**
 * Whether or not a timeout has occured.
*/
volatile unsigned char TIMER_TIMEOUT = 0;

/**
 * Number of interrupts. Enables the use of long timer periods by waiting for multiple
 * interrupts before setting `TIMER_TIMEOUT = 1`.
*/
int timeout_count = 0;

/* Handle interrupts. Called from assembly code. */
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

/**
 * Set the given coordinates to a pseudo-random position, based on the current timer value.
 * If the corresponding tile is non-EMPTY, the position will be set to the next available
 * (empty) tile, moving left-right and up-down.
 * 
 * @param position a two-element array where the generated coordinates will be stored
 * @return `0` if a position was found
*/
unsigned char randomPosition(unsigned char *position){
    unsigned short left = MAP_S;
    unsigned short pos = getTimeLow() % left;

    while(left-- > 0){
        if(mGetAt(pos) == EMPTY){
            position[0] = pos % MAP_W;
            position[1] = pos / MAP_W;
            return 0;
        }
        pos++;
        pos %= MAP_S;
    }

    return 1;
}

/**
 * Display the current score on the seven-segment displays.
 * @param score score to be displayed
*/
void displayScore(short score){
    set_displays(5, -1);
    set_displays(4, -1);
    set_displays(3, -1);
    set_displays(2, -1);

    if(score >= 0){
        set_displays(1, score / 10);
        set_displays(0, score % 10);
    }else{
        set_displays(1, -1);
        set_displays(0, -1);
    }
}

/**
 * Show title screen and wait for user input.
*/
void showTitleScreen(){
    drawText(10, 10, "SNAKE", 0xC);
    drawText(10, 24, "PRESS KEY1 TO START", 0xFF);
    while((*((volatile char*) 0x040000d0) & 0b00000001) == 0);
}

/**
 * Show error screen.
*/
void showErrorScreen(const signed short code){
    drawText(10, 10, "AN ERROR OCCURED:", 0xC);
    switch(code){
        case ERROR_INVALID_GAME_STATE:
            drawText(10, 24, "INVALID GAME STATE", 0xFF);
            break;
        case ERROR_NO_EMPTY_TILE:
            drawText(10, 24, "NO EMPTY TILE", 0xFF);
            break;
    }
}

/**
 * Show the "game over" screen and wait for used input.
*/
void showGameOverScreen(short score){
    drawText(10, 10, "GAME OVER", 0xC);
    drawText(10, 24, "SCORE: ", 0xC);
    
    char scoreStr[4] = "000";
    for(int i = 2; i >= 0; i--){
        scoreStr[i] = (char) (0x30 + (score % 10));
        score /= 10;
    }

    drawText(10 + 42, 24, scoreStr, 0xC);
    drawText(10, 38, "PRESS KEY1 TO CONTINUE", 0xFF);
    while((*((volatile char*) 0x040000d0) & 0b00000001) == 0);
}

/**
 * Run the game.
 * @return score achieved by the player
*/
signed short startGame(){
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
    displayScore(snakeLength);

    enum Direction  move_direction = RIGHT,
                    next_direction = RIGHT;

    // state of the tile we are attempting to move into
    enum TileData atNextPos;

    randomPosition(ap); // generera ny äppelposition
    mSet(ap, APPLE); // skapa äpple

    while(1){
        // wait for timeout
        while(!TIMER_TIMEOUT){
            // poll user inputs while waiting
            next_direction = updateDirection();
#ifdef DEBUG
            set_leds((int) 0b1111 & (~(*((volatile int*) 0x040000e0))));
#endif
        }

        // reset timeout state
        TIMER_TIMEOUT = 0;

        if(next_direction != move_direction && snakeLength > 1){
            switch(next_direction + move_direction){
                case 12:
                case 3:
                    // not allowed to reverse direction when snakeLength > 1
                    next_direction = move_direction;
            }
        }

        move_direction = next_direction;

        // calculate new head position
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

        // check for collision with screen edge
        if(snh[0] < 0 || snh[1] < 0 || snh[0] >= MAP_W || snh[1] >= MAP_H){
            return snakeLength; // lose game
        }

        atNextPos = mGet(snh); // check what is at the target position

        // check for collision with body
        if(atNextPos != EMPTY && atNextPos != APPLE){
            return snakeLength; // lose game
        }

        mSet(snh, SHEAD); // add new head
        mSet(sh, mTrDir(move_direction)); // set old head to a tail piece pointing forward

        sh[0] = snh[0]; sh[1] = snh[1]; // updatera huvudposition

        if(atNextPos == APPLE){
            // öka längden, dvs. vi behåller sista svansbiten denna gång
            snakeLength++;
            displayScore(snakeLength);

            if(randomPosition(ap) != 0){ // generera ny äppelposition
                // ingen ledig tile kunde hittas - spelet vunnit
                return ERROR_NO_EMPTY_TILE;
            }

            mSet(ap, APPLE); // skapa nytt äpple
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
                    // error (invalid game state)
                    return ERROR_INVALID_GAME_STATE;
            }

            mSet(st, EMPTY); // ta bort gammal svans

            st[0] = snt[0]; st[1] = snt[1]; // spara ny svansposition
        }
    }
}

int main(){
    // Clock is started here, since we use the timer value for pseudo-
    // RNG, and this guarantees some kind of randomness (based on time
    // user input (in this case depending on how much time elapses
    // between startup and game start).
    timerSetup();

    while(1){
        displayScore(-1);

        resetAllPixels();
        showTitleScreen();

#ifdef DEBUG
        resetHardwareCounters();
#endif
        resetAllPixels();
        signed short score = startGame();
#ifdef DEBUG
        printHardwareCounters();
#endif

        resetAllPixels();
        if(score < 0){
            showErrorScreen(score);
            break;
        }

        showGameOverScreen(score);
    }

    return 0;
}