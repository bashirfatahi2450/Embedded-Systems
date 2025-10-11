#include "mbed.h"

PortOut lights(PortC, 0b0000000001001100);

int main()
{
    //All OFF
    lights = 0;

    while (true)
    {
        lights = 0b0000000000001100;
        wait_us(1000000);
        lights = 0b0000000001001000;
        wait_us(1000000);
        lights = 0b0000000001000100;
        wait_us(1000000);                
    }
}