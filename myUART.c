#include"liberary.h"
void UART0_init()
{
  SYSCTL_RCGCUART_R |= 0x01;
  UART0_CTL_R &= ~0x01;
  //9,600 braud rate
  //IBRD= int(16 000 000/ 16 *9600) = int(104.16667)
  UART0_IBRD_R = 104;
  //FBRD= round(0.16667*64) = 11
  UART0_FBRD_R = 11;
  UART0_LCRH_R = 0x60;
  UART0_CC_R = 0x00;
  UART0_CTL_R = (1 << 0) | (1 << 8) | (1 << 9);
}
void UART0_printChar(char c)
{
  while ((UART0_FR_R & (1 << 5)) != 0);
  UART0_DR_R = c;
}
void printUART(char *string){
    while (*string)
  {
    UART0_printChar(*(string++));
  }
}