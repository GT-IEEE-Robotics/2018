#pragma once
#include "Motor.h"

class MotorVelocity : public Motor {
    public:
        MotorVelocity(int pwm, int dir, int enc_a, int enc_b,
                      float p, float i, float d) : Motor(pwm, dir, enc_a, enc_b,
                                                    p,  i,  d) {};
        int update(void);
};

int MotorVelocity::update() {

    // velocity control
    noInterrupts();
    float dx = last_encoder - encoder_count;
    last_encoder = encoder_count;
    interrupts();
    uint32_t now = millis();
    float velocity = dx / (now - last_micros);
    last_micros = now;

    float error = target - velocity;
    float output = pid->update(error);

//    Serial.print("left rear error: "); Serial.println(error);

    if (output > 0) {
        setDirection(1);
    } else {
        setDirection(0);
    }

    Serial.println(encoder_count);

    return constrain(abs(output), 0, 255);
}
