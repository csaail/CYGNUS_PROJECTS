/*Problem statement:
To detect the movement of Pluto drone in vertical direction (upwards anddownwards) by using LEDs on board and printing the velocity values on the Pluto Monitor.*/

#include "PlutoPilot.h"
#include "Estimate.h" /*gives access to drone rates, angles, velocities andpositions*/
#include "Utils.h" /*gives access to LED, Graphs and Print*/

/*The setup function is called once at Pluto's hardware startup*/
void plutoInit()
{
/*Add your hardware initialization code here*/
}
/*The function is called once before plutoPilot when you activate Developer Mode*/

void onLoopStart()
{
  /*do your one time tasks here*/
  LED.flightStatus(DEACTIVATE); /*Disable default Led behaviour*/
}

void plutoLoop()
{
  /*Add your repeated code here*/
  if(Velocity.get(Z) > 0) /*If the drone is moving upwards (Velocity in the Z axis will be positive)*/
  {
    LED.set(RED, ON);
    LED.set(GREEN, OFF);
  }
  else /*If the drone is moving downwards*/
  {
    LED.set(RED, OFF);
    LED.set(GREEN, ON);
  }
  Monitor.println("Velocity Z: ", Velocity.get(Z));
  Graph.red(Velocity.get(Z), 1);
}

void onLoopFinish()
{
  /*do your cleanup tasks here*/
  LED.flightStatus(ACTIVATE); /*Enable the default LED behaviour*/
}

