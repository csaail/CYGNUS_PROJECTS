/*Problem statement
Using two VL53L0X sensors create a feedback control system enabling the drone to avoid collision, using which the drone can be used for playing with.*/

/*Do not remove the include below*/
#include "PlutoPilot.h"
#include "Xranging.h"
#include "User.h"
#include "Utils.h"

/*The setup function is called once at Pluto's hardware startup*/
void plutoInit()
{
  /*Add your hardware initialization code here*/
  XRanging.init(LEFT); /*Initialize Left Ranging sensor*/
  XRanging.init(RIGHT); /*Initialize Right Ranging sensor*/
  setUserLoopFrequency(4); /*Change loop frequency for faster loop execution*/
}

/*The function is called once before plutoLoop when you activate Developer Mode*/
void onLoopStart()
{
  /*do your one time tasks here*/
  LED.flightStatus(DEACTIVATE); /*Disable the default led behavior*/
}

/*The loop function is called in an endless loop*/
void plutoLoop()
{
  /*Add your repeated code here*/
  /*if the sensor detects an obstacle on the left side i.e. range less than 500,
  roll right*/
  if(XRanging.getRange(LEFT)<500 && XRanging.getRange(LEFT)>0)
  {
    RcCommand.set(RC_ROLL, 1600);
    LED.set(RED,ON);
    LED.set(BLUE,OFF);
  }
  /*if the sensor detects an obstacle on the right side i.e. range less than500, roll left*/
  else if(XRanging.getRange(RIGHT)<500 && XRanging.getRange(RIGHT)>0)
  {
    RcCommand.set(RC_ROLL, 1400);
    LED.set(RED,OFF);
    LED.set(BLUE,ON);
  }
  /*when no obstacle is detected, let control be with the user*/
  else
  {
    RcCommand.set(RC_ROLL,RcData.get(RC_ROLL));
    LED.set(RED,OFF);
    LED.set(BLUE,OFF);
  }
}

/*The function is called once after plutoLoop when you deactivate Developer Mode*/
void onLoopFinish()
{
  /*do your cleanup tasks here*/
  LED.flightStatus(ACTIVATE); /*Enable the default led behavior*/
}
