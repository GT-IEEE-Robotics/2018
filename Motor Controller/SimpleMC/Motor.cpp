#include "Motor.h"
#include "Arduino.h"

Motor::Motor(uint8_t M_PWM, uint8_t M_DIR_1, uint8_t M_DIR_2, uint8_t M_STBY) {
  
  this->M_PWM = M_PWM;
  this->M_DIR_1 = M_DIR_1;
  this->M_DIR_2 = M_DIR_2;
  this->M_STBY = M_STBY;

  pinMode(M_PWM, OUTPUT);
  pinMode(M_DIR_1, OUTPUT);
  pinMode(M_DIR_2, OUTPUT);
  pinMode(M_STBY, OUTPUT);
}

void Motor::drive(int speed, bool direction) {
  digitalWrite(M_STBY, HIGH);
  
  if (direction){
    digitalWrite(M_DIR_1, HIGH);
    digitalWrite(M_DIR_2, LOW);
  } else {
    digitalWrite(M_DIR_1, LOW);
    digitalWrite(M_DIR_2, HIGH);
  }

  analogWrite(M_PWM, speed);
}

void Motor::brake() {
  digitalWrite(M_STBY, LOW);
  analogWrite(M_PWM, 0);
  digitalWrite(M_DIR_1, LOW);
  digitalWrite(M_DIR_2, LOW);
}
