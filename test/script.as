int main(void) {
  while(true) {
    P4DR+=1;
    if(P4DR > 0xff)P4DR=0x00;
  }
  return 0;
}