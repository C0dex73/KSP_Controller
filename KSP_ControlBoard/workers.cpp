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
