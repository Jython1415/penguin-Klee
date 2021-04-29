// curve mapping constants
bool curve_is_on = 1; // on and off for curved controller mapping
double c_exponent = 2.0;
int c_lower_dz = 10; // lower dead zone; dead zone being the part of the joystick range that has no effect
int c_upper_dz = 10; // upper dead zone
int c_lowest_pwr = 3; // lowest power output

// derived using desmos.com/calculator/rzxfys8ctn -- a calculator I developed for this purpose
double c_multiplier = 0;

// math for the mapping
int c_equation (int axis_input)
{
  if (abs(axis_input) >= 127 - c_upper_dz) { return copysign(100, axis_input); }
  else if (abs(axis_input) <= c_lower_dz) { return 0; }
  else { return int(copysign(round(c_multiplier * pow(abs(axis_input) - c_lower_dz, c_exponent)) + c_lowest_pwr, axis_input)); }
}

// initiaizing the mapping constant
void c_mapping_initialize() { c_multiplier = (100 - c_lowest_pwr) / pow(127 - (c_upper_dz + c_lower_dz), c_exponent); }
