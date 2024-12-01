#include "font.h"

// Glyph design by user "Qimplef" on fontstruct, plus ÅÄÖ by sethsson.
// https://fontstruct.com/fontstructions/show/521592/px_5x6_1

const unsigned int  FONTCHAR_A = 0b011101000111111100011000110001,
                    FONTCHAR_B = 0b111101000111110100011000111110,
                    FONTCHAR_C = 0b011111000010000100001000001111,
                    FONTCHAR_D = 0b111101000110001100011000111110,
                    FONTCHAR_E = 0b111111000011110100001000011111,
                    FONTCHAR_F = 0b111111000011110100001000010000,
                    FONTCHAR_G = 0b011111000010111100011000101110,
                    FONTCHAR_H = 0b100011000111111100011000110001,
                    FONTCHAR_I = 0b011100010000100001000010001110,
                    FONTCHAR_J = 0b001110001000010000100001011100,
                    FONTCHAR_K = 0b100011001010100110101000110001,
                    FONTCHAR_L = 0b100001000010000100001000011111,
                    FONTCHAR_M = 0b100011101110101100011000110001,
                    FONTCHAR_N = 0b100011100110101100111000110001,
                    FONTCHAR_O = 0b011101000110001100011000101110,
                    FONTCHAR_P = 0b111101000111110100001000010000,
                    FONTCHAR_Q = 0b011101000110001101011001001101,
                    FONTCHAR_R = 0b111101000111110100011000110001,
                    FONTCHAR_S = 0b011111000001110000010000111110,
                    FONTCHAR_T = 0b111110010000100001000010000100,
                    FONTCHAR_U = 0b100011000110001100011000101110,
                    FONTCHAR_V = 0b100011000110001010100101000100,
                    FONTCHAR_W = 0b100011000110101101011010101010,
                    FONTCHAR_X = 0b100010101000100010101000110001,
                    FONTCHAR_Y = 0b100010101000100001000010000100,
                    FONTCHAR_Z = 0b111110001000100010001000011111,
                    //FONTCHAR_Å = 0b001000000001110100011111110001,
                    //FONTCHAR_Ä = 0b100010000001110100011111110001,
                    //FONTCHAR_Ö = 0b100010000001110100011000101110,
                    FONTCHAR_NBSP = 0, 
                    FONTCHAR_1 = 0b001000110000100001000010001110;

unsigned int getCharData(char ch){
    switch(ch){
        case 'A':
            return FONTCHAR_A;
        case 'B':
            return FONTCHAR_B;
        case 'C':
            return FONTCHAR_C;
        case 'D':
            return FONTCHAR_D;
        case 'E':
            return FONTCHAR_E;
        case 'F':
            return FONTCHAR_F;
        case 'G':
            return FONTCHAR_G;
        case 'H':
            return FONTCHAR_H;
        case 'I':
            return FONTCHAR_I;
        case 'J':
            return FONTCHAR_J;
        case 'K':
            return FONTCHAR_K;
        case 'L':
            return FONTCHAR_L;
        case 'M':
            return FONTCHAR_M;
        case 'N':
            return FONTCHAR_N;
        case 'O':
            return FONTCHAR_O;
        case 'P':
            return FONTCHAR_P;
        case 'Q':
            return FONTCHAR_Q;
        case 'R':
            return FONTCHAR_R;
        case 'S':
            return FONTCHAR_S;
        case 'T':
            return FONTCHAR_T;
        case 'U':
            return FONTCHAR_U;
        case 'V':
            return FONTCHAR_V;
        case 'W':
            return FONTCHAR_W;
        case 'X':
            return FONTCHAR_X;
        case 'Y':
            return FONTCHAR_Y;
        case 'Z':
            return FONTCHAR_Z;
        //case 'Å':
        //    return FONTCHAR_Å;
        //case 'Ä':
        //    return FONTCHAR_Ä;
        //case 'Ö':
        //    return FONTCHAR_Ö;
        case ' ':
            return FONTCHAR_NBSP;
        case '1':
            return FONTCHAR_1;
        default:
            return 0;
    }
}