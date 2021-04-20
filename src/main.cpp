// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auton/routes.h"
#include "motors.h"

using namespace vex;

// A global instance of competition
competition Competition;

// drive selection
bool chassis_tank_drive = true;

// speed multiplier
double chassis_speed_multiplier = 0.8;

// controler variables
int axis1;
int axis2;
int axis3;
int axis4;

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void autonomous(void)
{
  route_2();
}

void usercontrol(void)
{
  while (true)
  {
    // controller variables update
    axis1 = ctlr1.Axis1.value();
    axis2 = ctlr1.Axis2.value();
    axis3 = ctlr1.Axis3.value();
    axis4 = ctlr1.Axis4.value();

    // speed multiplier control
    chassis_speed_multiplier = ctlr1.ButtonUp.pressing() ? 0.8 : ctlr1.ButtonDown.pressing() ? 0.4 : 1.0;

    // chassis control
    if (chassis_tank_drive)
    {
      // basic tank drive
      if (!ctlr1.ButtonX.pressing())
      {
        int chassis_left_power = abs(axis3) > 10 ? axis3 : 0;
        chassis_left_power *= chassis_speed_multiplier;
        int chassis_right_power = abs(axis2) > 20 ? axis2 : 0;
        chassis_right_power *= chassis_speed_multiplier;

        chassisL_set(chassis_left_power);
        chassisR_set(chassis_right_power);
      }
      else // when button B is pressed
      {
        chassisL_set(-60);
        chassisR_set(-60);
      }
    }
    else
    {
      // basic arcade control
      chassisL_set((axis2 + axis1) * chassis_speed_multiplier);
      chassisR_set((axis2 - axis1) * chassis_speed_multiplier);
    }
    // intake control
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

    task::sleep(20);
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
