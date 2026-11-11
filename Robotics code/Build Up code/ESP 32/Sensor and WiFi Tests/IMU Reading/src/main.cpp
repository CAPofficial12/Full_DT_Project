#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
double time_p, time_c, dif;
double ax, ay, az;
double gx, gy, gz;
void setup(void) {
  Serial.begin(115200);
  Wire.begin(14, 27);


  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }

  Serial.println("MPU6050 Found!");

  //Sets the ccelerometer Range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  //Checks what the range is set to
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  //Sets Gyro range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  //Checks what the gyro range is
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  //Sets filter
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);

  //Check Filter bandwidth
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  dif = 0;
}

void loop() {
  /* Get new sensor events with the readings */
  time_p = micros();
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  ax += a.acceleration.x;
  ay += a.acceleration.y;
  az += a.acceleration.z;
  gx += g.gyro.x;
  gy += g.gyro.y;
  gz += g.gyro.z;

  /* Print out the values */
  Serial.print(">Acceleration X: ");
  Serial.print(ax);
  Serial.print(", Y: ");
  Serial.print(ay);
  Serial.print(", Z: ");
  Serial.print(az);
  Serial.println(" m/s^2");

  Serial.print(">Rotation X: ");
  Serial.print(gx);
  Serial.print(", Y: ");
  Serial.print(gy);
  Serial.print(", Z: ");
  Serial.print(gz);
  Serial.println(" rad/s");

  Serial.print(">Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" degC");

  Serial.print(", Time");
  Serial.print(micros()/100000);
  Serial.println("/s");

  Serial.println("");
  dif = (micros() - time_p)/1000000;
}