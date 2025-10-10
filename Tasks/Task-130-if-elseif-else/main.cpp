#include "uop_msb.h"
using namespace uop_msb;

BusIn bus(PG_0, PG_1, PG_2, PG_3);

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    int count = 100;
    bus[2].mode(PinMode::PullDown);
    bus[3].mode(PinMode::PullDown);


    //Turn ON the 7-segment display
    disp.enable(true);

    //Update display
    disp = count;

    while (true) {
        
        //Read button without blocking
        int btnA = bus[0];     //Local to the while-loop  
        int btnB = bus[1];     //Local to the while-loop
        //Test Button A,
        if (btnA == 1) {
            greenLED = !greenLED;    //Toggle RED led
            count ++;         //Increment count
            disp = count;       //Update display
        }
        if (btnB == 1) {
            greenLED = !greenLED;    //Toggle RED led
             count --;             //Increment count
            disp = count;       //Update display
        }
        if ((btnA == 1) && (btnB == 1)) {
            count = 0;
            greenLED = 1;
        }
        else {
            greenLED = !greenLED;    //Toggle RED led

        }
       
        // Slow it down a bit (and debounce the switches)
        wait_us(100000);  
    }
}


