int rPin = A15;

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(rPin));
}
