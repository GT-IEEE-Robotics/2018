#include "Motor.h"

int32_t steps1 = 0;
uint8_t state1 = 0;
int32_t steps2 = 0;
uint8_t state2 = 0;

void encoder1Count();
void encoder2Count();
void encoder3Count();
void encoder4Count();

Motor motor1 = Motor(&steps1, &state1, 2, 22, 23, 24, 50, 51);
Motor motor2 = Motor(&steps2, &state2, 3, 25, 26, 24, 52, 53);

void setup() {
  Serial.begin(9600);
  Serial.println("Program starting...");

  attachInterrupt(digitalPinToInterrupt(motor1.getEncoder1Pin()), encoder1Count, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor1.getEncoder2Pin()), encoder2Count, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor2.getEncoder1Pin()), encoder3Count, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor2.getEncoder2Pin()), encoder4Count, CHANGE);
}

void loop() {
  motor1.drive(2000);
  Serial.println("here");
  motor1.drive(-2000);
  Serial.println("now here");
}

void encoder1Count() {
  steps1 += (0 - (state1 & 1)) | 1;
  state1 = state1 ^ 0x1;
}

void encoder2Count() {
  steps1 -= (0 - (state1 & 1)) | 1;
  state1 = state1 ^ 0x3;
}

void encoder3Count() {
  steps2 += (0 - (state2 & 1)) | 1;
  state2 = state2 ^ 0x1;
}

void encoder4Count() {
  steps2 -= (0 - (state2 & 1)) | 1;
  state2 = state2 ^ 0x3;
}
