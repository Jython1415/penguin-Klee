#include "vex.h"
#include "robot-config.h"
#include "motors.h"

#define rot_LB chassisLB.rotation(vex::rotationUnits::raw)
#define rot_RB chassisRB.rotation(vex::rotationUnits::raw)

void chassis_stop()
{
  chassis_set(0);
}
void chassis_reset()
{
  chassisLF.resetRotation();
  chassisLB.resetRotation();
  chassisRF.resetRotation();
  chassisRB.resetRotation();
}

// pause in ms
void pause(int input)
{
  vex::task::sleep(input);
}

// controlled forward/backward movement
void f_c(int dist, int max_pwr)
{
  // forward movement
  if (dist > 0)
  {
    // acc 1
    chassis_set(int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB > int(dist/6) * 1);
    chassis_set(int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB > int(dist/6) * 2);
    chassis_set(max_pwr);

    // decc 1
    waitUntil(rot_LB > int(dist/6) * 4);
    chassis_set(int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB > int(dist/6) * 5);
    chassis_set(int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB > dist);
    chassis_stop();
  }
  // backward movement
  else
  {
    // acc 1
    chassis_set(-int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB < int(dist/6) * 1);
    chassis_set(-int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB < int(dist/6) * 2);
    chassis_set(-max_pwr);

    // decc 1
    waitUntil(rot_LB < int(dist/6) * 4);
    chassis_set(-int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB < int(dist/6) * 5);
    chassis_set(-int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB < dist);
    chassis_stop();
  }
}

// controlled turn
void t_c(int dist, int max_pwr)
{
  // forward movement
  if (dist > 0)
  {
    // acc 1
    chassis_set_turn(int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB < -int(dist/6) * 1);
    chassis_set_turn(int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB < -int(dist/6) * 2);
    chassis_set_turn(max_pwr);

    // decc 1
    waitUntil(rot_LB < -int(dist/6) * 4);
    chassis_set_turn(int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB < -int(dist/6) * 5);
    chassis_set_turn(int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB < -dist);
    chassis_stop();
  }
  // backward movement
  else
  {
    // acc 1
    chassis_set_turn(-int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB > -int(dist/6) * 1);
    chassis_set_turn(-int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB > -int(dist/6) * 2);
    chassis_set_turn(-max_pwr);

    // decc 1
    waitUntil(rot_LB > -int(dist/6) * 4);
    chassis_set_turn(-int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB > -int(dist/6) * 5);
    chassis_set_turn(-int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB > -dist);
    chassis_stop();
  }
}

// pause and reset chassis encoders
void p_r()
{
  pause(500);
  chassis_reset();
}

// score corner
void route_corner ()
{
  // shoot (time)
  intake_set(50);
  roller_set(100);
  pause(600);
  // pause a bit
  intake_set(0);
  roller_set(0);
  chassis_set(20);
  pause(500);
  // remove blue balls
  intake_set(100);
  rollerT_set(-10);
  rollerB_set(60);
  pause(550);
  // stop
  intake_set(0);
  roller_set(0);
  chassis_stop();
  
  p_r(); // reset

  // back away
  intake_set(-20);
  chassis_set(-40);
  f_c(-1300, 40);
  // get rid of blue balls
  intake_set(-50);
  roller_set(-100);
  pause(1500);
  intake_set(0);
  roller_set(0);
}

// corner descore
void route_corner_descore ()
{
  // remove blue balls
  intake_set(100);
  rollerT_set(-10);
  rollerB_set(60);
  pause(550);
  // stop
  intake_set(0);
  roller_set(0);
  chassis_stop();
  
  p_r(); // reset

  // back away
  intake_set(-20);
  chassis_set(-40);
  f_c(-1000, 40);
  // get rid of blue balls
  intake_set(-50);
  roller_set(-100);
  pause(1000);
  intake_set(0);
  roller_set(0);
}


