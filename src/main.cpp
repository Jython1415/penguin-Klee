// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auton/routes.h"
#include "motors.h"
#include "user/usercontrol.h"
#include "user/controller.h"
#include "user/controller-mapping.h"

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
    intake_control();
    roller_control();

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
