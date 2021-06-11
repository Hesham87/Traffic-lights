#include "liberary.h"

void PORTA_Init_Output(uint8_t pins)
{
    SYSCTL_RCGCGPIO_R |= 0x01;
    while ((SYSCTL_PRGPIO_R & 0x01) == 0);
    GPIO_PORTA_AFSEL_R = 0x03;
    GPIO_PORTA_PCTL_R = 0x11;
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R = pins;
    GPIO_PORTA_DIR_R = pins;
    GPIO_PORTA_DEN_R = pins | 0x03;
    GPIO_PORTA_DATA_R |= 0x28;
}
void PORTC_Init_Output(uint8_t pins)
{
    SYSCTL_RCGCGPIO_R |= 0x04;
    while ((SYSCTL_PRGPIO_R & 0x04) == 0);
    GPIO_PORTC_LOCK_R = 0x4C4F434B;
    GPIO_PORTC_CR_R = pins;
    GPIO_PORTC_DIR_R = pins;
    GPIO_PORTC_DEN_R = pins;
}
void PORTD_Init_Output(uint8_t pins)
{
    SYSCTL_RCGCGPIO_R |= 0x08;
    while ((SYSCTL_PRGPIO_R & 0x08) == 0);
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R = pins;
    GPIO_PORTD_DIR_R = pins;
    GPIO_PORTD_DEN_R = pins;
}