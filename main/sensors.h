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
//states
#define ON_STRAIGHT 0
#define ON_CURVE   1

#define INDICATOR_COOLDOWN 170

#define NUM_SENSORS 6
// 8 (left) -> 1 (right)

class Sensors {
    public:
        Sensors(); //initialise class
        //sensor pins left to right 
        //sensor[1], sensor[2] are for line following , sensor[4], sensor[5] for curve line //sensor_8 and 4 for pid
        //  ROBOT POV sensor_8 is left most 
        char sensorPins[NUM_SENSORS] = {SENSOR_8, SENSOR_7, SENSOR_6, SENSOR_4, SENSOR_2, SENSOR_1};
        void updateSensors();
        int sensorValues[NUM_SENSORS];
        bool onStraight = true;
        int calculateError();
    private:
        int a_sensorValues[NUM_SENSORS];
        long indicatorTimer = 0;
};





#endif
