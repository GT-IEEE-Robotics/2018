#include "Motor.h"

Motor* motor1 = new Motor(2, 22, 23, 24, 52, 53);

void setup() {
  Serial.begin(9600);


}

void loop() {
  motor1->drive(300);
  delay(1000);
}
