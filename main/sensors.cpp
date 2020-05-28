#include "sensors.h"

Sensors::Sensors() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(sensorPins[i], INPUT);
    }
    pinMode(EMITTER, OUTPUT);
    digitalWrite(EMITTER, HIGH);
}

void Sensors::updateSensors() {
    // read analog
    for (int i =0; i < NUM_SENSORS; i++) {
        a_sensorValues[i] = analogRead(sensorPins[i]);
    }
    //could probably put this in the above for loop
   for (int i=0; i <NUM_SENSORS; i++) {
        // if (a_sensorValues[i] > WHITE_THRESHOLD && a_sensorValues[i] < GREEN_RED_THRESHOLD){
        //     sensorValues[i] = 2; //green or red
        // }
        if (a_sensorValues[i] > WHITE_THRESHOLD){
            sensorValues[i] = 1; //black
        }else {
            sensorValues[i] = 0;
        }
    }

    //if indicator is on black and past the cooldown time (new indicator) change state
    if (sensorValues[4] == 1 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        indicatorTimer = millis();
        pathTracker++; 
        state = path[pathTracker];
    }

 
    if (sensorValues[5] == 1 and (rightIndicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        // code for stop
        rightIndicatorTimer = millis();
        stopCounter++;
        if (stopCounter == 7) {
          finishLine = true;
        }
    }
}

/** returns error value based on distance 
 * negative error means the robot is to the left of the line **/

int Sensors::calculateError() {

    if (sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 0) {
        return 0;
    } else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 0 && sensorValues[3] == 0) {
        return 1;
    } else if (sensorValues[0] == 1 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0) {
        return 2;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1 && sensorValues[3] == 1) {
        return -1;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1) {
        return -2;
    } else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1) {
        return 0;
    }
}
