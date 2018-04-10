#include "Arduino.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    uint8_t pwmA1, pwmA2;
    uint8_t pwmB1, pwmB2;
    
  public:
    Motor(uint8_t, uint8_t, uint8_t, uint8_t);
    void drive(int, bool);
    void brake();
};

#endif
