#include <webots/robot.h>
#include <webots/differential_wheels.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <stdio.h>
#define TIME_STEP 64 /* ms */
#define WHEEL_RADIUS 0.0205 /* m */
#define AXLE_LENGTH 0.052 /* m */
#define ENCODER_RESOLUTION 159.23 /* pulses per revolution  */
#define RANGE (1024 / 2)

int main(int argc, char *argv[]) {
  //* define variables */
  WbDeviceTag distance_sensor_0;
  WbDeviceTag distance_sensor_1;
  WbDeviceTag distance_sensor_6;
  WbDeviceTag distance_sensor_7;
  
  WbDeviceTag led_0;
  WbDeviceTag led_1;
  WbDeviceTag led_6;
  WbDeviceTag led_7;

  double speed_0;
  double speed_1;
  double sensors_value_0;
  double sensors_value_1;
  double sensors_value_6;
  double sensors_value_7;
  /* initialize Webots */
  wb_robot_init();
  /* get and enable devices */
  wb_differential_wheels_enable_encoders(TIME_STEP*4);
  distance_sensor_0 = wb_robot_get_device("ps0"); //get distance sensors
  distance_sensor_1 = wb_robot_get_device("ps1");
  distance_sensor_6 = wb_robot_get_device("ps6");
  distance_sensor_7 = wb_robot_get_device("ps7");
  
  /* get leds */
  led_0 = wb_robot_get_device("led0");
  led_1 = wb_robot_get_device("led1");
  led_6 = wb_robot_get_device("led6");
  led_7 = wb_robot_get_device("led7");
  wb_distance_sensor_enable(distance_sensor_0,TIME_STEP*4);
  wb_distance_sensor_enable(distance_sensor_1,TIME_STEP*4);
  wb_distance_sensor_enable(distance_sensor_6,TIME_STEP*4);
  wb_distance_sensor_enable(distance_sensor_7,TIME_STEP*4);
  
  wb_led_set(led_0,1);
  wb_led_set(led_1,0);
  wb_led_set(led_6,0);
  wb_led_set(led_7,1);
  /* main loop */
  for (;;) {
    
  /* get sensors values */
  sensors_value_0 = wb_distance_sensor_get_value(distance_sensor_0);
  sensors_value_1 = wb_distance_sensor_get_value(distance_sensor_1);
  sensors_value_6 = wb_distance_sensor_get_value(distance_sensor_6);
  sensors_value_7 = wb_distance_sensor_get_value(distance_sensor_7);
  wb_led_set(led_0,1);
    wb_led_set(led_1,1);
    wb_led_set(led_6,1);
    wb_led_set(led_7,1);
    
    /* bahaviours and speed values*/
    if ((sensors_value_0>= 500)||(sensors_value_1>= 500)||(sensors_value_6>=500)||(sensors_value_7>=500)) {
    speed_0 = 100;
    speed_1 = -100;
    }

    else {
    wb_led_set(led_0,0);
    wb_led_set(led_1,0);
    wb_led_set(led_6,0);
    wb_led_set(led_7,0);
    speed_0 = 100;
    speed_1 = 100;
    }
    /* set speed values */
    wb_differential_wheels_set_speed(speed_0,speed_1);
    


    /* perform a simulation step */
    wb_robot_step(TIME_STEP);
  
 } /* For ... */
  return 0;

} /* int main ... */
