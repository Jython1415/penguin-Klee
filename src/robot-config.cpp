#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller ctlr1;

#ifdef C_TEAM_BOT // C

motor chassisLF = motor(PORT1, true);
motor chassisLB = motor(PORT9, false);
motor chassisRF = motor(PORT5, false);
motor chassisRB = motor(PORT8, true);

motor intakeL = motor(PORT20, true);
motor intakeR = motor(PORT7, false);

motor rollerT = motor(PORT14, false);
motor rollerB = motor(PORT16, true);

#else // A

motor chassisRF = motor(PORT11, false);
motor chassisRB = motor(PORT1,  true);
motor chassisLF = motor(PORT19, true);
motor chassisLB = motor(PORT12, false);

// positive is intake, negative is outtake
motor intakeR = motor(PORT16, true);
motor intakeL = motor(PORT7, false);

// positive is intake, negative is outtake
motor rollerT = motor(PORT4, false);
motor rollerB = motor(PORT6, false);

#endif

void vexcodeInit(void) {
}