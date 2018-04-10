#include "Arduino.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    uint8_t M_PWM;
    uint8_t M_DIR_1;
    uint8_t M_DIR_2;
    uint8_t M_STBY;
    
  public:
    Motor(uint8_t, uint8_t, uint8_t, uint8_t);
    void drive(int, bool);
    void brake();
};

#endif
