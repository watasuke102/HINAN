// reader_test.cpp
//
#include <h8/reg3067.h>
#include <mes2.h>

int main(void) {
  PBDDR = 0xff; // Set Port4 to output
  P2DDR   =   0x00; // Set PortB to input

  /*
   * Set PBDR
   */
  PBDR = 0x0f;
  return 0;
}
