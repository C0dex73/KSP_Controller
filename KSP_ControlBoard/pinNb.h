#ifndef PINNB_H
#define PINNB_H

#include <Arduino.h>

//multiple lcd handling
const int RS = 53;
const int D4 = 52;
const int D5 = 51;
const int D6 = 50;
const int D7 = 49;

//STARTUP MODULE
const int STARTUPPIN = 22;
const int STAGINGPIN = 23;
const int ABORTPIN = 24;

//ACTION MODULE
const int ACTIONS1TO3PIN = A0;
const int ACTIONS4TO6PIN = A1;
const int ACTIONS7TO9PIN = A2;
const int ACTION10PIN = 25;

//MANEUVER MODULE
const int MANEUVERLCDENPIN = 26;

const int MANEUVERSENSIBILITYPIN = A3;

const int PROGRADEPIN = 27;
const int RETROGRADEPIN = 28;
const int RADIALINPIN = 29;
const int RADIALOUTPIN = 30;
const int NORMALPIN = 31;
const int ANTINORMALPIN = 32;
const int TIMEADDPIN = 33;
const int TIMEREMOVEPIN = 34;

const int GOTOPIN = 35;

//MAIN ROTATION MODULE
const int ROTATEJOY_Pin[4] = { A4, A5, A6, 36 };
//TODO : #define each axis

const int SASPIN = 37;
const int THRUSTPIN = A7;

//MAIN TRANSLATION MODULE
//TODO : JOYSTICK CONTROLLER

const int LIGHTSPIN = 38;

#endif