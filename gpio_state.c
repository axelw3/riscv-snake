// Determine direction if one button pressed. Else ignore.
unsigned char* get_dpad_state() {
    volatile int* gpio_pointer = (volatile int*) 0x040000e0;
    unsigned char dpad_state = *gpio_pointer & 0b1111;

    switch(dpad_state){
        case 0b1110:
            // höger
            return 1;
            break;
        case 0b1101:
            // vänster
            return 2;
            break;
        case 0b1011:
            // ner
            return 3;
            break;
        case 0b0111:
            // upp
            return 4;
            break;
        default:
            // no input
            return 0b0000;
    }
    }