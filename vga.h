// VGA_H
#ifndef VGA_H
#define VGA_H

/**
 * Width, in pixels.
*/
#define SCR_W 320
#define SCR_H 240

/**
 * VGA backbuffer.
*/
volatile char *VGA = (volatile char*) 0x08000000;

/**
 * DMA controller register.
*/
volatile char *VGA_CTRL = (volatile char*) 0x04000100;

/**
 * Set the color of a pixel in the backbuffer.
*/
void setPixel(unsigned int x, unsigned int y, unsigned char color);

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

#endif // VGA_H