#include "pins.h"

//Pin class constructor
Pin::Pin(){}

//****************************DIGITAL PIN****************************\\

//Constructor of the DigitalPin class
DigitalPin::DigitalPin(int _pin, int _IOmode){
	pin = _pin;
	IOmode = _IOmode;
	pinMode(pin, IOmode);
}

//Call a tick (actualizing data)
void DigitalPin::Tick() {
	oldState = state;
	state = digitalRead(pin);
}

//Specfy if the signal on the pin is turning on or off
bool DigitalPin::Turning(bool transfert) {
	return (transfert && state == HIGH && oldState == LOW) || (!transfert && state == LOW && oldState == HIGH);
}

//True if the signal if HIGH
bool DigitalPin::Pressed() {
	return state == HIGH;
}

bool DigitalPin::ChangingState() {
	return oldState != state;
}

//****************************ANALOG PIN****************************\\

AnalogPin::AnalogPin(int _pin){
	pin = _pin;
}

void AnalogPin::Tick() {
	oldState = state;
	state = analogRead(pin);
}
