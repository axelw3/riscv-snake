#include "font.h"

const unsigned int  FCHAR_A = 0b011101000111111100011000110001,
                    FCHAR_B = 0b111101000111110100011000111110,
                    FCHAR_C = 0b011111000010000100001000001111;

unsigned int getCharData(char ch){
    switch(ch){
        case 'A':
            return FCHAR_A;
        case 'B':
            return FCHAR_B;
        case 'C':
            return FCHAR_C;
        default:
            return 0;
    }
}