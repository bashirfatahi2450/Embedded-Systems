#include "mbed.h"

// DigitalOut redLED(PC_2,0);
// DigitalOut yellowLED(PC_3,0);
// DigitalOut greenLED(PC_6,0);
BusOut leds(PC_2, PC_3, PC_6);

// main() runs in its own thread in the OS
int main()
{
    while (true) {

        //For-Loop

        for ( int n=1; n<=7; n = n+2) {
            printf("n=%d\n", n);
            leds = n;
            wait_us(250000);
        }

        //2s pause
        wait_us(2000000);
    }
}

