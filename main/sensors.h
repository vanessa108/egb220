#ifndef SENSORS_H
#define SENSORS_H

#include "spark.h"
#include <arduino.h>

#define SENSOR_1 F4
#define SENSOR_2 F5
#define SENSOR_3 F6
#define SENSOR_4 F7
#define SENSOR_5 B4
#define SENSOR_6 D7
#define SENSOR_7 D6
#define SENSOR_8 D4

#define EMITTER B3

#define WHITE_THRESHOLD 50

#define NUM_SENSORS 2
// 8 (left) -> 1 (right)

class Sensors {
    public:
        Sensors(); //initialise class
        char sensorPins[NUM_SENSORS] = {SENSOR_1, SENSOR_4};
        void updateSensors();
        int sensorValues[NUM_SENSORS];
    private:
        int a_sensorValues[NUM_SENSORS];
};





#endif
