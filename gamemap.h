#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "vga.h"
#include "dpad_state.h" // enums cannot be forward-declared

#if(SCR_W % 16 != 0 || SCR_H % 16 != 0)
#error
#endif

/**
 * Tile size, in pixels.
*/
#define TILE_SIZE 16

/**
 * Snake head color.
*/
#define HEAD_COLOR 0xFF

/**
 * Snake tail color.
*/
#define TAIL_COLOR 0xF

/**
 * Apple color.
*/
#define APPLE_COLOR 0xC3

/**
 * Number of map tiles on the x-axis.
*/
extern const unsigned char MAP_W;

/**
 * Number of map tiles on the y-axis.
*/
extern const unsigned char MAP_H;

/**
 * Total number of map tiles.
*/
extern const unsigned short MAP_S;

/**
 * Map of the current game state.
*/
extern unsigned char map[]; // 300 bytes

/**
 * Possible tile states.
 * 
 * @author sethsson
*/
enum TileData{
    EMPTY = 0,  // tom yta
    APPLE = 1,  // äpple
    SHEAD = 2,  // huvud (dit svansen leder)
    SBONU = 3,  // nästa upp
    SBONR = 4,  // nästa höger
    SBOND = 5,  // nästa ner
    SBONL = 6   // nästa vänster
};

/**
 * Set data for the specified game tile.
 * @param i a two-element byte array containing the x/y position
 * @param newState new data value
 * 
 * @author sethsson
*/
void mSet(unsigned char *i, enum TileData newState);

/**
 * Get data for a game tile.
 * @param i a two-element byte array containing the x/y position
 * @return tile data for the specified tile
 * 
 * @author sethsson
*/
inline enum TileData mGet(unsigned char *i){
    return (enum TileData) map[MAP_W * i[1] + i[0]];
}

/**
 * Get data for a game tile.
 * @param xy a one-dimensional coordinate `0 <= xy < MAP_S`
 * @return tile data for the specified tile
 * 
 * @author sethsson
*/
inline enum TileData mGetAt(unsigned short xy){
    return (enum TileData) map[xy];
}

/**
 * Translate a `Direction` direction to the corresponding directed snake tail component.
 * @param dir a `Direction`, i.e. either `LEFT`, `RIGHT`, `DOWN` or `UP`
 * 
 * @author sethsson
*/
enum TileData mTrDir(enum Direction dir);

#endif