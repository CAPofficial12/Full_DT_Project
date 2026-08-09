#include <Arduino.h>

const int enA = 1;
const int enB = 2;
const int in1 = 3;
const int in2 = 4;
const int in3 = 5;
const int in4 = 6;

void setup(){

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void loop() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  delay(3000);

  analogWrite(enA, 200);
  analogWrite(enB, 200);
  delay(3000);

  analogWrite(enA, 150);
  analogWrite(enA, 255);
  delay(3000);

  analogWrite(enA, 100);
  analogWrite(enA, 255);
  delay(3000);

  analogWrite(enA, 50);
  analogWrite(enA, 255);
  delay(3000);

  analogWrite(enA, 0);
  analogWrite(enA, 0);
  delay(3000);
}