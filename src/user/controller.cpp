#include "vex.h"
#include "robot-config.h"

// controler variables for funsies
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
int axis4 = 0;

// to update controller related variables
void controller_variables_update()
{
  axis1 = ctlr1.Axis1.value();
  axis2 = ctlr1.Axis2.value();
  axis3 = ctlr1.Axis3.value();
  axis4 = ctlr1.Axis4.value();
}