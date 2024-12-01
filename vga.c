#include "vga.h"
#include "gamemap.h"

/**
 * VGA backbuffer.
*/
volatile char *VGA = (volatile char*) 0x08000000;

/**
 * DMA controller register.
*/
volatile char *VGA_CTRL = (volatile char*) 0x04000100;

void setPixel(unsigned int x, unsigned int y, unsigned char color){
    *(VGA + y * SCR_W + x) = color;
    return;
}

void swap(){
    *(VGA_CTRL + 1) = (int) VGA; // set address of rgb data
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

/**
 * Updates VGA buffer based on state of 'map' when called.
 */
void invalidate(){
    for(short x = 0; x <= MAP_H; x++){
        for(short y = 0; y <= MAP_W; y++){
            switch (mGet(x * y)){
                case EMPTY:
                    fillSquare(x * MAP_W, y * MAP_H, MAP_W, MAP_H, 0x0);
                    break;
                case APPLE:
                    fillSquare(x * MAP_W, y * MAP_H, MAP_W, MAP_H, 0xDC);
                    break;
                case SHEAD:
                    fillSquare(x * MAP_W, y * MAP_H, MAP_W, MAP_H, 0xF);
                default:
                    fillSquare(x * MAP_W, y * MAP_H, MAP_W, MAP_H, 0xc0);
            }
        }
    } 
}