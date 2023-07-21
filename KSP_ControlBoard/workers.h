#ifndef WORKERS_h
#define WORKERS_h

#include <Arduino.h>
#include "pins.h"

enum resCombo {None,  A33K, B100K, C150K, AB25K, BC60K, CA27K, ABC21K};

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

class ActionGroup : public AnalogPin {
	public:
		
		ActionGroup(int _pin, int Nb) : AnalogPin(_pin) {};
};

class ActionGroupMultiple : public AnalogPin {
	private:
		void ChangeState(int _AGState[3]);

	public :
		
		resCombo oldComboState;
		resCombo comboState;

		int AG[3];
		int AGState[3] = {};

		ActionGroupMultiple(int _pin, int _AG[3]) :
			AG { _AG[0], _AG[1], _AG[2]},
			AnalogPin(_pin) {};
		void Action();
};

#endif