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

#endif