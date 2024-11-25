#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "vga.h"
#include "dpad_state.h" // enums cannot be forward-declared

#if(SCR_W % 16 != 0)
#error
#endif

#define TILE_SIZE 16

const signed char   MAP_W = SCR_W / TILE_SIZE,
                    MAP_H = SCR_H / TILE_SIZE;

unsigned char map[(SCR_W / TILE_SIZE) * (SCR_H / TILE_SIZE)]; // 300 bytes

/**
 * Mutually exclusive tile states/data.
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
*/
inline void mSet(signed char *i, enum TileData newState){
    map[MAP_W * i[1] + i[0]] = (unsigned char) newState;
}

/**
 * Get data for a game tile.
 * @param i a two-element byte array containing the x/y position
 * @return tile data for the specified position
*/
inline enum TileData mGet(signed char *i){
    return (enum TileData) map[MAP_W * i[1] + i[0]];
}

/**
 * Translate a `Direction` direction to the corresponding directed snake tail component.
 * @param dir a `Direction`, i.e. either `LEFT`, `RIGHT`, `DOWN` or `UP`
*/
enum TileData mTrDir(enum Direction dir);

#endif