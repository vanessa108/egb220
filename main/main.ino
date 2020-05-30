#include <LiquidCrystal_SoftI2C.h>
#include <SoftwareWire.h>
#include <arduino.h>
#include <stdio.h>
#include "spark.h"
#include "motors.h"
#include "sensors.h"

#define ON_CURVE 0
#define ON_STRAIGHT 1
#define ON_SLOW 2

SoftwareWire *wire = new SoftwareWire(C7, C6);
LiquidCrystal_I2C lcd(0x27, 16, 2, wire);
Sensors sensor;
Motors motor;

/** Error constants **/
int error = 0;
int previousError = 0;
int dError = 0;
int iError = 0;
float Kp = 35; //best for speed 80 //34 , 1
float Kd = 45; //7.5
float Ki = 0;
float errorSpeed = 0;


bool prevStraight = true;
long straightCool = 0; //cooldown timer for speeding up 
long lastMillis = 0;
long lapStartTime = 0;
long currentTime = 0;
long currentDuration = 0;
int intSeconds;
int millseconds;


void setup() {
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  pinMode(LED3, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(12, 0);
  lcd.print(":");
  lcd.setCursor(0, 1);
  lcd.print("E:");
  lcd.setCursor(6, 1);
  lcd.print("SPD:");
  lcd.setCursor(14,1);
  lcd.print("C2");
  lcd.setCursor(10, 0);
  lcd.print("T:");
  lcd.setCursor(14, 0);
  lcd.print("s");


}



void loop() {
  Serial.println(sensor.sensorValues[4]);
  sensor.updateSensors();
  if (sensor.finishLine == true) {
    
    motor.baseSpeed = 0;
    analogWrite(D0, 0);
    analogWrite(B7, 0);  
    sensor.pathTracker = 0;
    intSeconds = 0;
    previousError = 0;

    lcd.setCursor(3, 1);
    lcd.print(error);
    lcd.setCursor(10, 1);
    lcd.print(motor.baseSpeed);
    lcd.setCursor(1, 0);
    lcd.print(" FINISH ");
    
    delay(3000);
    
    sensor.rightIndicatorTimer = millis();
    sensor.startTimer = millis();
    lapStartTime = millis();
    sensor.finishLine = false;
  } else {   

      /** PID control **/
    error = sensor.calculateError();
    dError = error - previousError;
    iError += iError;
    errorSpeed = (Kp*error) + (Ki*iError) + (Kd*dError);
    motor.drive(errorSpeed);
    previousError = error;


    
    if (sensor.state == 2) {
      motor.baseSpeed = 34;
      Kp = 34;
      Kd = 0;
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
    // if the robot is on a straight, speed up and turn on LEDs
    if (sensor.state == ON_STRAIGHT) {
            Kp = 35;
            Kd = 45;
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        //if not previously on a straight, reset the speed cooldown and state
        if (!prevStraight) {
          prevStraight = true;
          straightCool = millis();
        }
      // robot speeds up if it is still on a straight and the cooldown is over
        if (straightCool + 100 < millis()) {
          motor.baseSpeed = 100;
        }   
    } 
    if (sensor.state == ON_CURVE){
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        motor.baseSpeed = 75;
        prevStraight = false;
    }


  }
  long currMillis = millis();
  if (lastMillis /1000 != currMillis/1000) {
    
      
  lcd.setCursor(2, 1);
  lcd.print(error);
  lcd.setCursor(10, 1);
  lcd.print(motor.baseSpeed);
  
  currentTime = millis();
  currentDuration = currentTime - lapStartTime;
  intSeconds = currentDuration / 1000;
  if (intSeconds <10) {
    lcd.setCursor(12, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print(intSeconds);
   } else {
    lcd.setCursor(12, 0);
    lcd.print(intSeconds);
    }

    lcd.setCursor(1, 0);
    if (sensor.state == ON_CURVE) {
        lcd.print(" CURVE  ");
      } else if (sensor.state == ON_STRAIGHT) {
        lcd.print("STRAIGHT");
        } else if (sensor.state == ON_SLOW) {
          lcd.print("  SLOW  ");
          }

    lastMillis = currMillis;
    
    }




  
}
