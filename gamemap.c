#include "gamemap.h"

const signed char MAP_W = SCR_W / TILE_SIZE;
const signed char MAP_H = SCR_H / TILE_SIZE;

unsigned char map[(SCR_W / TILE_SIZE) * (SCR_H / TILE_SIZE)];

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