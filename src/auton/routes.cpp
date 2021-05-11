#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include <cmath>

using namespace vex;

float power;
float temp;
float error;
const float default_value = 40; 
const float FB_error = 40;
const float T_error = 70;

void chassis_stop()
{
  chassisLB.setBrake(vex::brakeType::brake);
  chassisLF.setBrake(vex::brakeType::brake);
  chassisRB.setBrake(vex::brakeType::brake);
  chassisRF.setBrake(vex::brakeType::brake);
  chassisLB.stop();
  chassisLF.stop();
  chassisRB.stop();
  chassisRF.stop();
}

void chassis_reset()
{
  chassisLF.resetRotation();
  chassisLB.resetRotation();
  chassisRF.resetRotation();
  chassisRB.resetRotation();
}

void forward_ (float target) {
  target -= FB_error;
  power = default_value;
  while (chassisRF.rotation(rotationUnits::raw) < target) {
    power = target - chassisRF.rotation(rotationUnits::raw);
    if (power >= default_value) {
      power = default_value;
    }
    if (chassisLF.rotation(rotationUnits::raw) > chassisRF.rotation(rotationUnits::raw)) {
      error = chassisLF.rotation(rotationUnits::raw) - chassisRF.rotation(rotationUnits::raw);
      chassisL_set(power - error);
      chassisR_set(power);
    }
    else if (chassisLF.rotation(rotationUnits::raw) < chassisRF.rotation(rotationUnits::raw)) {
      error = chassisRF.rotation(rotationUnits::raw) - chassisLF.rotation(rotationUnits::raw);
      chassisL_set(power);
      chassisR_set(power - error);
    }
    else {
      chassisL_set(power);
      chassisR_set(power);
    }
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
}

void backward_ (float target) {
  target += FB_error;
  power = default_value;
  while (chassisRF.rotation(rotationUnits::raw) > target) {
    power = target + chassisRF.rotation(rotationUnits::raw);
    if (power <= -default_value) {
      power = -default_value;
    }
    if (chassisLF.rotation(rotationUnits::raw) > chassisRF.rotation(rotationUnits::raw)) {
      error = chassisLF.rotation(rotationUnits::raw) - chassisRF.rotation(rotationUnits::raw);
      chassisL_set(power + error);
      chassisR_set(power);
    }
    else if (chassisLF.rotation(rotationUnits::raw) < chassisRF.rotation(rotationUnits::raw)) {
      error = chassisRF.rotation(rotationUnits::raw) + chassisLF.rotation(rotationUnits::raw);
      chassisL_set(power);
      chassisR_set(power - error);
    }
    else {
      chassisL_set(power);
      chassisR_set(power);
    }
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
}

void turn_right (float target) {
  target -= T_error;
  power = default_value;
  temp = default_value;
  do {
    temp = power;
    power = target - chassisRF.rotation(rotationUnits::raw);
    if (power >= default_value) {
      power = default_value;
    }
    chassisL_set(-power);
    chassisR_set(temp);
  } while (chassisRF.rotation(rotationUnits::raw) > target);
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
}

void turn_left (float target) {
  target += FB_error;
  power = -default_value;
  temp = -default_value;
  do {
    temp = power;
    power = target - chassisRF.rotation(rotationUnits::raw);
    if (power <= -default_value) {
      power = -default_value;
    }
    chassisL_set(-power);
    chassisR_set(temp);
  } while (chassisRF.rotation(rotationUnits::raw) < target);
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
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

void intake_ (bool intake) {
  if (intake) {
    intake_set(100);
  }
  else {
    intake_set(-100);
  }
}
void debug () {
  forward_(1000);
}