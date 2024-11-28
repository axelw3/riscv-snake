#include "gamemap.h"

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
}