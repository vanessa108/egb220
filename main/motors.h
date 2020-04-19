#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "spark.h"

#define FORWARD LOW
#define R_DIR E6
#define R_PWM D0
#define L_PWM B7
#define L_DIR B0 


class Motors {
    public:
      Motors();
        int motorPins[4] = {L_PWM, L_DIR, R_PWM, R_DIR};
        void driveForward(int speed);
        void driveLeft (int speed);
        void driveRight(int speed);
        void drive(int speed);
    private:
      const int leftBaseSpeed = 100;
      const int rightBaseSpeed = 100;

};

#endif
