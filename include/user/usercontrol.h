#ifndef _USERCONTROL_H_
#define _USERCONTROL_H_

// linear mapping constants
extern int linear_b_threshold; // linear bottom threshold

// curve mapping constants
extern bool curve_is_on; // on and off for curved controller mapping
extern double c_exponent;
extern int c_lower_dz; // lower dead zone; dead zone being the part of the joystick range that has no effect
extern int c_upper_dz; // upper dead zone
extern int c_lowest_pwr; // lowest power output
// derived using desmos.com/calculator/rzxfys8ctn -- a calculator I developed for this purpose
extern double c_multiplier;
int c_equation (int axis_input);

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