#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "mbed.h"


#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define TRAF_RED2_PIN PC_7
#define TRAF_YEL2_PIN PC_8
#define TRAF_GRN2_PIN PC_9

class TrafficLight 
{
    public:
    typedef enum {STOP, READY, GO, WARNING} LIGHT_STATE;

    // Which set of lights (1 = push-pull, 2 = open-drain)
    typedef enum { SET1, SET2 } LIGHT_SET;

    private:
    // Use DigitalInOut so we can support open-drain for set 2
    DigitalInOut redLED;
    DigitalInOut yellowLED;
    DigitalInOut greenLED;
    Ticker t;
    LIGHT_STATE State;

    // --- Added: private members for flasher speed control ---
    double _flashHz;   // flasher speed in Hz (on–off cycles/sec)
    bool   _yellowOn;

    // Logic mapping (true = active-low e.g., open-drain)
    bool _activeLow;

    // Helpers
    inline void writeLED(DigitalInOut& pin, bool on) {
        pin.write(_activeLow ? (on ? 0 : 1) : (on ? 1 : 0));
    }
    void yellowFlashISR();
    void flashYellow(bool enable);
    void updateOutput();

    // Configure pin modes per light set
    static void configurePin(DigitalInOut& pin, PinMode mode, bool output = true) {
        pin.input();    // reset
        if (output) pin.output();
        pin.mode(mode);
    }

    

    public:
    //Constructor
   TrafficLight(LIGHT_SET which);

    //Destructor
    ~TrafficLight();

    //Advance the traffic lights to the next state
    LIGHT_STATE nextState();
    
    // ===== NEW PUBLIC API =====
    void   stop();                 // reset lights to red at any point
    void   setFlashSpeed(double);  // set yellow flasher speed in Hz
    double getFlashSpeed() const;  // read current flasher speed in Hz

};


#endif