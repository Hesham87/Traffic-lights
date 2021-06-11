
#include "main.h"

void startTraffic(int);
void INIT(void);

int main()
{
    INIT();
    while (1)
    {
        startTraffic(1);
        startTraffic(2);
    }
}

void INIT(){
    UART0_init();
    PORTA_Init_Output(0x78);
    PORTC_Init_Output(0xF0);
    PORTD_Init_Output(0x0F);
    PORTB_Init_Button(0x04);
    PORTF_Init_Button(0x01);
    PORTB_Interrupt_Init();
    PORTF_Interrupt_Init();
}
void startTraffic(int trafficNumber)
{
    enum Lights
    {
        green = 0,
        yellow = 1,
        red = 2
    };

    for (volatile int counter = green; counter < 3; counter++)
    {

        if (trafficNumber == 1)
        {
            GPIO_PORTD_DATA_R = 1U << counter;
        }
        else if (trafficNumber == 2)
        {
            GPIO_PORTC_DATA_R = 1U << (counter + 4);
        }
        switch (counter)
        {
        case green:
            
            if (trafficNumber == 1)
              printUART("\n\rCARS EAST WEST");
            else if (trafficNumber == 2)
              printUART("\n\rCARS North South");
            T0_delay(5);
            break;
        case yellow:
            T0_delay(2);
            break;
        case red:
            T0_delay(1);
            break;
        default:
            break;
        }
    }
}