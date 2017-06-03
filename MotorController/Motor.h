#include "Arduino.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int32_t* steps;
    uint8_t* state;
    int32_t kpNumer;
    int32_t kpDenom;
    int32_t kiNumer;
    int32_t kiDenom;

    uint8_t M_PWM;
    uint8_t M_DIR_1;
    uint8_t M_DIR_2;
    uint8_t M_STBY;
    uint8_t ENC_1;
    uint8_t ENC_2;
    
  public:
    Motor(int32_t*, uint8_t*, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    void drive(int);
    void PIDtuner();
    int32_t getSteps();
    uint8_t getEncoder1Pin();
    uint8_t getEncoder2Pin();
};

#endif
