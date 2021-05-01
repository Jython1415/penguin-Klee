#include "vex.h"
#include "robot-config.h"

using namespace vex;

void print_rotation () {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Right Front: %f", chassisRF.rotation(rotationUnits::raw));
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Right Back: %f", chassisRB.rotation(rotationUnits::raw));
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("Left Front: %f", chassisLF.rotation(rotationUnits::raw));
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print("Left Back: %f", chassisLB.rotation(rotationUnits::raw));
}