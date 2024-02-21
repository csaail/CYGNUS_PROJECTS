/*Problem Statement 
By making changes in the atmospheric pressure in the drone’s surroundings, make the drone take off to a certain altitude.*/

#include "PlutoPilot.h"
#include "Control.h"
#include "Sensor.h"
#include "User.h"
#include "Utils.h"
#include "Math.h"

int16_t initPressure;
int16_t currPressure;

void onLoopStart()
{
  /*do your one time tasks here*/
  initPressure=Barometer.get(PRESSURE); /*Get Initial Temperature
  when you turn the developer mode*/
  LED.flightStatus(DEACTIVATE); /*Disable the default led behavior*/
}

void plutoLoop()
{
  /*Add your repeated code here*/
  currPressure=Barometer.get(PRESSURE); /*Get pressure valuescontinuously*/
  if(fabs(currPressure-initPressure)>2) /*calculate if the difference
  {
    LED.set(RED, ON); /*turn on led to indicate if condition is true*/
    Command.arm(); /*arm the drone*/
    DesiredPosition.set(Z,100); /*set the drone altitude to 100cms*/
  }
  initPressure=((initPressure*0.9)+(currPressure*0.1));
  Monitor.println("oldPressure", initPressure);
  Monitor.println("newPressure", currPressure);
  Graph.red(currPressure);
}

void onLoopFinish()
{
  /*do your cleanup tasks here*/
  LED.flightStatus(ACTIVATE); /*Enable the default led behavior*/
}
