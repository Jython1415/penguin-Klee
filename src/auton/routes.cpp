#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include <cmath>

using namespace vex;

float power;
float temp;
float error;
const float default_value = 40; 
const float error_rate = 0.5;
const float turn_error_rate = 0.45;
const float FB_error = 40;
const float T_error = 70;
const float rollerB_power = 10;

void chassis_stop() {
  chassisLB.setBrake(vex::brakeType::brake);
  chassisLF.setBrake(vex::brakeType::brake);
  chassisRB.setBrake(vex::brakeType::brake);
  chassisRF.setBrake(vex::brakeType::brake);
  chassisLB.stop();
  chassisLF.stop();
  chassisRB.stop();
  chassisRF.stop();
}

void chassis_reset() {
  chassisLF.resetRotation();
  chassisLB.resetRotation();
  chassisRF.resetRotation();
  chassisRB.resetRotation();
}

void forward_ (float target, int intake) {
  target -= FB_error;
  power = default_value;
  while (chassisRF.rotation(rotationUnits::raw) < target && chassisLF.rotation(rotationUnits::raw) < target) {
    power = target - chassisRF.rotation(rotationUnits::raw);
    if (power >= default_value) {
      power = default_value;
    }
    if (chassisLF.rotation(rotationUnits::raw) > chassisRF.rotation(rotationUnits::raw)) {
      error = chassisLF.rotation(rotationUnits::raw) - chassisRF.rotation(rotationUnits::raw);
      error *= error_rate;
      chassisL_set(power - error);
      chassisR_set(power);
    }
    else if (chassisLF.rotation(rotationUnits::raw) < chassisRF.rotation(rotationUnits::raw)) {
      error = chassisRF.rotation(rotationUnits::raw) - chassisLF.rotation(rotationUnits::raw);
      error *= error_rate;
      chassisL_set(power);
      chassisR_set(power - error);
    }
    else {
      chassisL_set(power);
      chassisR_set(power);
    }
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void backward_ (float target, int intake) {
  target = std::abs(target) - std::abs(FB_error);
  power = default_value;
  while (std::abs(chassisRF.rotation(rotationUnits::raw)) < std::abs(target) && std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(target)) {
    power = std::abs(target) - std::abs(chassisRF.rotation(rotationUnits::raw));
    if (power >= default_value) {
      power = default_value;
    }
    if (std::abs(chassisLF.rotation(rotationUnits::raw)) > std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisLF.rotation(rotationUnits::raw)) - std::abs(chassisRF.rotation(rotationUnits::raw));
      error *= error_rate;
      chassisL_set(-power + error);
      chassisR_set(-power);
    }
    else if (std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisRF.rotation(rotationUnits::raw)) - std::abs(chassisLF.rotation(rotationUnits::raw));
      error *= error_rate;
      chassisL_set(-power);
      chassisR_set(-power + error);
    }
    else {
      chassisL_set(-power);
      chassisR_set(-power);
    }
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void turn_right (float target, int intake) {
  target = std::abs(target) - std::abs(T_error);
  power = default_value;
  while (std::abs(chassisRF.rotation(rotationUnits::raw)) < std::abs(target) && std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(target)) {
    power = std::abs(target) - std::abs(chassisRF.rotation(rotationUnits::raw));
    if (power >= default_value) {
      power = default_value;
    }
    if (std::abs(chassisLF.rotation(rotationUnits::raw)) > std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisLF.rotation(rotationUnits::raw)) - std::abs(chassisRF.rotation(rotationUnits::raw));
      error *= turn_error_rate;
      chassisL_set(-power + error);
      chassisR_set(power);
    }
    else if (std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisRF.rotation(rotationUnits::raw)) - std::abs(chassisLF.rotation(rotationUnits::raw));
      error *= turn_error_rate;
      chassisL_set(-power);
      chassisR_set(power - error);
    }
    else {
      chassisL_set(-power);
      chassisR_set(power);
    }
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void turn_left (float target, int intake) {
  target = std::abs(target) - std::abs(T_error);
  power = default_value;
  while (std::abs(chassisRF.rotation(rotationUnits::raw)) < std::abs(target) && std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(target)) {
    power = std::abs(target) - std::abs(chassisRF.rotation(rotationUnits::raw));
    if (power >= default_value) {
      power = default_value;
    }
    if (std::abs(chassisLF.rotation(rotationUnits::raw)) > std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisLF.rotation(rotationUnits::raw)) - std::abs(chassisRF.rotation(rotationUnits::raw));
      error *= turn_error_rate;
      chassisL_set(power - error);
      chassisR_set(-power);
    }
    else if (std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(chassisRF.rotation(rotationUnits::raw))) {
      error = std::abs(chassisRF.rotation(rotationUnits::raw)) - std::abs(chassisLF.rotation(rotationUnits::raw));
      error *= turn_error_rate;
      chassisL_set(power);
      chassisR_set(-power + error);
    }
    else {
      chassisL_set(power);
      chassisR_set(-power);
    }
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void cycle (int time, int power) {
  roller_set(power);
  task::sleep(200);
  intake_set(power);
  roller_set(power);
  task::sleep(time - 150);
  rollerB.setBrake(brakeType::brake);
  rollerT.setBrake(brakeType::brake);
  rollerB.stop();
  rollerT.stop();
  task::sleep(150);
  intakeL.setBrake(brakeType::brake);
  intakeR.setBrake(brakeType::brake);
  intakeL.stop();
  intakeR.stop();
}

void left_only (float target, int intake) {
  int sign = target / std::abs(target); // sign changer
  power = default_value;
  while (std::abs(chassisLF.rotation(rotationUnits::raw)) < std::abs(target)) {
    chassisL_set(std::abs(power) * sign);
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void right_only (float target, int intake) {
  int sign = target / std::abs(target); // sign changer
  power = default_value;
  while (std::abs(chassisRF.rotation(rotationUnits::raw)) < std::abs(target)) {
    chassisR_set(std::abs(power) * sign);
    chassisL_set(10);
    intake_set(100 * intake);
    rollerB_set(100 * intake);
  }
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
  task::sleep(100);
  chassis_reset();
  task::sleep(30);
}

void route_1 () {
  cycle(400, 100);
  forward_(1800, 1);
  turn_right(455, 0);
  chassis_reset();
  forward_(2100, 1);
  cycle(570, 100);
  backward_(400, 0);
  cycle(400, 40);
  right_only(-1800, -1);
  backward_(700, 0);
}

void debug () {
  forward_(1000, 1);
  chassis_reset();
  backward_(1000, 2);
  turn_right(1000, 0);
  turn_left(600, 1);
  task::sleep(1000);
}