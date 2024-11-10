unsigned char LAST_BUTTONSTATE = 0b0000;
unsigned char MOVE_DIRECTION = 0;

void updateButtonState(const unsigned char newState){
    unsigned char changedBtns = LAST_BUTTONSTATE ^ newState; // bitwise XOR
    switch(changedBtns){
        case 0b0001:
            // höger
            MOVE_DIRECTION = 0;
            break;
        case 0b0010:
            // vänster
            MOVE_DIRECTION = 1;
            break;
        case 0b0100:
            // ner
            MOVE_DIRECTION = 2;
            break;
        case 0b1000:
            // upp
            MOVE_DIRECTION = 3;
            break;
        default:
    }
    LAST_BUTTONSTATE = newState;
    return;
}

unsigned char get_dpad_state() {
    unsigned char changedBtns = LAST_BUTTONSTATE ^ *((volatile int*) 0x040000e0);
    switch(changedBtns){
    case 0b0001:
        // höger
        if ((LAST_BUTTONSTATE & 0b1) == 0) {
            MOVE_DIRECTION = 1;
        } else {
        MOVE_DIRECTION = 0;
        }

        break;
    case 0b0010:
        // vänster
        MOVE_DIRECTION = 1;
        break;
    case 0b0100:
        // ner
        MOVE_DIRECTION = 2;
        break;
    case 0b1000:
        // upp
        MOVE_DIRECTION = 3;
        break;
    default:

    return MOVE_DIRECTION;
    }