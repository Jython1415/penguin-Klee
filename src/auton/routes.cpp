#include "vex.h"
#include "robot-config.h"
#include "motors.h"

using namespace vex;

float power;
float temp;
const float default_value = 50; 
const float FB_error = 60;
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
    chassisL_set(power);
    chassisR_set(power);
  }  
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
  rollerT.stop();
  rollerB.stop();
}

void forward_ (float target, bool intake) {
  target -= FB_error;
  power = 50;
  while (chassisRF.rotation(rotationUnits::raw) < target) {
    power = target - chassisRF.rotation(rotationUnits::raw);
    if (power >= 50) {
      power = 50;
    }
    chassisL_set(power);
    chassisR_set(power);
    if (intake) {
      intake_set(100);
    }
    else {
      intake_set(-100);
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
  power = -default_value;
  temp = -default_value;
  do {
    temp = power;
    power = target + chassisRF.rotation(rotationUnits::raw);
    if (power <= -default_value) {
      power = -default_value;
    }
    chassisL_set(power);
    chassisR_set(temp);
  } while (chassisRF.rotation(rotationUnits::raw) > target);
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
}

void backward_ (float target, bool intake) {
  target += FB_error;
  power = -default_value;
  temp = -default_value;
  do {
    temp = power;
    power = target + chassisRF.rotation(rotationUnits::raw);
    if (power <= -default_value) {
      power = -default_value;
    }
    chassisL_set(power);
    chassisR_set(temp);
    if (intake) {
      intake_set(100);
    }
    else {
      intake_set(-100);
    }
  } while (chassisRF.rotation(rotationUnits::raw) > target);
  chassis_stop();
  intakeL.stop();
  intakeR.stop();
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

void turn_right (float target, bool intake) {
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
    if (intake) {
      intake_set(100);
    }
    else {
      intake_set(-100);
    }
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

void turn_left (float target, bool intake) {
  target -= T_error;
  power = -default_value;
  temp = -default_value;
  do {
    temp = power;
    power = -target + chassisRF.rotation(rotationUnits::raw);
    if (power <= -default_value) {
      power = -default_value;
    }
    chassisL_set(-power);
    chassisR_set(temp);
    if (intake) {
      intake_set(100);
    }
    else if (!intake) {
      intake_set(-100);
      rollerB_set(-100);
    }
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

void route_1 () {
  cycle(400, 100);
  forward_(1700);
  chassis_reset();
  task::sleep(100);
  turn_left(600);
  chassis_reset();
  task::sleep(200);
  forward_(2200);
  cycle(600, 100);
  chassis_reset();
  backward_(-800, false);
  task::sleep(100);
  turn_right(1200, false);
}

// forward +
// backward -
// right turn +
// left turn -

void route_2 () {
  cycle(400, 100);
  forward_(1600, true);
  task::sleep(100);
  turn_left(2000, true);
  task::sleep(100);
}

void debug () {
  turn_left(-1000);
  turn_right(-1000);
}