#ifndef _ROBOT_CONFIG_H_
#define _ROBOT_CONFIG_H_

using namespace vex;

extern brain Brain;

extern controller ctlr1;

extern motor chassisLF;
extern motor chassisLB;
extern motor chassisRF;
extern motor chassisRB;

extern motor intakeL;
extern motor intakeR;

extern motor rollerT;
extern motor rollerB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif