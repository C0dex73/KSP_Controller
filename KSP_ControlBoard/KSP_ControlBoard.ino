//Libraries
#include <LiquidCrystal.h>

//Startup module
const int STARTUP_Pin = 53;
const int STAGING_Pin = 52;
const int ABORT_Pin = 51;

int startupState = 0;
int oldStartupState = 0;
int stagingState = 0;
int oldStatgingState = 0;
int abortState = 0;
int oldAbortState = 0;

//Action module
const int ACTIONGROUP1_Pin = 41;
const int ACTIONGROUP2_Pin = 42;
const int ACTIONGROUP3_Pin = 43;
const int ACTIONGROUP4_Pin = 44;
const int ACTIONGROUP5_Pin = 45;
const int ACTIONGROUP6_Pin = 46;
const int ACTIONGROUP7_Pin = 47;
const int ACTIONGROUP8_Pin = 48;
const int ACTIONGROUP9_Pin = 49;
const int ACTIONGROUP10_Pin = 50;

int actionGroup1State = 0;
int oldActionGroup1State = 0;

int actionGroup2State = 0;
int oldActionGroup2State = 0;

int actionGroup3State = 0;
int oldActionGroup3State = 0;

int actionGroup4State = 0;
int oldActionGroup4State = 0;

int actionGroup5State = 0;
int oldActionGroup5State = 0;

int actionGroup6State = 0;
int oldActionGroup6State = 0;

int actionGroup7State = 0;
int oldActionGroup7State = 0;

int actionGroup18tate = 0;
int oldActionGroup8State = 0;

int actionGroup9State = 0;
int oldActionGroup9State = 0;

int actionGroup10State = 0;
int oldActionGroup10State = 0;

//Maneuver Module
LiquidCrystal ManeuverLcd(35, 36, 37, 38, 39, 40);

const int PROGRADEADD_Pin = 34;
const int PROGRADEREMOVE_Pin = 33;

int progradeAddState = 0;
int oldProgradeAddState = 0;
int progradeRemoveState = 0;
int oldProgradeRemoveState = 0;

const int RADIALADD_Pin = 32;
const int RADIALREMOVE_Pin = 31;

int radialAddState = 0;
int oldRadialAddState = 0;
int radialRemoveState = 0;
int oldRadialRemoveState = 0;

const int NORMALADD_Pin = 30;
const int NORMALREMOVE_Pin = 29;

int normalAddState = 0;
int oldNormalAddState = 0;
int normalRemoveState = 0;
int oldNormalRemoveState = 0;

const int GOTO_Pin = 28;
int gotoState = 0;
int oldGotoState = 0;

//no need of an old state because handled internaly
const int SENSIBILITY_Pin = A15;
float sensibility = 0.00;


//Main rotation module
//no need of an old state because handled internaly
const int JOYSTICK1X_Pin = A14;
const int JOYSTICK1Y_Pin = A13;
const int JOYSTICK1R_Pin = A12;

float joystick1X = 0.00;
float joystick1Y = 0.00;
float joystick1R = 0.00;

const int SAS_Pin = 27;
int sasState = 0;
int oldSasState = 0;

const int THRUST_Pin = A11;
float thrust = 0.00;
float OldThrust = 0.00

//Telemetric module
LiquidCrystal apPe(26, 25, 24, 23, 22, 21);
LiquidCrystal alt(20, 19, 18, 17, 16, 15);

const int XENONADD_Pin = 14;
const int MONOPROPADD_Pin = 13;
const int OREADD_Pin = 12;
const int ELECADD_Pin = 11;
const int SOLIDFUELADD_Pin = 10;
const int LIQUIDFUELADD_Pin = 9;
const int OXYGENADD_Pin = 8;

const int XENONREMOVE_Pin = 7;
const int MONOPROPREMOVE_Pin = 6;
const int OREREMOVE_Pin = 5;
const int ELECREMOVE_Pin = 4;
const int SOLIDFUELREMOVE_Pin = 3;
const int LIQUIDFUELREMOVE_Pin = 2;
const int OXYGENREMOVE_Pin = 1;

int xenonLevelPercent = 0;
int monopropLevelPercent = 0;
int oreLevelPercent = 0;
int elecLevelPercent = 0;
int soldiFuelLevelPercent = 0;
int liquidFuelLevelPercent = 0;
int oxygenLevelPercent = 0;

void setup(){
  Serial.begin(9600);
  
  //Telemetric module
  apPe.begin(16,2);
  alt.begin(16,2);

  pinMode(XENONADD_Pin, OUTPUT);
  pinMode(MONOPROPADD_Pin, OUTPUT);
  pinMode(OREADD_Pin, OUTPUT);
  pinMode(ELECADD_Pin, OUTPUT);
  pinMode(SOLIDFUELADD_Pin, OUTPUT);
  
}

void loop(){}
