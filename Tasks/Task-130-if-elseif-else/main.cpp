#include "uop_msb.h"
using namespace uop_msb;

DigitalIn ButtonA(PG_0); //Button A
DigitalIn ButtonB(PG_1); //Button B
DigitalIn ButtonC(PG_2, PullDown); //Button C
DigitalIn ButtonD(PG_3, PullDown); //Button D

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    int count = 100;

    //Turn ON the 7-segment display
    disp.enable(true);

    //Update display
    disp = count;

    while (true) {
        
        //Read button without blocking
        int btnA = ButtonA;     //Local to the while-loop  
        int btnB = ButtonB;     //Local to the while-loop
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
       
        // Slow it down a bit (and debounce the switches)
        wait_us(100000);  
    }
}


