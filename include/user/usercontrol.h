#ifndef _USERCONTROL_H_
#define _USERCONTROL_H_

// speed multiplier
extern double chassis_speed_multiplier;

// speed multiplier control
void speed_multiplier_update();

void tank_drive();

// basic intake control
void intake_control();

// basic roller control
void roller_control();

#endif