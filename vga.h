#ifndef VGA_H
#define VGA_H

/**
 * Screen width, in pixels.
*/
#define SCR_W 320

/**
 * Screen height, in pixels.
*/
#define SCR_H 240

/**
 * Set the color of a pixel on the screen (frontbuffer).
 * @param x pixel x coordinate
 * @param y pixel y coordinate
 * @param color color to be used
 * 
 * @author sethsson
*/
inline void setPixel(unsigned int x, unsigned int y, unsigned char color){
    *((volatile char*) 0x08000000 + y * SCR_W + x) = color;
    return;
}

/**
 * Draw a filled square to the screen.
 * @param x0 leftmost pixel x coordinate
 * @param y0 top pixel y coordinate
 * @param s side length, in pixels
 * @param color fill color
 * 
 * @author sethsson
*/
void fillSquare(unsigned int x0, unsigned int y0, unsigned int s, unsigned char color);

/**
 * Reset pixel buffer
 * 
 * @author owiren
*/
void resetAllPixels();

/**
 * Render a text string on the screen.
 * @param x0 leftmost pixel x coordinate
 * @param y0 top pixel y coordinate
 * @param text a null-terminated char array (a C string)
 * @param color text fill color
 * 
 * @author sethsson
*/
void drawText(unsigned int x0, unsigned int y0, char* text, unsigned char color);

/**
 * Draw a single character to the screen.
 * @param x0 leftmost pixel x coordinate
 * @param y0 top pixel y coordinate
 * @param glyph_data glyph data
 * @param color text fill color
 * 
 * @author sethsson
*/
void drawChar(unsigned int x0, unsigned int y0, unsigned int glyph_data, unsigned char color);

#endif