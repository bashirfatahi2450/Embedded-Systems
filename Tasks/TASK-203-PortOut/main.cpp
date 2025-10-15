#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define LEDMASK 0b0000000001001100
#define LedMASK 0b0100000010000001

// Objects
//BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
PortOut leds(PortC, LEDMASK);
PortOut LEDs(PortB, LedMASK);
int main()
{
    leds = 0;   //Binary 000
    LEDs = 0;
    while (true) {
       
        
    leds = leds ^ LEDMASK, LEDs = LEDs ^ LedMASK;  // toggle only the masked pins on both ports
    wait_us(500000);                   // 500 ms delay
    
    }    

}





