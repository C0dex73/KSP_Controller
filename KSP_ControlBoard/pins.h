#ifndef PIN_h
#define PIN_h

#include <Arduino.h>

#define ANALOG_MAX 1023
#define ANALOG_MIN 0
#define ON true
#define OFF false

//Handle any Pin
class Pin {
    public:
        int pin;
    
        int state = LOW;
        int oldState = LOW;

        Pin();
};

//Handle any GPIO
class DigitalPin : public Pin {
    public:

        //INPUT or OUTPUT Arduino pinMode
        int IOmode;

        //Constructor of the DigitalPin class
        DigitalPin(int _pin, int _IOmode);

        //Call a tick (actualizing data)
        void Tick();



        //Specfy if the signal on the pin is turning on or off
        bool Turning(bool transfert);
        //True if the signal if HIGH
        bool Pressed();
        //True is oldState != state
        bool ChangingState();
};

//Handle any analog input pin
class AnalogPin : public Pin {
    public:
        float analogState = 0.00;
        float oldAnalogState = 0.00f;

        AnalogPin(int _pin);

        void Tick();
};

#endif