void route_p1 ()
{
  // score preload
  rollerB_set(100);
  waitUntil(rollerB.rotation(vex::rotationUnits::deg) > 180);
  rollerB_set(0);

  // get to ball
  chassis_set(20);
  waitUntil(rot_LB > 200);
  chassis_set(30);
  waitUntil(rot_LB > 100);
  // intake
  chassis_set(50);
  intake_set(100);
  waitUntil(rot_LB > 2000);
  // slow down
  chassis_set(10);
  waitUntil(rot_LB > 2500);
  // stop
  chassis_stop();
  intake_set(20);

  p_r(); // reset

  // turn left
  t_c(275, 40);

  pause(500);

  // forward to the goal (time)
  intake_set(-5);
  chassis_set(30);
  pause(2000);
  chassis_stop();

  route_corner();
}

// score the 2nd tower and back up
void route_p2 ()
{
  t_c(-900, 30);

  // pause
  pause(500);
  chassis_reset();

  // forward
  f_c(1750, 60);

  p_r(); // reset
  
  // intake
  intake_set(100);
  chassis_set(20);
  waitUntil(rot_LB > 1000);
  // stop
  intake_set(10);
  chassis_stop();

  p_r(); // reset

  // turn left
  t_c(600, 50);

  // forward to goal
  chassis_set(40);
  pause(1000);
  chassis_stop();

  p_r(); // reset

  //// this should be a function
  // shoot (time)
  intake_set(100);
  roller_set(100);
  pause(600);
  // remove blue balls
  rollerT_set(-5);
  rollerB_set(60);
  pause(250);
  // stop (intake out to avoid descore)
  intake_set(-20);
  roller_set(0);
  // reset encoders
  chassis_reset();
  // back away
  chassis_set(-20);
  waitUntil(rot_LB < -400);
  roller_set(-100);
  intake_set(-100);
  f_c(-1000, 60);
  // outake a bit more
  pause(500);
  // stop outaking
  roller_set(0);
  intake_set(0);
}

// head across to the other corner
void route_p2_v2 ()
{
  p_r(); // reset

  chassis_set(10);
  waitUntil(rot_LB > 200);
  intake_set(-30);
  f_c(8000, 60);
  p_r();

  t_c(100, 30);

  p_r();

  // forward to goal
  chassis_set(30);
  pause(2000);
  chassis_stop();
  
  pause(500); // pause

  route_corner_descore();
}

void route_1 ()
{
  route_p1();

  p_r(); // reset

  route_p2();

  p_r(); // reset

  // turn right
  t_c(-600, 50);

  p_r(); // reset

  // forward
  f_c(2500, 60);

  p_r(); // reset

  // forward and intake
  intake_set(100);
  f_c(600, 40);
  intake_set(20);

  p_r(); // reset

  // turn left
  t_c(600, 40);

  // forward to goal
  chassis_set(30);
  pause(1500);
  chassis_set(0);

  //// this should be a function
  // shoot (time)
  intake_set(100);
  roller_set(100);
  pause(600);
  // remove blue balls
  rollerT_set(-5);
  rollerB_set(60);
  pause(250);
  // stop (intake out to avoid descore)
  intake_set(-20);
  roller_set(0);
  // reset encoders
  chassis_reset();
  // back away
  chassis_set(-20);
  waitUntil(rot_LB < -400);
  roller_set(-100);
  intake_set(-100);
  f_c(-1000, 60);
  // outake a bit more
  pause(500);
  // stop outaking
  roller_set(0);
  intake_set(0);
}

void route_2 ()
{
  chassis_reset();

  route_p1();

  p_r(); // reset

  // turn right
  t_c(-1000, 40);

  // back against the wall
  chassis_set(-35);
  pause(2000);
  chassis_stop();

  route_p2_v2();

  p_r(); // reset

  t_c(-450, 30);

  pause(500); // pause

  // align against wall
  chassis_set(-30);
  pause(1500);
  chassis_stop();

  route_p2_v2();
}