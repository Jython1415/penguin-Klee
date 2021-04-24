#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include "user/controller.h"

// linear mapping constants
int linear_b_threshold = 15; // linear bottom threshold

// speed multiplier
double chassis_speed_multiplier = 1.0;

// speed multiplier control
void speed_multiplier_update()
{
  // default is 1.0
  // button up is 0.8
  // botton down is 0.4
  chassis_speed_multiplier = ctlr1.ButtonUp.pressing() ? 0.8 : ctlr1.ButtonDown.pressing() ? 0.4 : 1.0;
}

// tank drive with 1 macro
void tank_drive()
{
  // basic tank drive
  if (!ctlr1.ButtonX.pressing()) // normal input
  {
    // assign power with threshold
    int chassis_left_power = abs(axis3) > linear_b_threshold /* threshold check */ ? axis3 : 0;
    // multiply by speed multiplier
    chassis_left_power *= chassis_speed_multiplier;

    int chassis_right_power = abs(axis2) > linear_b_threshold ? axis2 : 0;
    chassis_right_power *= chassis_speed_multiplier;

    chassisL_set(chassis_left_power);
    chassisR_set(chassis_right_power);
  }
  else // when button B is pressed; a macro
  {
    chassisL_set(-60);
    chassisR_set(-60);
  }
}

// basic intake control
void intake_control()
{
  if (ctlr1.ButtonL1.pressing())
    {
      intake_set(100);
    }
    else if (ctlr1.ButtonL2.pressing())
    {
      intake_set(-100);
    }
    else
    {
      intake_set(0);
    }
}

// basic roller control
void roller_control()
{
  // roller control
  if (!ctlr1.ButtonX.pressing())
  {
    if (ctlr1.ButtonR1.pressing())
    {
      roller_set(100);
    }
    else if (ctlr1.ButtonR2.pressing())
    {
      roller_set(-100);
    }
    else
    {
      roller_set(0);
    }
  }
  else
  {
    roller_set(80);
  }
}