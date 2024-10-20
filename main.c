#include <stdio.h>
#include "accele.h"

int main() {
    while(1) {
        volatile short* accelePointer = (short*) 0x32;
        printf("%h", (*accelePointer & 0b11111111) % 100);
    }
};