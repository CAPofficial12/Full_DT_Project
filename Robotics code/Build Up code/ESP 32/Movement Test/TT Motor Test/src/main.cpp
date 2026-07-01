#include <Arduino.h>

int enA = 1;
int enB = 2;
int in1 = 3;
int in2 = 4;
int in3 = 5;
int in4 = 6;

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
  delay(3000);

  analogWrite(enA, 200);
  delay(3000);

  analogWrite(enA, 150);
  delay(3000);

  analogWrite(enA, 100);
  delay(3000);

  analogWrite(enA, 50);
  delay(3000);

  analogWrite(enA, 0);
  delay(3000);
}