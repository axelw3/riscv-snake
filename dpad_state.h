#ifndef DPAD_STATE_H
#define DPAD_STATE_H

/**
 * Possible dpad states: up, down, left and right.
*/
enum Direction{
    UP = 0b1000,
    DOWN = 0b0100,
    LEFT = 0b0010,
    RIGHT = 0b0001
};

#endif