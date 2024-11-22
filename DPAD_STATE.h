// DPAD_STATE_H
#ifndef DPAD_STATE_H
#define DPAD_STATE_H

/*
Possible D-PAD states. Used for communication between GPIO and game loop
*/
enum DPAD_STATE{
    UP = 0b1000,
    DOWN = 0b0100,
    LEFT = 0b0010,
    RIGHT = 0b0001
};

#endif // DPAD_STATE_H