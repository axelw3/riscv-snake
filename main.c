#include <stdio.h>
#include "accele.h"
#include "dtekv-lib.h"

void handle_interrupt(unsigned cause) 
{}

int main() {
    while(1) {
        volatile short* accelePointer = (short*) 0x32;
        display_2_dig_short((short) 0, (short) ((*accelePointer & 0b11111111) % 100));
    }
    return 0;
};