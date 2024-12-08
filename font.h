#ifndef FONT_H
#define FONT_H

/**
 * Width of a font character.
*/
#define FCHAR_W 5

/**
 * Height of a font character.
*/
#define FCHAR_H 6

/**
 * Get raw character pixel data.
 * @param ch character to fetch
 * @return raw pixel data
 * 
 * @author sethsson
*/
unsigned int getCharData(char ch);

#endif