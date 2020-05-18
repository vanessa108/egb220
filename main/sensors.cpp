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
        if (a_sensorValues[i] < RED_THRESHOLD && a_sensorValues[i] > GREEN_THRESHOLD) {
            sensorValues[i] = 3; //red
        } else if (a_sensorValues[i] > WHITE_THRESHOLD && a_sensorValues[i] < GREEN_THRESHOLD){
            sensorValues[i] = 2; //green
        }else if (a_sensorValues[i] > WHITE_THRESHOLD && a_sensorValues[i] > GREEN_THRESHOLD && a_sensorValues[i] > RED_THRESHOLD){
            sensorValues[i] = 1; //black
        }else {
            sensorValues[i] = 0;
        }
    }

    //if indicator is on black and past the cooldown time (new indicator) change state
    if (sensorValues[6] == 1 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        indicatorTimer = millis();
        onStraight = !onStraight;
    }
    //if indicator is on green and past the cooldown time (new indicator) change state
	if (sensorValues[6] == 2 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        indicatorTimer = millis();
        onSlow = !onSlow;
    }
	if (sensorValues[6] == 3 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        indicatorTimer = millis();
        onSlow = onSlow;
    }
}

/** returns error value based on distance 
 * negative error means the robot is to the left of the line **/

int Sensors::calculateError() {
    // int weightedAverage = (5000*sensorValues[0] + 4000*sensorValues[1] + 3000*sensorValues[2] + 2000*sensorValues[3]
    //                         + 1000*sensorValues[4] + 0*sensorValues[5]) /
    //                         (sensorValues[0]+sensorValues[1]+ sensorValues[2]+sensorValues[3]+sensorValues[4]+ sensorValues[5]);
    
    // return weightedAverage;
    if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 0 && sensorValues[5] == 0) {
        return 0;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
        return 1;
    } else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
        return 2;
    } else if (sensorValues[0] == 1 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
        return 3;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 0) {
        return -1;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 1 && sensorValues[5] == 1) {
        return -2;
    } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 1) {
        return -3;
    }else {
      return 0;
    }
}
