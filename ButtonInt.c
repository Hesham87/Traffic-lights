#include "liberary.h"

void delay(double sec)
{
    volatile int counter = 0;
    while (counter < ((int)(160000 * sec)))
    {
        counter++;
    }
}

void PORTB_Init_Button(uint8_t pins)
{
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R = pins;
    GPIO_PORTB_DIR_R = ~pins;
    GPIO_PORTB_PUR_R = pins;
    GPIO_PORTB_DEN_R = pins;
}
void PORTF_Init_Button(uint8_t pins)
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = pins;
    GPIO_PORTF_DIR_R = ~pins;
    GPIO_PORTF_PUR_R = pins;
    GPIO_PORTF_DEN_R = pins;
}
void PortF_Button_Handle() //PEDESTRIAN NORTH SOUTH Traffic light
{
    GPIOIntDisable(GPIO_PORTF_BASE,GPIO_INT_PIN_0);
    printUART("\n\rPEDESTRIAN NORTH SOUTH");
    uint32_t value = TimerValueGet(TIMER0_BASE, TIMER_A);
    unsigned int temp1 = GPIO_PORTD_DATA_R; // store the value in them so as to return to their previous state after intruption
    unsigned int temp2 = GPIO_PORTC_DATA_R;
    GPIO_PORTD_DATA_R = 0x04;
    GPIO_PORTC_DATA_R = 0x40;
    GPIO_PORTA_DATA_R &= ~0x20;
    GPIO_PORTA_DATA_R |= 0x40;
    T1_delay(4);
    GPIO_PORTA_DATA_R &= ~0x40;
    GPIO_PORTA_DATA_R |= 0x20;
    GPIO_PORTD_DATA_R = temp1;
    GPIO_PORTC_DATA_R = temp2;
    delay(value / 16000000.0F); // if timer0 had 0.5 sec left before being intrupted it will wait the 0.5 sec here
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
    
}
void PortB_Button_Handle() //PEDESTRIAN EAST WEST Traffic light
{
    GPIOIntDisable(GPIO_PORTB_BASE,GPIO_INT_PIN_2);
    printUART("\n\rPEDESTRIAN EAST WEST");
    uint32_t value = TimerValueGet(TIMER0_BASE, TIMER_A);
    unsigned int temp1 = GPIO_PORTD_DATA_R;
    unsigned int temp2 = GPIO_PORTC_DATA_R;
    GPIO_PORTD_DATA_R = 0x04;
    GPIO_PORTC_DATA_R = 0x40;
    GPIO_PORTA_DATA_R &= ~0x08;
    GPIO_PORTA_DATA_R |= 0X10;
    T1_delay(4);
    GPIO_PORTA_DATA_R &= ~0x10;
    GPIO_PORTA_DATA_R |= 0x08;
    GPIO_PORTB_IM_R |= 0x10;
    GPIO_PORTD_DATA_R = temp1;
    GPIO_PORTC_DATA_R = temp2;
    T0_delay(value / 16000000.0F);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_2);
}
void PORTF_Interrupt_Init()
{
    GPIOIntRegister(GPIO_PORTF_BASE, PortF_Button_Handle);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
}
void PORTB_Interrupt_Init()
{
    GPIOIntRegister(GPIO_PORTB_BASE, PortB_Button_Handle);
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_LOW_LEVEL);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);
}