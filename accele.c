#include <stdio.h>
#include "accele.h"

/* Display a number on the 7 segment display */
void set_displays(int display_number, int value){
  volatile char* seg7display = (volatile char*) (0x04000050 + 0x10 * display_number);
  switch(value){
    case 0:
      (*seg7display) = 0b01000000;
      break;
    case 1:
      (*seg7display) = 0b01111001;
      break;
    case 2:
      (*seg7display) = 0b00100100;
      break;
    case 3:
      (*seg7display) = 0b00110000;
      break;
    case 4:
      (*seg7display) = 0b00011001;
      break;
    case 5:
      (*seg7display) = 0b00010010;
      break;
    case 6:
      (*seg7display) = 0b00000010;
      break;
    case 7:
      (*seg7display) = 0b01111000;
      break;
    case 8:
      (*seg7display) = 0b00000000;
      break;
    case 9:
      (*seg7display) = 0b00010000;
      break;
    default:
      (*seg7display) = 0b01111111;
  }

  char dp = 0;
  if(display_number % 2 == 1 || display_number == 0){
    dp = 0b10000000;
  }
  (*seg7display) |= dp;

  return;
}

void display_2_dig_short(short num, short pos) {
    short first_num = num % 10;
    short second_num = num / 10;
    short display_num = pos * 2;

    set_displays((int) display_num, (int) first_num);
    set_displays((int) display_num + 1, (int) second_num);
}