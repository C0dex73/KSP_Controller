//Libraries
#include <LiquidCrystal.h>;
#include "workers.h";
#include "pinNb.h";

//Struct modules definitions

struct StartupModule
{
	Startup startup;
	Staging staging;
	Abort flightAbort;

	void Action() {
		startup.Action();
		staging.Action();
		flightAbort.Action();
	}
};
StartupModule startupModule = {
		Startup(STARTUPPIN),
		Staging(STAGINGPIN),
		Abort(ABORTPIN),
};

struct ActionModule {
	ActionGroupMultiple AG1TO9[3];
	ActionGroup AG10;

	#define AG1TO3 0
	#define AG4TO6 1
	#define AG7TO9 2

	void Action() {
		for (int i = 0; i < 3; i++) {
			AG1TO9[i].Action();
		}
		AG10.Action();
	}
};

ActionModule actionModule = {
		ActionGroupMultiple(ACTIONS1TO3PIN, new String[3]{ "1", "2", "3" }),
		ActionGroupMultiple(ACTIONS4TO6PIN, new String[3]{ "4", "5", "6" }),
		ActionGroupMultiple(ACTIONS7TO9PIN, new String[3]{ "7", "8", "9" }),
		ActionGroup(ACTION10PIN, "10")
};

struct ManeuverModule {
	ManeuverController controllers[8];
	LiquidCrystal lcd;
	AnalogPin sensibility;
	Goto goTo;

	#define prograde 0
	#define retrograde 1
	#define radialIn 2
	#define radialOut 3
	#define normal 4
	#define antiNormal 5
	#define timeAdd 6
	#define timeRemove 7

	void Action() {
		sensibility.Tick();
		for (int i = 0; i < 8; i++) {
			controllers[i].Action();
		}
		goTo.Action();
	}

	void ControllersInit(ManeuverController _controllers[8]) {
		for (int i = 0; i < 8; i++) {
			controllers[i] = _controllers[i];
		}
	}
};
ManeuverModule maneuverModule = {
	{NOMANEUVER, NOMANEUVER, NOMANEUVER, NOMANEUVER, NOMANEUVER, NOMANEUVER, NOMANEUVER, NOMANEUVER},
	LiquidCrystal(RS, MANEUVERLCDENPIN, D4, D5, D6, D7),
	AnalogPin(MANEUVERSENSIBILITYPIN),
	Goto(GOTOPIN)
};

struct RotationModule {
	//TODO : HANDLE JOYSTICK

	SAS sas;
	Thrust thrust;

	void Action() {
		sas.Action();
		thrust.Action();
	}
};

RotationModule rotationModule = {
		SAS(SASPIN),
		Thrust(THRUSTPIN)
};

//Main rotation module



//Main translation module
const int TRANSLATEJOY_Pin[4] = { A8, A9, A10, 15 };

const int RCS_Pin = 16;


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

	//Serial.print(actionModule.AG1TO9[0].AGState[0]);
	//Serial.print(actionModule.AG1TO9[0].AGState[1]);
	//Serial.println(actionModule.AG1TO9[0].AGState[2]);

	Serial.println(rotationModule.thrust.thrust);
}

void Actions() {
	//Startup
	startupModule.Action();

	//Action
	actionModule.Action();

	//Maneuver
	maneuverModule.Action();

	//Rotation
	rotationModule.Action();
}

void setup() {
	//Serial
	Serial.begin(9600);

	maneuverModule.ControllersInit(new ManeuverController[8]{ 
		ManeuverController(PROGRADEPIN, "PR ", maneuverModule.sensibility),
		ManeuverController(RETROGRADEPIN, "PR -", maneuverModule.sensibility),
		ManeuverController(RADIALINPIN, "RD ", maneuverModule.sensibility),
		ManeuverController(RADIALOUTPIN, "RD -", maneuverModule.sensibility),
		ManeuverController(NORMALPIN, "NO ", maneuverModule.sensibility),
		ManeuverController(ANTINORMALPIN, "NO -", maneuverModule.sensibility),
		ManeuverController(TIMEADDPIN, "TIME ", maneuverModule.sensibility),
		ManeuverController(TIMEREMOVEPIN, "TIME -", maneuverModule.sensibility)
	});

}

void loop() {
	Debug();
	Actions();
}