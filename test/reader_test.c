/*
 * C言語ほぼそのまま
 */

#include <h8/reg3067.h>
#include <mes2.h>

void myWait() {
  int i, j;
  for (i = 0; i < 35000; i++)
    for (j = 0; j < 1000; j++)
      ;
}

int main(void) {
  P4DDR = 0xff; // P4を出力用に
  P1DR  = 0xf0;
  PBDDR = 0x93;
  PBDR  = 0xff;

  P2DR = 0x99;
  for (int i = 0; i < 4; i++) {
    P4DR = 0x8A;
    myWait();
  }

  while (true) {
    P4DR = 0x11;
    myWait();
    P4DR = 0x22;
    myWait();
    P4DR = 0x34;
    myWait();
    P4DR = 0x48;
    myWait();
    P2DR = 2 | 4;
    PBDR = PBDR << 1;
  }

  return 0;
}
