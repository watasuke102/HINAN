/*
 * C言語ほぼそのまま
 */

#include <h8/reg3067.h>
#include <mes2.h>

void myWait() {
  int i;
  for (i = 0; i < 700; i++)
    ;
}

int main(void) {
  P4DDR = 0xff; // P4を出力用に

  while (true) {

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
