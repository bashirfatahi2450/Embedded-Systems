#include "TrafficLight.h"
#include <chrono>
using namespace std::chrono;

static const PinName RED1  = TRAF_RED1_PIN;
static const PinName YEL1  = TRAF_YEL1_PIN;
static const PinName GRN1  = TRAF_GRN1_PIN;
static const PinName RED2  = TRAF_RED2_PIN;
static const PinName YEL2  = TRAF_YEL2_PIN;
static const PinName GRN2  = TRAF_GRN2_PIN;

TrafficLight::TrafficLight(LIGHT_SET which)
  : redLED( (which==SET1) ? TRAF_RED1_PIN : TRAF_RED2_PIN ),
    yellowLED( (which==SET1) ? TRAF_YEL1_PIN : TRAF_YEL2_PIN ),
    greenLED( (which==SET1) ? TRAF_GRN1_PIN : TRAF_GRN2_PIN ),
    t(), State(STOP), _flashHz(2.0), _yellowOn(false),
    _activeLow(which == SET2)
{
    if (which == SET1) {
        configurePin(redLED,    PullNone,  true);
        configurePin(yellowLED, PullNone,  true);
        configurePin(greenLED,  PullNone,  true);
        _activeLow = false;
    } else {
        configurePin(redLED,    OpenDrain, true);
        configurePin(yellowLED, OpenDrain, true);
        configurePin(greenLED,  OpenDrain, true);
        _activeLow = true;
    }

    flashYellow(false);             // ensure flasher is off
    // Start clean: all OFF, then drive by state machine
    writeLED(redLED,   false);
    writeLED(yellowLED,false);
    writeLED(greenLED, false);

    State = STOP;
    updateOutput();                 // <-- ensures consistent STOP on both sets
}


// --- Destructor ---
TrafficLight::~TrafficLight() {
    t.detach();
    writeLED(redLED,   false);
    writeLED(yellowLED,false);
    writeLED(greenLED, false);
}

// --- Flasher ISR (toggle logical yellow, then write via helper) ---
void TrafficLight::yellowFlashISR() {
    if (State != WARNING) return;   // defensive
    _yellowOn = !_yellowOn;
    writeLED(yellowLED, _yellowOn);
}

// --- Start/stop flasher ---
void TrafficLight::flashYellow(bool enable) {
    t.detach();
    _yellowOn = false;
    writeLED(yellowLED, false);     // steady OFF when not flashing

    if (enable) {
        double hz = (_flashHz > 0.0) ? _flashHz : 1.0;
        auto half = microseconds(static_cast<int>(0.5e6 / hz)); // toggle period
        if (half < 1ms) half = 1ms;
        t.attach(callback(this, &TrafficLight::yellowFlashISR), half);
    }
}






// Moore Machine - update outputs
void TrafficLight::updateOutput()
{
    switch (State)
    {
        case STOP:
            flashYellow(false);
            writeLED(redLED,   true);
            writeLED(yellowLED,false);
            writeLED(greenLED, false);
            break;

        case READY:
            flashYellow(false);
            writeLED(redLED,   true);
            writeLED(yellowLED,true);
            writeLED(greenLED, false);
            break;

        case GO:
            flashYellow(false);
            writeLED(redLED,   false);
            writeLED(yellowLED,false);
            writeLED(greenLED, true);
            break;

        case WARNING:
            writeLED(redLED,   false);
            writeLED(greenLED, false);
            flashYellow(true);              // yellow handled by ISR
            break;
    }
}


// Moore machine - next state logic
TrafficLight::LIGHT_STATE TrafficLight::nextState()
{
    // Update State
    switch (State)
    {
        case STOP:
            State = READY;
            break;
        case READY:
            State = GO;
            break;
        case GO:
            State = WARNING;
            break;
        case WARNING:
            State = STOP;
            break;
    }

    //As it says
    updateOutput();

    //Return the current state (for information)
    return State; 
} 

// ===== NEW PUBLIC API =====
void TrafficLight::stop() {
    State = STOP;
    updateOutput();
}

void TrafficLight::setFlashSpeed(double hz) {
    if (hz <= 0.0) hz = 1.0;
    _flashHz = hz;
    if (State == WARNING) {
        // Reconfigure ticker with the new speed
        flashYellow(true);
    }
}


double TrafficLight::getFlashSpeed() const {
    return _flashHz;
}