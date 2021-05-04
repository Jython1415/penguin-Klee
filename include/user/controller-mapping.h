#ifndef _CONTROLLER_MAPPING_H_
#define _CONTROLLER_MAPPING_H_

// curve mapping constants
extern bool curve_is_on; // on and off for curved controller mapping
extern double c_exponent;
extern int c_lower_dz; // lower dead zone; dead zone being the part of the joystick range that has no effect
extern int c_upper_dz; // upper dead zone
extern int c_lowest_pwr; // lowest power output

// derived using desmos.com/calculator/rzxfys8ctn -- a calculator I developed for this purpose
extern double c_multiplier;

int c_equation (int axis_input);

void c_mapping_initialize();

void c_mapping_print_map();

#endif
