/**
 * Width, in pixels.
*/
const unsigned int WIDTH = 320;
const unsigned int HEIGHT = 240;

/**
 * VGA backbuffer.
*/
volatile char *VGA = (volatile char*) 0x08000000;

/**
 * DMA controller register.
*/
volatile char *VGA_CTRL = (volatile int*) 0x04000100;

/**
 * Set the color of a pixel in the backbuffer.
*/
void setPixel(unsigned int x, unsigned int y, unsigned char color){
    *(VGA + y * WIDTH + x) = color;
    return;
}

/**
 * Perform framebuffer swap.
*/
void swap(){
    *(VGA_CTRL + 1) = VGA; // set address of rgb data
    *VGA_CTRL = 0; // swap
    return;
}

/**
 * Draw a filled square to the backbuffer.
*/
void fillSquare(unsigned int x0, unsigned int y0, unsigned int w, unsigned int h, unsigned char color){
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            setPixel(x0 + x, y0 + y, color);
        }
    }
    return;
}

/*
Reset pixel buffer
*/
void resetAllPixels(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            setPixel(x, y, 0x0);
        }
    }
}