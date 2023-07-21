/*
 * USed to check resistor compatibility to use one pin for 3 buttons (not enought pins on megaAT2560 otherwise)
 * 
 * FOUND IT : 33K / 100K / 150K
 */

#define RES33K [880,900]		//
#define RES100K [690, 710]		//
#define RES150K [600, 620]      //
#define RESFULL [930, 940]
#define RES33K100K [915, 925]
#define RES100K150K [795, 815]	//
#define RES150K33K [905, 914]	//

const int READRES_Pin = A0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(analogRead(READRES_Pin));
}
