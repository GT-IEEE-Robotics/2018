#include "Motor.h"
#include "Arduino.h"

Motor::Motor(volatile int32_t* steps, volatile uint8_t* state, uint8_t M_PWM, uint8_t M_DIR_1, uint8_t M_DIR_2, uint8_t M_STBY, uint8_t ENC_1, uint8_t ENC_2) {
  this->steps = steps;
  this->state = state;

  kpNumer = 3;
  kpDenom = 128;
  kiNumer = 0;
  kiDenom = 100;

  this->M_PWM = M_PWM;
  this->M_DIR_1 = M_DIR_1;
  this->M_DIR_2 = M_DIR_2;
  this->M_STBY = M_STBY;
  this->ENC_1 = ENC_1;
  this->ENC_2 = ENC_2;

  pinMode(M_PWM, OUTPUT);
  pinMode(M_DIR_1, OUTPUT);
  pinMode(M_DIR_2, OUTPUT);
  pinMode(M_STBY, OUTPUT);
  pinMode(ENC_1, INPUT);
  pinMode(ENC_2, INPUT);
  
  if (digitalRead(ENC_1)) {
    *this->state |= 0x2;
    Serial.println("hello");
  }
  if (digitalRead(ENC_2)) *this->state |= 0x1;
}

void Motor::drive(int amount) {
  bool done = false;
  int error = 0;
  int lastError = 0;
  //int totalError = 0;
  unsigned long graphLastMillis = 0;
  unsigned long ctrlLastMicros = 0;
  const int GRAPH_MILLIS_PERIOD = 10;
  const int CTRL_MICROS_PERIOD = 10;

  digitalWrite(M_STBY, HIGH);

  while (!done) {
    if(micros() - ctrlLastMicros > CTRL_MICROS_PERIOD) { // controlled encoder checking
      ctrlLastMicros = micros();

      noInterrupts();
      error = amount - *steps;
      interrupts();
  
      if (abs(lastError - error) < 10 && abs(error) < 100) {
        done = true;
        // break;
      }

      lastError = error;
      //totalError += error;

      if (*steps < amount) {
        digitalWrite(M_DIR_1, LOW);
        digitalWrite(M_DIR_2, HIGH);
      }
      if (*steps > amount) {
        digitalWrite(M_DIR_1, HIGH);
        digitalWrite(M_DIR_2, LOW);
      }

      int output = kpNumer * error / kpDenom;
      analogWrite(M_PWM, constrain(abs(output), 100, 250));

      if (millis() - graphLastMillis > GRAPH_MILLIS_PERIOD) { // controlled encoder printing
        Serial.print("Error: ");
        Serial.println(error);
        Serial.print("Steps: ");
        Serial.println(*steps);
        graphLastMillis = millis();
      }
    }
  }

  *steps = 0;
  
  // shut the motor down
  analogWrite(M_PWM, 0);
  digitalWrite(M_DIR_1, LOW);
  digitalWrite(M_DIR_2, LOW);
}

void Motor::PIDtuner() { /* coming soon to code near you */ }

int32_t Motor::getSteps() { return *steps; }
uint8_t Motor::getEncoder1Pin() { return ENC_1; }
uint8_t Motor::getEncoder2Pin() { return ENC_2; }
