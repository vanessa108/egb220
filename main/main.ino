#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"
#include "LiquidCrystal_SoftI2C.h"

#define ON_CURVE 0
#define ON_STRAIGHT 1
#define ON_SLOW 2

SoftwareWire *wire = new SoftwareWire(F1, F4);
Sensors sensor;
Motors motor;
LiquidCrystal_I2C lcd(0x27, 16, 2, wire);

/** Error constants **/
int error = 0;
int previousError = 0;
int dError = 0;
int iError = 0;
float Kp = 33; //best for speed 80 //34 , 1
float Kd = 5; 
float Ki = 0;
float errorSpeed = 0;
bool prevStraight = true;
long straightCool = 0; //cooldown timer for speeding up 

void setup() {
  Serial.begin(9600);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.print("hello");
}

void loop() {
  sensor.updateSensors();
  lcd.print(sensor.stopCounter);
  Serial.println(analogRead(sensor.sensorPins[4]));
  if (sensor.finishLine == true) {
    motor.baseSpeed = 0;
    analogWrite(D0, 0);
    analogWrite(B7, 0);
    sensor.pathTracker = 0;
    sensor.stopCounter = 0;
    delay(3000);
    sensor.rightIndicatorTimer = millis();
    sensor.finishLine = false;
  } else {
      
  if (sensor.state == 2 and analogRead(sensor.sensorPins[4]) < 100){
    motor.baseSpeed = 20;
  }
  // if the robot is on a straight, speed up and turn on LEDs
  if (sensor.state == ON_STRAIGHT) {
      //lcd.print("Full speed");
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      //if not previously on a straight, reset the speed cooldown and state
      if (!prevStraight) {
        prevStraight = true;
        straightCool = millis();
      }
    // robot speeds up if it is still on a straight and the cooldown is over
      if (straightCool + 100 < millis()) {
        motor.baseSpeed = 75;
      }   
  } else {
      //lcd.print("Curve");
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      motor.baseSpeed = 75;
      prevStraight = false;
  }


/** PID control **/
  error = sensor.calculateError();
  dError = error - previousError;
  iError += iError;
  errorSpeed = (Kp*error) + (Ki*iError) + (Kd*dError);
  motor.drive(errorSpeed);
  previousError = error;


    
  }


}
