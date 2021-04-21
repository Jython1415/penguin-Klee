// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auton/routes.h"
#include "motors.h"

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
  while (true)
  {
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