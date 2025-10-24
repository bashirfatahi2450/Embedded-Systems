#include "mbed.h"


PwmOut   led(PB_0);       // PWM output for LED
AnalogIn pot(PA_0);       // Potentiometer input (ADC 0.0 .. 1.0)

int main() {
    printf("Program Starting...\n");

    // Set PWM frequency (1 kHz)
    led.period(0.001f);

    // Polling interval
    const int POLL_US = 100000; // 100 ms

    float potValue = 0.0f;    // ADC normalized value (0.0 .. 1.0)
    float brightness = 0.0f;  // PWM duty cycle (0.0 .. 1.0)

    while (true) {
        // Step 1: Read the potentiometer (ADC normalized value)
        potValue = pot.read();   // returns 0.0 to 1.0

        // Step 2: Map potentiometer position directly to brightness
        brightness = potValue;

        // Step 3: Write PWM duty to LED
        led.write(brightness);

        // Debug output
        printf("Potentiometer: %.3f  -> LED Brightness: %.2f\n", potValue, brightness);

        // Step 4: Wait 100 ms before next read
        wait_us(POLL_US);
    }
}

