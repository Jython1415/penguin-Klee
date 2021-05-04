#include "vex.h"

// curve mapping constants
bool curve_is_on = 1; // on and off for curved controller mapping
double c_exponent = 2.0;
int c_lower_dz = 10; // lower dead zone; dead zone being the part of the joystick range that has no effect
int c_upper_dz = 10; // upper dead zone
int c_lowest_pwr = 3; // lowest power output

// derived using desmos.com/calculator/rzxfys8ctn -- a calculator I developed for this purpose
double c_multiplier = 0;

// mapping array
int c_map_array[255];
int c_map (int input) { return c_map_array[input + 127]; }

// math for the mapping
int c_equation (int axis_input)
{
  if (abs(axis_input) >= 127 - c_upper_dz) { return copysign(100, axis_input); }
  else if (abs(axis_input) <= c_lower_dz) { return 0; }
  else { return int(copysign(round(c_multiplier * pow(abs(axis_input) - c_lower_dz, c_exponent)) + c_lowest_pwr, axis_input)); }
}

// initiaizing the mapping constant
void c_mapping_initialize()
{
  c_multiplier = (100 - c_lowest_pwr) / pow(127 - (c_upper_dz + c_lower_dz), c_exponent);

  // add values to the array
  for (int i = 0; i < 255; i++) {
    c_map_array[i] = c_equation(i - 127);
    if (i % 10 == 0) { vex::task::sleep(1); } // to make sure the program doesn't cut off the loop for hogging too much time
  }
}

void c_mapping_print_map()
{
  // print the array
  std::cout << "Controller Mapping Array (CMA)" << std::endl;

  for (int i = 0; i < 255; i++) {
    std::cout << i - 127 << ", " << c_map_array[i] << std::endl; // prints: axis, power
    if (i % 10 == 0) { vex::task::sleep(1); } // to make sure the program doesn't cut off the loop for hogging too much time
  }

  // points of interest (POI) print
  std::cout << "Points of Interest on the CMA" << std::endl;

  const int POI_len = 9;
  int POI[POI_len] = {0, c_lower_dz - 1, c_lower_dz, c_lower_dz + 1, 63, (127 - c_upper_dz) - 1, (127 - c_upper_dz), (127 - c_upper_dz) + 1, 127};

  for (int i = 0; i < POI_len; i++) {
    std::cout << POI[i] << ", " << c_map(POI[i]);
    if (POI[i] != 0) { std::cout << ", " << c_map(POI[i] * -1) << std::endl; }
    else { std::cout << std::endl; }
  }
}