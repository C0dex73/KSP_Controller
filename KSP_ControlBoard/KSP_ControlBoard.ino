//Libraries
#include <LiquidCrystal.h>
#include "workers.h"
#include "pinNb.h"


//Startup module
Startup startup(STARTUPPIN);
Staging staging(STAGINGPIN);
Abort flightAbort(ABORTPIN);

//Action module
ActionGroupMultiple AG1To3(ACTIONS1TO3PIN, new String[3]{ "1", "2", "3" });
ActionGroupMultiple AG4To6(ACTIONS4TO6PIN, new String[3]{ "4", "5", "6" });
ActionGroupMultiple AG7To9(ACTIONS7TO9PIN, new String[3]{ "7", "8", "9" });
ActionGroup AG10(ACTION10PIN, "10");

//Maneuver Module
LiquidCrystal ManeuverLcd(RS, MANEUVERLCDENPIN, D4, D5, D6, D7);

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

	Serial.print(AG1To3.AGState[0]);
	Serial.print(AG1To3.AGState[1]);
	Serial.println(AG1To3.AGState[2]);
}

void Actions() {
	flightAbort.Action();
	startup.Action();
	staging.Action();
	AG1To3.Action();
	AG4To6.Action();
	AG7To9.Action();
	AG10.Action();
}

void setup() {
	//Serial
	Serial.begin(9600);
}

void loop() {
	Debug();
	Actions();
}
