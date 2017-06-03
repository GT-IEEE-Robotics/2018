#include "Motor.h"

int32_t steps1 = 0;
uint8_t state1 = 0;

void encoder1Count();
void encoder2Count();

Motor motor1 = Motor(&steps1, &state1, 2, 22, 23, 24, 52, 53);

void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(motor1.getEncoder1Pin()), encoder1Count, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor1.getEncoder2Pin()), encoder2Count, CHANGE);
}

void loop() {
  motor1.drive(300);
  delay(1000);
}

void encoder1Count() {
  steps1 += (0 - (state1 & 1)) | 1;
  state1 = state1 ^ 0x1;
}

void encoder2Count() {
  steps1 -= (0 - (state1 & 1)) | 1;
  state1 = state1 ^ 0x3;
}
