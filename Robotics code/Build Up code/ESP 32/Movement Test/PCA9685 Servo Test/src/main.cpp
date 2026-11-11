#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define ServoMin 1364
#define ServoMax 2728

int Signal_Conv(double theta, int angle) {
  theta = theta/angle + 1/2;
  int diff = ServoMax - ServoMin;
  diff *= theta;
  return map(angle, -135, 135, ServoMin, ServoMax);
}

void setup() {
  Serial.begin(115200);
  Serial.println("PCA9685 Test Begin...");

  Wire.begin();
  pwm.begin();

  pwm.setPWMFreq(333);
  delay(100);
}

void loop() {
  //-135 degrees
  pwm.setPWM(15, 0, Signal_Conv(-135, 270));
  delay(1000);

  //0 degrees
  pwm.setPWM(15, 0, Signal_Conv(-135, 270));
  delay(1000);

  // 135 degrees
  pwm.setPWM(15, 0, Signal_Conv(-135, 270));
  delay(1000);
}