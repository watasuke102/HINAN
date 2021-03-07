/*
 * C言語ほぼそのまま
 */

#include <h8/reg3067.h>
#include <mes2.h>

void myWait() {
  int i, j;
  for (i = 0; i < 300; i++)
    for (j = 0; j < 100; j++)
      ;
}

int main(void) {
  P4DDR = 0xff; // P4を出力用に
  P1DR  = 0xf0;

  while (true) {
    // for (int i = 0; i < 1000; i++) {
    P4DR = 0x11;
    myWait();
    P4DR = 0x22;
    myWait();
    P4DR = 0x34;
    myWait();
    P4DR = 0x48;
    myWait();
  }

  return 0;
}
