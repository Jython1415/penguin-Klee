#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include "user/controller.h"
#include "user/controller-mapping.h"

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
  if (ctlr1.ButtonA.pressing()) { curve_is_on = 1; }
  if (ctlr1.ButtonY.pressing()) { curve_is_on = 0; }

  // basic tank drive
  if (!ctlr1.ButtonX.pressing()) // normal input
  {
    // declare variables
    int chassis_lp = 0; // left power
    int chassis_rp = 0; // right power

    if (curve_is_on) // if curved power is on
    {
      chassis_lp = c_map(axis3);
      chassis_rp = c_map(axis2);
    }
    else // linear control
    {
      // assign power linearly with threshold
      chassis_lp = abs(axis3) > linear_b_threshold /* threshold check */ ? axis3 : 0;
      chassis_rp = abs(axis2) > linear_b_threshold ? axis2 : 0;
    }

    // apply the speed multiplier
    chassis_lp *= chassis_speed_multiplier;
    chassis_rp *= chassis_speed_multiplier;

    // set power
    chassisL_set(chassis_lp);
    chassisR_set(chassis_rp);
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

// A usercontrol functions
void intake_control_a()
{
  if (ctlr1.ButtonR1.pressing())
  {
    intake_set(100);
  }
  else if (ctlr1.ButtonL1.pressing())
  {
    intake_set(-100);
  }
  else
  {
    intake_set(0);
  }
}

void roller_control_a()
{
  if (ctlr1.ButtonR2.pressing())
  {
    roller_set(100);
  }
  else if (ctlr1.ButtonL2.pressing())
  {
    roller_set(-100);
  }
  else
  {
    roller_set(0);
  }
}