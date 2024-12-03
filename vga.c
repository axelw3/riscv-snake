#include "vga.h"
#include "gamemap.h"
#include "font.h"

/**
 * VGA backbuffer.
*/
volatile char *VGA = (volatile char*) 0x08000000;

extern inline void setPixel(unsigned int x, unsigned int y, unsigned char color);

void fillSquare(unsigned int x0, unsigned int y0, unsigned int s, unsigned char color){
    for(int x = 0; x < s; x++){
        for(int y = 0; y < s; y++){
            setPixel(x0 + x, y0 + y, color);
        }
    }
    return;
}

void resetAllPixels(){
    for(int x = 0; x < SCR_W; x++){
        for(int y = 0; y < SCR_H; y++){
            setPixel(x, y, 0x0);
        }
    }
}

void drawText(unsigned int x0, unsigned int y0, char* text, unsigned char color){
    char ch;
    while((ch = *(text++)) != '\0'){
        drawChar(x0, y0, getCharData(ch), color);
        x0 += 6;
    }
}

void drawChar(unsigned int x0, unsigned int y0, unsigned int glyph_data, unsigned char color){
    int pos = FCHAR_W * FCHAR_H;
    do{
        pos--;

        if(glyph_data & 0b1){
            setPixel(x0 + (pos % FCHAR_W), y0 + (pos / FCHAR_W), color);
        }
    }while(glyph_data >>= 1);
}