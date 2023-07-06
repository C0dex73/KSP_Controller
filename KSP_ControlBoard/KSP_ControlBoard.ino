//Libraries
#include <LiquidCrystal.h>
#include "workers.h"

//multiple lcd handling
const int RS = 53;
const int D4 = 52;
const int D5 = 51;
const int D6 = 50;
const int D7 = 49;

//Startup module
Startup startup(2);
Staging staging(3);
Abort flightAbort(4);

//Action module
const int ACTIONGROUP1TO3_Pin = A0;
const int ACTIONGROUP4TO6_Pin = A1;
const int ACTIONGROUP6TO9_Pin = A2;
const int ACTIONGROUP10_Pin = 5;

//Maneuver Module
LiquidCrystal ManeuverLcd(RS, 48, D4, D5, D6, D7);

const int PROGRADEADD_Pin = 6;
const int PROGRADEREMOVE_Pin = 7;

const int RADIALADD_Pin = 8;
const int RADIALREMOVE_Pin = 9;

const int NORMALADD_Pin = 10;
const int NORMALREMOVE_Pin = 11;

const int GOTO_Pin = 12;

//no need of an old state because handled internaly
const int SENSIBILITY_Pin = A3;
int sensibility = 0.00;


//Main rotation module
//no need of an old state because handled internaly
const int ROTATEJOY_Pin[4] = {A4, A5, A6, 13};

const int SAS_Pin = 14;

const int THRUST_Pin = A7;

//Main translation module
const int TRANSLATEJOY_Pin[4] = { A8, A9, A10, 15 };

const int RCS_Pin = 16;

const int LIGHTS_Pin = 17;
const int GEARS_Pin = 18;
const int BREAKS_Pin = 19;

//Telemetric module
LiquidCrystal apPe(RS, 47, D4, D5, D6, D7);
LiquidCrystal alt(RS, 46, D4, D5, D6, D7);

const int XENONADD_Pin = 20;
const int MONOPROPADD_Pin = 21;
const int OREADD_Pin = 22;
const int ELECADD_Pin = 23;
const int SOLIDFUELADD_Pin = 24;
const int LIQUIDFUELADD_Pin = 25;
const int OXYGENADD_Pin = 26;

const int XENONREMOVE_Pin = 27;
const int MONOPROPREMOVE_Pin = 28;
const int OREREMOVE_Pin = 29;
const int ELECREMOVE_Pin = 30;
const int SOLIDFUELREMOVE_Pin = 31;
const int LIQUIDFUELREMOVE_Pin = 32;
const int OXYGENREMOVE_Pin = 33;

void Debug(){
	//Serial.println(flightAbort.state);
}

void Actions() {
	flightAbort.Action();
	startup.Action();
	staging.Action();
}

void setup() {

	//Serial
	Serial.begin(9600);
}

void loop() {
	Debug();
	Actions();
}