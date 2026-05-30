#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  mpu.CalibrateGyro();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected!");
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

  mpu.getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);

  double x = RAD_TO_DEG * atan2(AcY, AcZ);
  double y = RAD_TO_DEG * atan2(-AcX, AcZ);
  double z = RAD_TO_DEG * atan2(AcY, AcX);

  Serial.print("AngleX= "); Serial.println(x);
  Serial.print("AngleY= "); Serial.println(y);
  Serial.print("AngleZ= "); Serial.println(z);
  Serial.println("-----------");

  delay(400);
}