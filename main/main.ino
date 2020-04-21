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
const int Kp = 50;
const int Kd = 5;
const int Ki = 5;
int errorSpeed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  
  sensor.updateSensors();
  error = sensor.calculateError();
  dError = error - previousError;
  iError += iError;
  errorSpeed = (Kp*error) + (Ki*iError) + (Kd*dError);
  motor.drive(errorSpeed);
  previousError = error;

}
