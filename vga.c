#include "vga.h"

void setPixel(unsigned int x, unsigned int y, unsigned char color){
    *(VGA + y * SCR_W + x) = color;
    return;
}

void swap(){
    *(VGA_CTRL + 1) = VGA; // set address of rgb data
    *VGA_CTRL = 0; // swap
    return;
}

void fillSquare(unsigned int x0, unsigned int y0, unsigned int w, unsigned int h, unsigned char color){
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
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