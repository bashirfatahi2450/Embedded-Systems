#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "mbed.h"
using namespace chrono;

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

class TrafficLight 
{
    public:
    typedef enum {STOP, READY, GO, WARNING} LIGHT_STATE;

    private:
    DigitalOut redLED;
    DigitalOut yellowLED;
    DigitalOut greenLED;
    Ticker t;
    LIGHT_STATE State;

    // --- Added: private members for flasher speed control ---
    double _flashHz;   // flasher speed in Hz (on–off cycles/sec)


    void yellowFlashISR();
    void flashYellow(bool flash);
    void updateOutput();

    

    public:
    //Constructor
    TrafficLight(PinName redPin = TRAF_RED1_PIN, PinName yellowPin = TRAF_YEL1_PIN, PinName greenPin=TRAF_GRN1_PIN); 

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