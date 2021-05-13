#ifndef _MOTORS_H_
#define _MOTORS_H_

#include "vex.h"

using namespace vex;

void motor_set(motor name, int pwr = 0);

void chassisL_set(int input = 0);
void chassisR_set(int input = 0);
void chassis_set(int input = 0);
void chassis_set_turn(int input = 0);

void intake_set(int input = 0);

void rollerT_set(int input = 0);
void rollerB_set(int input = 0);
void roller_set(int input = 0);

#endif