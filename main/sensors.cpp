#include "sensors.h"

Sensors::Sensors() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(sensorPins[i], INPUT);
    }
    pinMode(EMITTER, OUTPUT);
    digitalWrite(EMITTER, HIGH);
}

void Sensors::updateSensors() {
    for (int i =0; i < NUM_SENSORS; i++) {
        a_sensorValues[i] = analogRead(sensorPins[i]);
    }

    for (int i=0; i <NUM_SENSORS; i++) {
        if (a_sensorValues[i] > WHITE_THRESHOLD) {
            sensorValues[i] = 1; //black
        } else {
            sensorValues[i] = 0;
        }
    }

    //if indicator is on black and past the cooldown time (new indicator) change state
    if (sensorValues[3] == 1 and (indicatorTimer + INDICATOR_COOLDOWN <= millis())) {
        indicatorTimer = millis();
        onStraight = !onStraight;
    }
}
