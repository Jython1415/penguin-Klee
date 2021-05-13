#include "vex.h"
#include "robot-config.h"

using namespace vex;

void motor_set(motor name, int pwr = 0)
{
  name.spin(directionType::fwd, pwr, percentUnits::pct);
}

void chassisL_set(int input = 0)
{
  motor_set(chassisLF, input);
  motor_set(chassisLB, input);
}
void chassisR_set(int input = 0)
{
  motor_set(chassisRF, input);
  motor_set(chassisRB, input);
}
void chassis_set(int input = 0)
{
  chassisL_set(input);
  chassisR_set(input);
}
void chassis_set_turn(int input = 0)
{
  chassisL_set(-input);
  chassisR_set(input);
}

void intake_set(int input = 0)
{
  motor_set(intakeL, input);
  motor_set(intakeR, input);
}

void rollerT_set(int input = 0)
{
  motor_set(rollerT, input);
}
void rollerB_set(int input = 0)
{
  motor_set(rollerB, input);
}
void roller_set(int input = 0)
{
  rollerT_set(input);
  rollerB_set(input);
}