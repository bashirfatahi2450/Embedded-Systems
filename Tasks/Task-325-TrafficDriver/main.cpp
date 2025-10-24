#include "mbed.h"
#include "TrafficLight.h"

TrafficLight lights;
DigitalIn sw(USER_BUTTON);

TrafficLight::LIGHT_STATE s;

int main()
{

    int presses = 0;
    double flashHz = 2.0;   // default flasher speed
    while (true) {

        //Wait for switch press
        while (sw==0);

        //Update lights
        presses++;
        s = lights.nextState();

        // If we just entered WARNING, apply/print current flash speed
        if (s == TrafficLight::WARNING) {
            lights.setFlashSpeed(flashHz);
            printf("Entered WARNING: flash @ %.1f Hz (get=%.1f)\n",
                   flashHz, lights.getFlashSpeed());
        }

        // --- Test new APIs on specific presses ---
        if (presses == 5) {
            flashHz = 5.0;
            lights.setFlashSpeed(flashHz);
            printf("[TEST] setFlashSpeed(%.1f) -> getFlashSpeed()=%.1f\n",
                   flashHz, lights.getFlashSpeed());
        } else if (presses == 7) {
            printf("[TEST] stop() called -> should be solid RED now\n");
            lights.stop();
        } else if (presses == 9) {
            flashHz = 1.0;
            lights.setFlashSpeed(flashHz);
            printf("[TEST] setFlashSpeed(%.1f) -> getFlashSpeed()=%.1f\n",
                   flashHz, lights.getFlashSpeed());
        }

        //Debounce switch
        wait_us(300000);

        //Wait for switch release
        while (sw==1);

        //Switch debounce
        wait_us(300000);
        
    }
}

