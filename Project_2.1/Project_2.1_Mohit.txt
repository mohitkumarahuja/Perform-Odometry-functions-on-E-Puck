
/*

  { Project 2 }


Code submitted by:
Team members:

1.> Mohit Kumar Ahuja
2.> Marc Blanchon


Course 	: MSCV
Subject : Autonomous Robotics




Code submitted to: 

Prof. Xevi Cufí   
University of GIRONA

*/

//including important libraries
#include <webots/robot.h>
#include <webots/differential_wheels.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/led.h>
#include <stdio.h>
#include <math.h>

#define TIME_STEP 32 /* ms */
#define WHEEL_RADIUS 0.0205 /* m */
#define AXLE_LENGTH 0.053 /* m */
#define ENCODER_RESOLUTION 159.23 /* pulses per revolution  */
#define RANGE (1024 / 2)

// Function Defination //
double update_odometry();

// Global variable //
double d[3] = {0.0,0.0,0.0};
double disp;

int main(int argc, char *argv[]) {

/* infinite for loop */
for(;;){
    
    wb_robot_init();  // initialize Webots //
    wb_differential_wheels_enable_encoders(TIME_STEP);
    wb_differential_wheels_set_encoders(0,0); //reseting encoders
    
    if ((0.1<disp) && (disp<0.115)) { //move robot till it covers 10 cm
    
      wb_differential_wheels_set_speed(0,0); // stop
      update_odometry(); //update the coordinates of {x,y} and Angle
      wb_robot_step(TIME_STEP*10000);
      printf("stop \n");
      break; // terminate the loop
    }
    
    else { // otherwise move forward
      
      printf("Move Forwarddddddddddddddd\n");
      wb_differential_wheels_set_speed(200,200); // go straight
      wb_robot_step(TIME_STEP);
      update_odometry(); //update the coordinates of {x,y} and Angle
      
    }
    
  }/* For ... */
  
  return 0;
}

double update_odometry(){

  //* define variables */
  double l = wb_differential_wheels_get_left_encoder(); // Steps for left wheel
  double r = wb_differential_wheels_get_right_encoder();// Steps for right wheel
  double dl = l / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by left wheel in meter
  double dr = r / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by right wheel in meter
  double da = (((dr - dl))/ AXLE_LENGTH); // delta orientation
  //printf("estimated distance covered by left wheel: %f cm.\n",dl);
  //printf("estimated distance covered by right wheel: %f cm.\n",dr);
  double dis = ((dl+dr)/2); // mean distance of both tyres
  disp += ((dl+dr)/2);      // mean distance of both tyres stored in another variable
  d[0] += dis*cos(d[2]);    // calculate and update x coordinate 
  d[1] += dis*sin(d[2]);    // calculate and update y coordinate 
  d[2] += da;               // calculate and update angle 
  double h = 57.2958*d[2];  // multiplying rad value to const to convert it into degrees
  printf("\n");
  printf("mean distance covered by both of wheel: %f cm.\n",100*disp);
  printf("Distance calculated for x in  odometry: %f cm.\n",100*d[0]);
  printf("Distance calculated for y in  odometry: %f cm.\n",100*d[1]);
  printf("estimated change of orientation: %f degree.\n",h);
  printf("Angle calculated by by odometry: %f rad.\n",d[2]);
  return disp ;
}
