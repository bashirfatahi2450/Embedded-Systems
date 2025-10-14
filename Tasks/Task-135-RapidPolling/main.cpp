#include "uop_msb.h"
using namespace uop_msb;

BusIn buttons(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);
// DigitalIn buttonA(BTN1_PIN);    //ButtonA is synonamous with buttons[0]
// DigitalIn buttonB(BTN2_PIN);
// DigitalIn buttonC(BTN3_PIN);
// DigitalIn buttonD(BTN4_PIN);

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    volatile int count = 0;

    // This little C++ trick allows us to use BOTH BusIn and DigitalIn
    DigitalIn& buttonA = buttons[0];    //ButtonA is synonamous with buttons[0]
    DigitalIn& buttonB = buttons[1];
    DigitalIn& buttonC = buttons[2];
    DigitalIn& buttonD = buttons[3];

    //Configure switches
    buttonC.mode(PullDown);
    buttonD.mode(PullDown);

    //Turn ON the 7-segment display
    disp.enable(true);

   
    int btnA_curr;
    int btnB_curr;
    
    // Latches for one-shot per press
uint8_t btnA_prev = 0;
uint8_t btnB_prev = 0;
uint8_t both_prev = 0;

while (true) {
    // Assume these booleans are updated each loop: 1 = pressed, 0 = not pressed
    uint8_t a = buttonA;
    uint8_t b = buttonB;

    // --- Update display first (as in your code)
    disp = count;

    // --- Handle BOTH pressed first (edge so it triggers once)
    uint8_t both = a & b;
    if (both && !both_prev) {
        count = 0;                   // your reset action
    } else {
        // --- Handle A press (edge: now 1, previously 0)
        if (a && !btnA_prev) {
            if (count <99) { count += 1 ; }   // your A action
        }

        // --- Handle B press (edge)
        if (b && !btnB_prev) {
            if (count > 0) { count -= 1; } // your B action
        }
    }

    // The previous values are now set to the current
    btnA_prev = a;
    btnB_prev = b;
    both_prev = both;

    // Small pacing (and mild debounce). Keep it short so you don’t miss presses.
    wait_us(2000);  // ~2 ms; bump to 10–20 ms if you see bounce
}

}





