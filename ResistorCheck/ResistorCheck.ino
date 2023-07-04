/*
 * USed to check resistor compatibility to use one pin for 3 buttons (not enought pins on megaAT2560 otherwise)
 * 
 * FOUND IT : 33K / 100K / 150K
 */

const int READRES_Pin = A0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(analogRead(READRES_Pin));
}
