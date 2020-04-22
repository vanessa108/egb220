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
//threshold for detecting black
#define WHITE_THRESHOLD 100
//states
#define ON_STRAIGHT 0
#define ON_CURVE   1
//cool down for the indicator (this prevents the indicator blinking on and off while over a line)
#define INDICATOR_COOLDOWN 100

#define NUM_SENSORS 7
// 8 (left) -> 1 (right)

class Sensors {
    public:
        /**
         * Sets the pin mode for the sensors as input, turns on emitter LED **/
        Sensors(); //initialise class
        //sensor pins left to right   ROBOT POV sensor_8 is left most 
        char sensorPins[NUM_SENSORS] = {SENSOR_8, SENSOR_7, SENSOR_6, SENSOR_4, SENSOR_3 ,SENSOR_2, SENSOR_1};
        /**
         * reads the sensor values and sets them to either black or white
         * checks if the curve line sensor has detected an indicator and toggles states 
         **/
        void updateSensors();
        int sensorValues[NUM_SENSORS];
        bool onStraight = true;
        /**
         * determines the position error of the robot **/
        int calculateError();
    private:
        int a_sensorValues[NUM_SENSORS];
        long indicatorTimer = 0;
};



#endif
