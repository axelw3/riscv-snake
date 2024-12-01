#include "seven_seg.h"

/* Display a number on the 7 segment display */
void set_displays(int display_number, int value){
    volatile char* seg7display = (volatile char*) (0x04000050 + 0x10 * display_number);
    switch(value){
        case 0:
            (*seg7display) = 0b11000000;
            break;
        case 1:
            (*seg7display) = 0b11111001;
            break;
        case 2:
            (*seg7display) = 0b10100100;
            break;
        case 3:
            (*seg7display) = 0b10110000;
            break;
        case 4:
            (*seg7display) = 0b10011001;
            break;
        case 5:
            (*seg7display) = 0b10010010;
            break;
        case 6:
            (*seg7display) = 0b10000010;
            break;
        case 7:
            (*seg7display) = 0b11111000;
            break;
        case 8:
            (*seg7display) = 0b10000000;
            break;
        case 9:
            (*seg7display) = 0b10010000;
            break;
        default:
            (*seg7display) = 0b11111111;
    }

    return;
}