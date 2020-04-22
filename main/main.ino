#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"

Sensors sensor;
Motors motor;

/** Error constants **/
int error = 0;
int previousError = 0;
int dError = 0;
int iError = 0;
float Kp = 40; //18
float Kd = 0; //0
float Ki = 0;
float errorSpeed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  sensor.sensorSum = 0;
  sensor.updateSensors();
  Serial.println(sensor.sensorSum);
//  if (sensor.sensorSum == 0) {
//    error = -1;
//  } else {
//    error = sensor.calculateError();
//  }
//   if (sensor.onStraight) {
//   digitalWrite(LED2, HIGH);
//   digitalWrite(LED3, HIGH);
// } else {
//   digitalWrite(LED2, LOW);
//   digitalWrite(LED3, LOW);
// }
  error = sensor.calculateError();
  dError = error - previousError;
  iError += iError;
  errorSpeed = (Kp*error) + (Ki*iError) + (Kd*dError);
  motor.drive(errorSpeed);
  previousError = error;
  //Serial.println(errorSpeed);
  //Serial.println(analogRead(SENSOR_8));
//Serial.println(sensor.sensorValues[3]);



}
