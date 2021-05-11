#ifndef _VEX_H_
#define _VEX_H_

// This file must be included in all files for this project

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

// #define C_TEAM_BOT true

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, vex::msec);                                                        \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

#endif