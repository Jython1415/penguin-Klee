#ifndef _ROBOT_CONFIG_H_
#define _ROBOT_CONFIG_H_

extern vex::brain Brain;

extern vex::controller ctlr1;

extern vex::motor chassisLF;
extern vex::motor chassisLB;
extern vex::motor chassisRF;
extern vex::motor chassisRB;

extern vex::motor intakeL;
extern vex::motor intakeR;

extern vex::motor rollerT;
extern vex::motor rollerB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif