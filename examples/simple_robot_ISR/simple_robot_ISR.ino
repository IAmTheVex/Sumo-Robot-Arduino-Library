/*This example show how to use the SumoRobot library for arduino!
If you want to make a sumo robot, it can't be any easier 
than this library.
This example and the library itself is made by #noName 
(Ciobanu Laurentiu). Special thanks to #noFear (Tenea Mihai)
for his contribution! :) 

File signed - 24 / 06 / 2015 - #noName 
Romania - Alpha Robotics Team - Ciobanu Laurentiu
Thanks to Ion Ghiteanu -YO9BXE- for his support
*/

#include <SumoRobot.h>
char iMode = 'C';//The intrerrups and timer modes.
//The options are: C - Classic Mode 
//                 A - Advanced Mode 
//                 M - You are crazy man 
//                 N - Disable Intrerrupts

int motors[] = {3, 11, 5, 6}; // Motor control
//Pins in order, doesn't count if 3/motor (L298 Driver)
//or 2/motor (TB6612FGN Driver)

int irSensors[] = {1, 2, 3}; //ir digital sensors pins in order

int startModulePin = 13;

int echoPin = 7, trigPin = 8;
// /\ - pins for the ultrasonic distance sensor ex: HC-06

int max_dist = 35; //max distance for ultrasonic sensor
int act_dist; //this will store the distance from ultrasonic sensor

SumoRobot sumo(sumoRobotMain, startModulePin);
//from now on, we can add our own routine like loop or setup
//this routine will run in ISR
//also the second argument of the constructor is the start module pin 

void setup(){
  sumo.initSumo(iMode, motors); //init motors and intrerrupts
  sumo.irSetup(irSensors); //init ir digital sensors
  //now you will be able to use analog sensors as well
  //using the following functions
  //sumo.irAnalogSetup(int analogPins[]);
  //sumo.irAnalogRead(int n, int r)
  //in the variable r will be stored the value received
  //from the sensor attached on pin n from pins[] vector
  //as well you can read all the sensors as once using the funtion:
  //sumo.irAnalogRead(int vals[]);;
  //in the vector vals[] will be stored the values
  //from the sensor in the same order like in the pins[] vector   
  sumo.ultraSetup(echoPin, trigPin, max_dist); //init ultrasonic sensors
  sumo.Begin();//jump to loop and start the isr
  // you can use sumo.Stop(); to stop the robot ..
  //this is good if you need to use start modules
  //for international competitions
}

void loop(){} // in this example i'm not gonna' use the loop
//keep in mind that if you wanna' data communicate with both
//loop and isr you will need to declare global variables

void sumoRobotMain(){
	  // here will go your normal sumo altgorithm
  
  //ultraRead(int x) will return true if is a object
  //in the range of max_dist, otherwise will return false
  //as well the x value will store the distance in cm
  //to that object ... 
  if(sumo.ultraRead(act_dist)){ //if enemy is in front of you  
    sumo.setMotors(255, 255);//go at maximum speed to it
  }
  //the function sumo.ir(n) will return true if the 
  //sensor on the n - 1 position in the sensor 
  //array see anything (its state is 1) and will
  //return false if the sensor doesn't see anything
  //as well, if you wanna' know the state of all of your
  //ir sensors you can use the function ir(boolean irsv[])
  //the vector irsv[] will store all of your sensor data ..
  else if(sumo.ir(1)){//if the left sensor see anything
    sumo.setMotors(100, -100);//go to left  
  }
  else if(sumo.ir(2)){//if the right sensor see anything
    sumo.setMotors(-100, 100);//go to right 
  }
  else{ //if none of the sensors see's anything
    sumo.setMotors(60, -60);//spin slowly in a circle
  }
}