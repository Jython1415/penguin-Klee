#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include <cmath>

using namespace vex;

float power;
float temp;
float error;
float default_value = 50; 
float error_rate = 0.5;
float turn_error_rate = 0.45;
float FB_error = 40;
float T_error = 70;

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

void forward_ (float target, float intake) {
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

void backward_ (float target, float intake) {
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

void turn_right (float target, float intake) {
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

void turn_left (float target, float intake) {
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

void left_only (float target, float intake) {
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

void right_only (float target, float intake) {
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

void route_C () {
  // pre-load shoot
  cycle(400, 100);
  // first goal
  forward_(1800, 1);
  turn_right(455, 0);
  forward_(2300, 1);
  task::sleep(100);
  cycle(300, -50);
  task::sleep(100);
  cycle(525, 100);
  backward_(450, 0);
  // second goal
  right_only(-2300, 0); 
  cycle(700, -80);
  backward_(1100, 0); // line up by wall
  default_value = 55;
  forward_(4700, 1);
  default_value = 40;
  task::sleep(100);
  turn_right(800, 1);
  task::sleep(100);
  forward_(700, 1);
  task::sleep(100);
  cycle(200, -50);
  task::sleep(100);
  cycle(500, 100);
  default_value = 50;
  backward_(1350, 0);
  // prep for third goal
  task::sleep(100);
  turn_left(830, 0);
  task::sleep(200);
  // third goal
  forward_(4000, 0.2);
  task::sleep(100);
  backward_(1200, 0.5); 
  cycle(400, 50);
  turn_right(400, 0);
  forward_(2300, 1);
  task::sleep(100);
  cycle(400, -50);
  task::sleep(100);
  cycle(525, 100);
  backward_(1000, -1);
  // fourth goal
  turn_left(500, -1);
  backward_(1000, -1);

}

void route_A () {
  cycle(1000, 100);
  forward_(1800, 1);
  turn_right(500, 1);
  forward_(1755,1);
}

void debug () {
  forward_(1000, 1);
}