#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"

#define STRAIGHT_SPEED 50
#define TURNING_SPEED  80
Sensors sensor;
Motors motor;



void follow_line() {
  int left = sensor.sensorValues[0];
  int right = sensor.sensorValues[1];
  //1 = black 0 = white
  if (left == 1 and right == 0){
    motor.driveLeft(TURNING_SPEED);
    Serial.println("left");
  } else if (left == 0 and right == 1) {
    motor.driveRight(TURNING_SPEED);
    Serial.println("right");
  } else {
      motor.driveForward(STRAIGHT_SPEED);
      Serial.println("straight");
  }
  
}



void setup() {
  Serial.begin(9600);

}


void loop() {
  sensor.updateSensors();
  follow_line();
  ///right
  //Serial.println(sensor.sensorValues[0]);
  //Serial.println(analogRead(sensor.sensorPins[0]));
  //Serial.println(sensor.sensorValues[1]);
  //Serial.println(analogRead(sensor.sensorPins[1]));
  //delay(1000);
  /**motor.driveForward(STRAIGHT_SPEED);
  
  motor.driveLeft(TURNING_SPEED);
  delay(2000);
  motor.driveRight(TURNING_SPEED);
  delay(2000);
  **/


}
