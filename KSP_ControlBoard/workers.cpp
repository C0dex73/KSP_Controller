#include "workers.h"
#include "pins.h"

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

void ActionGroup::Action() {
	Tick();

	if (ChangingState()) {
		Serial.print("ACTION " + AG + " ");
		Serial.println(state);
	}
}

void ActionGroupMultiple::ChangeState(int _AGState[3]) {
	
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
		ChangeState(new int[3]{ 0, 0, 1 });
		break;
	case 690 ... 710:
		comboState = resCombo::B100K;
		ChangeState(new int[3]{ 0, 1, 0 });
		break;
	case 795 ... 815:
		comboState = resCombo::BC60K;
		ChangeState(new int[3]{ 0, 1, 1 });
		break;
	case 880 ... 900:
		comboState = resCombo::A33K;
		ChangeState(new int[3]{ 1, 0, 0 });
		break;
	case 905 ... 914:
		comboState = resCombo::CA27K;
		ChangeState(new int[3]{ 1, 0, 1 });
    break;
	case 915 ... 925:
		comboState = resCombo::AB25K;
		ChangeState(new int[3]{ 1, 1, 0 });
		break;
	case 930 ... 940:
		comboState = resCombo::ABC21K;
		ChangeState(new int[3]{ 1, 1, 1 });
		break;
	default:
		comboState = resCombo::None;
		ChangeState(new int[3]{ 0, 0, 0 });
	}

	for (int i = 0; i < 3; i++) {
		if (AGState[i] != oldAGState[i]) {
			Serial.print("ACTION " + AG[i] + " ");
			Serial.println(AGState[i]);
		}
	}
}