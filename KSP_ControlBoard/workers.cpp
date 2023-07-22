#include "workers.h"
#include "pins.h"

//Staging module

void Abort::Action() {
	Tick();

	if (Turning(ON)) {
		Serial.println("ACTION AB");
	}
}
void Startup::Action() {
	Tick();

	if (Turning(ON)) {
		Serial.println("START");
	}
	else if (Turning(OFF)) {
		Serial.println("HALT");
	}
}
void Staging::Action() {
	Tick();

	if (Turning(ON)) {
		Serial.println("STAGE");
	}
}

//Action module

void ActionGroup::Action() {
	Tick();

	if (ChangingState()) {
		Serial.print("ACTION " + AG + " ");
		Serial.println(state);
	}
}
void ActionGroupMultiple::ChangeAGState(int _AGState[3]) {
	
	for (int i = 0; i < 3; i++) {
		oldAGState[i] = AGState[i];
		AGState[i] = _AGState[i];
	}
}
void ActionGroupMultiple::Action() {
	Tick();

	switch (state) {
	case 600 ... 620:
		comboState = resCombo::C150K;
		ChangeAGState(new int[3]{ 0, 0, 1 });
		break;
	case 690 ... 710:
		comboState = resCombo::B100K;
		ChangeAGState(new int[3]{ 0, 1, 0 });
		break;
	case 795 ... 815:
		comboState = resCombo::BC60K;
		ChangeAGState(new int[3]{ 0, 1, 1 });
		break;
	case 880 ... 900:
		comboState = resCombo::A33K;
		ChangeAGState(new int[3]{ 1, 0, 0 });
		break;
	case 905 ... 914:
		comboState = resCombo::CA27K;
		ChangeAGState(new int[3]{ 1, 0, 1 });
    break;
	case 915 ... 925:
		comboState = resCombo::AB25K;
		ChangeAGState(new int[3]{ 1, 1, 0 });
		break;
	case 930 ... 940:
		comboState = resCombo::ABC21K;
		ChangeAGState(new int[3]{ 1, 1, 1 });
		break;
	default:
		comboState = resCombo::None;
		ChangeAGState(new int[3]{ 0, 0, 0 });
	}

	for (int i = 0; i < 3; i++) {
		if (AGState[i] != oldAGState[i]) {
			Serial.print("ACTION " + AG[i] + " ");
			Serial.println(AGState[i]);
		}
	}
}

//Maneuver module

void ManeuverController::Action() {
	Tick();

	if (Turning(ON)) {
		Serial.print("MANEUVER " + msg);
		Serial.println(sensibilityPin.state);
	}
}
void Goto::Action() {
	Tick();

	if (Turning(ON)) {
		Serial.println("MANEUVER GOTO");
	}
}

//Rotation module

void SAS::Action() {
	Tick();

	if (ChangingState()) {
		Serial.print("SAS ");
		Serial.println(state);
	}
}
void Thrust::Action() {
	Tick();

	oldThrust = thrust;
	thrust = roundf(analogState * (10.00 / 1023.00))/10.00;

	if (oldThrust != thrust) {
		Serial.print("THRUST ");
		Serial.println(thrust);
	}
}