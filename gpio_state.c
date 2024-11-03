unsigned char LAST_GPIO_BUTTONSTATE = 0b0000;

//  Returns the change for one call when change is detected. 
//  Storage of state change is left to caller.
//  OBS!!! state 0 is reservved for no change.
int get_button_state_change(){
    unsigned char move_direction = 0;
    volatile unsigned char* current_state = (unsigned char*) 0x040000e0;
    unsigned char changedBtns = LAST_GPIO_BUTTONSTATE ^ *current_state; // bitwise XOR
    switch(changedBtns){
        case 0b0001:
            // höger
            move_direction = 1;
            break;
        case 0b0010:
            // vänster
            move_direction = 2;
            break;
        case 0b0100:
            // ner
            move_direction = 3;
            break;
        case 0b1000:
            // upp
            move_direction = 4;
            break;
        default:
            // no change
            // move_direction = 0;
    }
    LAST_GPIO_BUTTONSTATE = current_state;
    return move_direction;
}