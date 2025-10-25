#include "mbed.h"
#include "TrafficLight.h"
DigitalIn sw(USER_BUTTON);
TrafficLight set1(TrafficLight::SET1);
TrafficLight set2(TrafficLight::SET2);
TrafficLight::LIGHT_STATE s;









// Create the three LEDs (open-drain, output mode, default OFF = 1)
DigitalInOut red(TRAF_RED2_PIN,  PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);
DigitalInOut yel(TRAF_YEL2_PIN,  PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);
DigitalInOut grn(TRAF_GRN2_PIN,  PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 1);

int main() {
   
    printf("TrafficLight test (press button to advance)\n");

    ThisThread::sleep_for(20ms);  // tiny settle (OE/EN, pull-ups)
    set1.stop();
    set2.stop();
    set1.setFlashSpeed(2.0);
    set2.setFlashSpeed(2.0);

    int last = sw.read();
    const int DEB = 30000; // 30 ms

    while (true) {
        int cur = sw.read();
        if (last == 1 && cur == 0) {           // falling edge = press
            wait_us(DEB);
            if (sw.read() == 0) {
                set1.nextState();
                set2.nextState();
                while (sw.read() == 0) {}
                wait_us(DEB);
            }
        }
        last = cur;
        wait_us(2000);
    }
}




   
    


