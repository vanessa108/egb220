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

#define STOP_SENSOR D1

#define EMITTER B3
//threshold for detecting black
#define WHITE_THRESHOLD 600
#define GREEN_RED_THRESHOLD

//states
#define ON_CURVE 0
#define ON_STRAIGHT 1
#define ON_SLOW   2
//cool down for the indicator (this prevents the indicator blinking on and off while over a line)
#define INDICATOR_COOLDOWN 105

#define NUM_SENSORS 6
// 8 (left) -> 1 (right)

class Sensors {
    public:
        /**
         * Sets the pin mode for the sensors as input, turns on emitter LED **/
        Sensors(); //initialise class
        //sensor pins left to right   ROBOT POV sensor_8 is left most 
        char sensorPins[NUM_SENSORS] = {SENSOR_7, SENSOR_6, SENSOR_4,SENSOR_3, SENSOR_8,  SENSOR_2};
        /**ujy 
         * reads the sensor values and sets them to either black or white
         * checks if the curve line sensor has detected an indicator and toggles states 
         **/
        void updateSensors();
        int sensorValues[NUM_SENSORS];
        bool onStraight = true;
        int state = 1;
        
        /**
         * determines the position error of the robot **/
        int calculateError();
            // 11
        //int path[21] = {1, 0, 0, 1, 0, 0, 1,1, 0, 1, 0, 0, 1, 2, 1, 0, 1, 0, 1,0,1};
        int path[22] = {1, 0, 0, 1, 0, 0,  1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1,0,1};
        int pathTracker = 0;
        int stopCounter = 0;
        int numToStop = 10;
        long rightIndicatorTimer = 0;
        long startTimer;
        bool finishLine = false;
    private:
        int a_sensorValues[NUM_SENSORS];
        long indicatorTimer = 0;
        
};



#endif
