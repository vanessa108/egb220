#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"

#define STRAIGHT_SPEED 100
#define TURNING_SPEED  80
Sensors sensor;
Motors motor;


void followLine() {
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
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

}


void loop() {
  sensor.updateSensors();
  followLine();

  if (sensor.onStraight) {
    //Serial.println("on straight");
    //Serial.println(time);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  } else {
    //Serial.println("on curve");
    //Serial.println(time);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }

  // Serial.println("reading");
  // 
  // Serial.println(analogRead(sensor.sensorPins[0]));
  // Serial.println(sensor.sensorValues[1]);
  // Serial.println(analogRead(sensor.sensorPins[1]));
  // Serial.println(sensor.sensorValues[2]);
  // Serial.println(analogRead(sensor.sensorPins[2]));
  // Serial.println(sensor.sensorValues[3]);
  // Serial.println(analogRead(sensor.sensorPins[3]));
  //Serial.println(sensor.sensorValues[4]);
  //Serial.println(sensor.sensorValues[5]);
  //delay(1000);
  /**
  motor.driveForward(STRAIGHT_SPEED);
  
  motor.driveLeft(TURNING_SPEED);
  delay(2000);
  motor.driveRight(TURNING_SPEED);
  delay(2000);
  **/


}
