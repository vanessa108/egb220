#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"
#include "LiquidCrystal_SoftI2C.h"

//SoftwareWire *wire = new SoftwareWire(F1, F4);
Sensors sensor;
Motors motor;
//LiquidCrystal_I2C lcd(0x27, 16, 2, wire);

/** Error constants **/
int error = 0;
int previousError = 0;
int dError = 0;
int iError = 0;
float Kp = 39; //best for speed 80
float Kd = 2; 
float Ki = 0;
float errorSpeed = 0;
bool prevStraight = true;
long straightCool = 0; //cooldown timer for speeding up 

void setup() {
  Serial.begin(9600);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
//  lcd.begin();
//  lcd.backlight();
//  lcd.print("Hello World");
}

void loop() {
  sensor.updateSensors();
  Serial.println(analogRead(sensor.sensorPins[5]));
  delay(1000);
	if (sensor.onSlow){
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, HIGH);
	prevStraight = true;
	straightCool = millis();
	if (straightCool + 100 < millis()) {
        motor.baseSpeed = 65;
  	}
	}
  // if the robot is on a straight, speed up and turn on LEDs
  if (sensor.onStraight) {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  //if not previously on a straight, reset the speed cooldown and state
  if (!prevStraight) {
    prevStraight = true;
    straightCool = millis();
  }
  // robot speeds up if it is still on a straight and the cooldown is over
  if (straightCool + 100 < millis()) {
    motor.baseSpeed = 130;
  } 	
} else {
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  motor.baseSpeed = 80;
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
