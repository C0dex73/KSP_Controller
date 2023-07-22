#ifndef WORKERS_h
#define WORKERS_h

#include <Arduino.h>
#include "pins.h"



//Startup module

class Abort : public DigitalPin {
	public:
		Abort(int _pin) : DigitalPin(_pin, INPUT_PULLUP) {};
		void Action();
};

class Startup : public DigitalPin {
	public:
		Startup(int _pin) : DigitalPin(_pin, INPUT) {};
		void Action();
};

class Staging : public DigitalPin {
	public:
		Staging(int _pin) : DigitalPin(_pin, INPUT_PULLUP) {};
		void Action();
};

//Action module

class ActionGroup : public DigitalPin {
	public:
		String AG;

		ActionGroup(int _pin, String _AG) :
			AG {_AG},
			DigitalPin(_pin, INPUT) {};
		void Action();
};

enum resCombo { None, A33K, B100K, C150K, AB25K, BC60K, CA27K, ABC21K };

class ActionGroupMultiple : public AnalogPin {
	private:
		void ChangeAGState(int _AGState[3]);

	public :
		resCombo comboState;

		String AG[3];
		int AGState[3] = {0, 0, 0};
		int oldAGState[3] = {0, 0, 0};

		ActionGroupMultiple(int _pin, String _AG[3]) :
			AG { _AG[0], _AG[1], _AG[2]},
			AnalogPin(_pin) {};
		void Action();
};

//Maneuver module
class ManeuverController : public DigitalPin {
	public:
		String msg;
		AnalogPin sensibilityPin;

		ManeuverController(int _pin, String _msg, AnalogPin _sensibilityPin) :
			msg { _msg },
			sensibilityPin { _sensibilityPin },
			DigitalPin(_pin, INPUT_PULLUP) {};
		void Action();
};
#define NOMANEUVER ManeuverController(0,"", AnalogPin(0))

class Goto : public DigitalPin {
	public:
		Goto(int _pin) : DigitalPin(_pin, INPUT_PULLUP) {};
		void Action();
};

//Rotation module

class SAS : public DigitalPin {
	public:
		SAS(int _pin) : DigitalPin(_pin, INPUT) {};
		void Action();
};

class Thrust : public AnalogPin {
	public:
		float thrust = 0.00;
		float oldThrust = 0.00;

		Thrust(int _pin) : AnalogPin(_pin) {};
		void Action();
};

#endif