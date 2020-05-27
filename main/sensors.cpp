#include "sensors.h"
#define COUNTER 0

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
        onStraight = !onStraight;
    }


    
	// if (sensorValues[6] == 2 && COUNTER == 0 && COUNTER == 2 && COUNTER == 4 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
    //     indicatorTimer = millis();
    //     onSlow = !onSlow;
	// 	COUNTER++;
    // }
	// if (sensorValues[6] == 2 && COUNTER == 1 && COUNTER == 3 && COUNTER == 5 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
    //     indicatorTimer = millis();
    //     onSlow = onSlow;
	// 	COUNTER++;
    //}
    if (sensorValues[5] == 1) {
        // code for stop
    }
}

/** returns error value based on distance 
 * negative error means the robot is to the left of the line **/

int Sensors::calculateError() {
    // int weightedAverage = (5000*sensorValues[0] + 4000*sensorValues[1] + 3000*sensorValues[2] + 2000*sensorValues[3]
    //                         + 1000*sensorValues[4] + 0*sensorValues[5]) /
    //                         (sensorValues[0]+sensorValues[1]+ sensorValues[2]+sensorValues[3]+sensorValues[4]+ sensorValues[5]);
    
    // return weightedAverage;
    // if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 0 && sensorValues[5] == 0) {
    //     return 0;
    // } else if (sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
    //     return 1;
    // } else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
    //     return 2;
    // } else if (sensorValues[0] == 1 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0) {
    //     return 3;
    // } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 0) {
    //     return -1;
    // } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 1 && sensorValues[5] == 1) {
    //     return -2;
    // } else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 1) {
    //     return -3;
    // }else {
    //   return 0;
    // }

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
