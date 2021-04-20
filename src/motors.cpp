#include "vex.h"
#include "robot-config.h"

using namespace vex;

void chassisLF_set(int input)
{
  chassisLF.spin(directionType::fwd, input, percentUnits::pct);
}
void chassisLB_set(int input)
{
  chassisLB.spin(directionType::fwd, input, percentUnits::pct);
}
void chassisRF_set(int input)
{
  chassisRF.spin(directionType::fwd, input, percentUnits::pct);
}
void chassisRB_set(int input)
{
  chassisRB.spin(directionType::fwd, input, percentUnits::pct);
}
void intakeL_set(int input)
{
  intakeL.spin(directionType::fwd, input, percentUnits::pct);
}
void intakeR_set(int input)
{
  intakeR.spin(directionType::fwd, input, percentUnits::pct);
}
void rollerT_set(int input)
{
  rollerT.spin(directionType::fwd, input, percentUnits::pct);
}
void rollerB_set(int input)
{
  rollerB.spin(directionType::fwd, input, percentUnits::pct);
}

void chassisL_set(int input)
{
  chassisLF_set(input);
  chassisLB_set(input);
}
void chassisR_set(int input)
{
  chassisRF_set(input);
  chassisRB_set(input);
}
void chassis_set(int input)
{
  chassisL_set(input);
  chassisR_set(input);
}
void chassis_set_turn(int input)
{
  chassisL_set(-input);
  chassisR_set(input);
}

void intake_set(int input)
{
  intakeL_set(input);
  intakeR_set(input);
}

void roller_set(int input)
{
  rollerT_set(input);
  rollerB_set(input);
}