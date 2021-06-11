#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>


void DIO_Init_Port_F(){
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = 0x1F;
  GPIO_PORTF_DEN_R = 0x1F;
  GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_PUR_R = 0x11;

}
