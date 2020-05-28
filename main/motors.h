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
      //sets motor pin modes to output
      Motors();
        int motorPins[4] = {L_PWM, L_DIR, R_PWM, R_DIR};
        void drive(int speed);
        int baseSpeed = 75;
        // speed = 100 -> 333mm/s
        //aprox 45 for 100mm/s
    private:
      

};

#endif
