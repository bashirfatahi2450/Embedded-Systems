#include "uop_msb.h"
using namespace uop_msb;

// Inputs
DigitalIn SW2(BTN1_PIN);
DigitalIn SW3(BTN2_PIN);

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Timers (modified version from Timer)
TimerCompat tmr_flash;

// THE CODE BELOW IS NOT A SOLUTION
//
// IT IS FUNDAMENTALLY FLAWED (AND INCOMPLETE)
//
//
// --- Timing ---
constexpr auto DEBOUNCE   = 20ms;   // 10–50ms typical
constexpr auto YEL_PERIOD = 500ms;  // blink every 500ms

TimerCompat tmr;

int main()
{

    tmr.start();

    // Yellow scheduler
    auto nextYel = tmr.elapsed_time() + YEL_PERIOD;

    // Simple per-switch state
    constexpr int PRESSED_LEVEL = 1;

    // SW2 (RED)
    int  sw2_last = SW2.read();                  // last stable level
    bool sw2_press_seen = false;                 // saw the press yet?
    auto sw2_last_change = tmr.elapsed_time();   // last time we accepted a change

    // SW3 (GREEN)
    int  sw3_last = SW3.read();
    bool sw3_press_seen = false;
    auto sw3_last_change = tmr.elapsed_time();




    while (true) {

       
        auto now = tmr.elapsed_time();

        // --- Yellow blink ---
        if (now >= nextYel) {
            ledYel = !ledYel;
            nextYel += YEL_PERIOD;
        }

        // --- SW2 -> RED (debounced, non-blocking) ---
        {
            int raw = SW2.read();
            // only accept changes after debounce time
            if (raw != sw2_last && (now - sw2_last_change) >= DEBOUNCE) {
                sw2_last = raw;
                sw2_last_change = now;

                if (raw == PRESSED_LEVEL) {
                    sw2_press_seen = true;       // pressed edge
                } else if (sw2_press_seen) {
                    ledRed = !ledRed;            // release after valid press => toggle
                    sw2_press_seen = false;
                }
            }
        }

        // --- SW3 -> GREEN (debounced, non-blocking) ---
        {
            int raw = SW3.read();
            if (raw != sw3_last && (now - sw3_last_change) >= DEBOUNCE) {
                sw3_last = raw;
                sw3_last_change = now;

                if (raw == PRESSED_LEVEL) {
                    sw3_press_seen = true;
                } else if (sw3_press_seen) {
                    ledGrn = !ledGrn;
                    sw3_press_seen = false;
                }
            }
        }

       

        
    }
}





