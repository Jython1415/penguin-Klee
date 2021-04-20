#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
vex::brain Brain;

vex::controller ctlr1;

// main bot
vex::motor chassisLF  = vex::motor(PORT1, true);
vex::motor chassisLB  = vex::motor(PORT9, false);
vex::motor chassisRF = vex::motor(PORT5, false);
vex::motor chassisRB = vex::motor(PORT8, true);

vex::motor intakeL = vex::motor(PORT20, false);
vex::motor intakeR = vex::motor(PORT7, true);

vex::motor rollerT = vex::motor(PORT14, false);
vex::motor rollerB = vex::motor(PORT16, true);

void vexcodeInit(void) {
}
