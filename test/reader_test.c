int16 P1DDR = 0x00;
int16 P2DDR = 0x00;
int16 P3DDR = 0x00;
int16 P4DDR = 0x00;
int16 P5DDR = 0x00;
int16 P6DDR = 0x00;
int16 P7DDR = 0x00;
int16 P8DDR = 0x00;
int16 P9DDR = 0x00;
int16 PADDR = 0x00;
int16 PBDDR = 0x00;
int16 P1DR  = 0x00;
int16 P2DR  = 0x00;
int16 P3DR  = 0x00;
int16 P4DR  = 0x00;
int16 P5DR  = 0x00;
int16 P6DR  = 0x00;
int16 P7DR  = 0x00;
int16 P8DR  = 0x00;
int16 P9DR  = 0x00;
int16 PADR  = 0x00;
int16 PBDR  = 0x00;
/*
 * C言語ほぼそのまま
 */

//#include <h8/reg3067.h>
//#include <mes2.h>

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
