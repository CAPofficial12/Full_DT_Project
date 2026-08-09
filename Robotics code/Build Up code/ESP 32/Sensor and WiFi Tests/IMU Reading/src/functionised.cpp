#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

using ll = unsigned long long int;

Adafruit_MPU6050 mpu;
double angle = 0.0;
ll start, end;
void setup(){
    imu_initialsation();
}

void loop(){
    Serial.print("Gyro Rate: ");
    Serial.println(imu_get_gyro());

    Serial.print("Accel Rate: ");
    Serial.println(imu_get_accel());

    Serial.print("Angle: ");
    Serial.println(imu_get_tilt_comp());
}

void imu_initialsation(){
    if(!mpu.begin()){
        Serial.println("IMU not connected");
        while(1){
            delay(10);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
    start = micros();
    Serial.println("Initialisation Completed");
}

float imu_get_gyro(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    return g.gyro.y;
}

float imu_get_accel(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    double angle = atan2(a.acceleration.x, a.acceleration.z);
    return angle;
}

double imu_get_tilt_comp(){
    float accel_angle = imu_get_accel();
    float gyro_rate = imu_get_gyro();
    const float alpha = 0.98f;
    end = micros();
    float dt = (end - start)/1000000.0;
    start = end;
    angle = alpha*(angle + gyro_rate*dt) + (1.0 - alpha)*accel_angle;
    return angle;
}