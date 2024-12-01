#ifndef VGA_H
#define VGA_H

/**
 * Width, in pixels.
*/
#define SCR_W 320
#define SCR_H 240

/**
 * Set the color of a pixel in the backbuffer.
*/
inline void setPixel(unsigned int x, unsigned int y, unsigned char color){
    *(VGA + y * SCR_W + x) = color;
    return;
}

/**
 * Perform framebuffer swap.
*/
void swap();

/**
 * Draw a filled square to the backbuffer.
*/
void fillSquare(unsigned int x0, unsigned int y0, unsigned int w, 
                unsigned int h, unsigned char color);

/**
 * Reset pixel buffer
*/
void resetAllPixels();

void drawText(unsigned int x0, unsigned int y0, char* text, unsigned char color);

void drawChar(unsigned int x0, unsigned int y0, unsigned int char_data, unsigned char color);

#endif