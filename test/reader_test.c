/*
 * C言語ほぼそのまま
 */

#include <h8/reg3067.h>
#include <mes2.h>

void myWait() {
  return;
  int i, j;
  for (i = 0; i < 35000; i++)
    for (j = 0; j < 1000; j++)
      ;
}

int main(void) {
  P4DDR = 0xff; // Segment direction
  P5DDR = 0xf0; // Tact direction
  PBDDR = 0xff; // LED direction
  PBDR  = 0xff; // all LED turn off

  for (int i = 0; i < 4; i++) {
    P4DR = 0x8A;
    myWait();
  }

  while (true) {
    for (int i = 0; i < 500000; i++)
      ;
    P4DR = 0x11;
    myWait();
    P4DR = 0x22;
    myWait();
    P4DR = 0x34;
    myWait();
    P4DR = 0x48;
    myWait();
    PBDR = PBDR << 1;
  }

  return 0;
}
