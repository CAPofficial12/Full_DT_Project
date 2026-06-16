#include <Arduino.h>
#include <time.h>

#define LED 21
unsigned long startTime;

void setup(){
  Serial.begin(115200);
}

void loop(){
  startTime = micros();
  delay(1200);
  unsigned long timepassed = micros() - startTime;
  Serial.println(timepassed);
}