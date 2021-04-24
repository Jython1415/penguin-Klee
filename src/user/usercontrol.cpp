#include "vex.h"
#include "robot-config.h"
#include "motors.h"
#include "user/controller.h"

// linear mapping constants
int linear_b_threshold = 15; // linear bottom threshold

// curve mapping constants
const bool curve_is_on = 1; // on and off for curved controller mapping
const double c_exponent = 1.8;
const int c_lower_dz = 10; // lower dead zone; dead zone being the part of the joystick range that has no effect
const int c_upper_dz = 10; // upper dead zone
const int c_lowest_pwr = 3; // lowest power output
const double c_multiplier = 0.02157; // derived using desmos.com/calculator/rzxfys8ctn -- a calculator I developed for this purpose
int c_equation (int axis_input)
{
  if (abs(axis_input) >= c_upper_dz) { return copysign(100, axis_input); }
  else if (abs(axis_input) <= c_lower_dz) { return 0; }
  else { return int(round(c_multiplier * pow(axis_input - c_lower_dz, c_exponent))) + c_lowest_pwr; }
}

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
    // declare variables
    int chassis_lp = 0; // left power
    int chassis_rp = 0; // right power

    if (curve_is_on) // if curved power is on
    {
      chassis_lp = c_equation(axis3);
      chassis_rp = c_equation(axis2);
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