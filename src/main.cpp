#include "vex.h"
#include "auton/routes.h"
#include "auton/screen.h"
#include "motors.h"
#include "user/usercontrol.h"
#include "user/controller.h"
#include "user/controller-mapping.h"

#ifndef C_TEAM_BOT
#define C_TEAM_BOT false
#endif

using namespace vex;

// A global instance of competition
competition Competition;

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
  c_mapping_initialize();
  c_mapping_print_map();

  while (true)
  {
    controller_variables_update();

    speed_multiplier_update();

    tank_drive();
    
    if (C_TEAM_BOT)
    {
      intake_control();
      roller_control();
    }
    else
    {
      intake_control_a();
      roller_control_a();
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
    print_rotation();
    wait(100, msec);
  }
}
