#include "motors.h"

Motors::Motors() {
    for (int i = 0; i < 4; i++) {
        pinMode(motorPins[i], OUTPUT);
    }
}

void Motors::driveForward(int speed) {
    for (int i = 0; i <4; i+=2) {
        analogWrite(motorPins[i], speed);
    }
    digitalWrite(L_DIR, HIGH);
    digitalWrite(R_DIR, LOW);
}

void Motors::driveLeft(int speed) {
    analogWrite(R_PWM, speed);
    analogWrite(L_PWM, 0);
    digitalWrite(L_DIR, HIGH);
    digitalWrite(R_DIR, LOW);
}

void Motors::driveRight(int speed) {
    analogWrite(L_PWM, speed);
    analogWrite(R_PWM, 0);
    digitalWrite(L_DIR, HIGH);
    digitalWrite(R_DIR, LOW);
}
