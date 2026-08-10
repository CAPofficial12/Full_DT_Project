#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

double angle = 0.0, AngleC = 0.0, AngleK = 0.0;
u_int32_t start, end;
double dt = 0;
float P[2][2] = {{0.0f, 0.0f}, {0.0f, 0.0f}};
double bias = 0.0;
double rate = 0.0;

const double Q_Angle = 0.001f;
const double Q_bias = 0.003f;
const double R_measure = 0.03f;

void setup(){
    Serial.begin(115200);
    imu_initialsation();
}

void loop(){
    mpu.getEvent(&a, &g, &temp);

    end = micros();
    dt = (end - start)/1000000.0;
    start = end;

    Serial.print("Gyro Rate: ");
    Serial.println(imu_get_gyro());

    Serial.print("Accel Rate: ");
    Serial.println(imu_get_accel());

    Serial.print("Angle Comp: ");
    Serial.println(imu_get_tilt_comp());

    Serial.print("Angle Kalman: ");
    Serial.println(imu_get_tilt_kalman());

    Serial.print("dt: ");
    Serial.println(dt);

    angle = (AngleC + AngleK)/2;
    Serial.println();
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
    double angleG = angle + g.gyro.y * dt * 180/PI;
    return angleG;
}

float imu_get_accel(){
    double angleA = atan2(a.acceleration.x, a.acceleration.z);
    angleA *= 180/PI;
    return angleA;
}

double imu_get_tilt_comp(){
    float accel_angle = imu_get_accel();
    float gyro_angle = imu_get_gyro();

    const float alpha = 0.98;
    AngleC = alpha*(gyro_angle) + (1.0 - alpha)*accel_angle;
    return AngleC;
}

double imu_get_tilt_kalman() {
    // --- PREDICT step ---
    rate = g.gyro.y * 180.0 / PI;
    rate -= bias;
    AngleK += dt * rate;
    // Update error covariance matrix
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_Angle); // Q_angle
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt; // Q_bias

    // --- UPDATE step ---
    float S = P[0][0] + R_measure; // R_measure (trust in accelerometer)
    float K[2]; 
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    float y = imu_get_accel() - AngleK; // Innovation (difference between prediction and measurement)
    AngleK += K[0] * y;
    bias += K[1] * y;

    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return AngleK;
}