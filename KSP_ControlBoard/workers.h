#ifndef WORKERS_h
#define WORKERS_h

#include <Arduino.h>
#include "pins.h"

class Abort : public DigitalPin {
	public:
		Abort(int pin) : DigitalPin(pin, INPUT_PULLUP) {};
		void Action();
};

class Startup : public DigitalPin {
	public:
		Startup(int pin) : DigitalPin(pin, INPUT) {};
		void Action();
};

class Staging : public DigitalPin {
	public:
		Staging(int pin) : DigitalPin(pin, INPUT_PULLUP) {};
		void Action();
};

#endif
