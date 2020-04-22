#include "motors.h"

Motors::Motors() {
    for (int i = 0; i < 4; i++) {
        pinMode(motorPins[i], OUTPUT);
    }
}

void Motors::drive(int speed) {
    analogWrite(L_PWM, baseSpeed - speed);
    analogWrite(R_PWM, baseSpeed + speed);
    digitalWrite(L_DIR, HIGH);
    digitalWrite(R_DIR, LOW);
}
