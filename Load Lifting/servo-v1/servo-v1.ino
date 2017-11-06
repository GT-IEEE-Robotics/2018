#include <Servo.h>

Servo servo1, servo2;

int pos = 0;

void setup() {
  servo1.attach(A0);
  servo2.attach(A1);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    servo1.write(pos);
    servo2.write(180 - pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo1.write(pos);
    servo2.write(180 - pos);
    delay(15);
  }
}
