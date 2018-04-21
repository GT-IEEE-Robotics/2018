#pragma once
#include "Motor.h"

class MotorPosition : public Motor {
    public:
        MotorPosition(int pwm, int dir, int enc_a, int enc_b,
                      float p, float i, float d) : Motor(pwm, dir, enc_a, enc_b,
                                                    p,  i,  d) {};
        int update(void);
};

int MotorPosition::update() {

    noInterrupts();
    float error = target - encoder_count;
    interrupts();

    float output = pid->update(error);

    if (output > 0) {
        setDirection(1);
    } else {
        setDirection(0);
    }

    return constrain(abs(output), 0, 255);

    // setSpeed(output);
}