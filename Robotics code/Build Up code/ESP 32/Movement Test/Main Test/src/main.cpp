#include <Arduino.h>

#include "motors.h"
#include "servos.h"
#include "imu.h"
#include "controller.h"

void setup() {

    motors_init();
    servos_init();
    imu_init();
    controller_init();
}

void loop() {

    servos_update();

    float tilt = imu_get_tilt();

    float power = controller_update(0.0f, tilt);

    motors_set_power(power);
}