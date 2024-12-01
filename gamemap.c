#include "gamemap.h"
#include "vga.h"

const signed char MAP_W = SCR_W / TILE_SIZE;
const signed char MAP_H = SCR_H / TILE_SIZE;

unsigned char map[(SCR_W / TILE_SIZE) * (SCR_H / TILE_SIZE)];

void mSet(signed char *i, enum TileData newState){
    map[MAP_W * i[1] + i[0]] = (unsigned char) newState;
    
    switch(newState){
        case EMPTY:
            fillSquare(i[0] * TILE_SIZE, i[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x00);
            break;
        case APPLE:
            fillSquare(i[0] * TILE_SIZE, i[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE, APPLE_COLOR);
            break;
        case SHEAD:
            fillSquare(i[0] * TILE_SIZE, i[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE, HEAD_COLOR);
            break;
        default:
            fillSquare(i[0] * TILE_SIZE, i[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE, TAIL_COLOR);
            break;
    }
}

enum TileData mTrDir(enum Direction dir){
    switch(dir){
        case LEFT:
            return SBONL;
        case RIGHT:
            return SBONR;
        case DOWN:
            return SBOND;
        case UP:
            return SBONU;
    }
    return EMPTY;
}