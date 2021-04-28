// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auton/routes.h"
#include "motors.h"
#include "user/usercontrol.h"
#include "user/controller.h"

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
  c_multiplier = (100 - c_lowest_pwr) / pow(127 - (c_upper_dz + c_lower_dz), c_exponent);
  std::cout << c_multiplier << std::endl;

  int graph[255];

  for (int i = 0; i < 255; i++) {
    graph[i] = c_equation(i - 127);
  }

  for (int i = 0; i < 255; i++) {
    std::cout << int(i - 127) << " " << graph[i] << std::endl;
  }

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