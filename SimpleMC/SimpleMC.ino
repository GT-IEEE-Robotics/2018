#include "Motor.h"

/* Function prototypes */
void driveForward(int);
void driveBackward(int);
void driveLeft(int);
void driveRight(int);
void robotBrake();
/* * * * * * * * * * * */


Motor motor1 = Motor(2, 24, 24, 22);
Motor motor2 = Motor(3, 26, 27, 22);
Motor motor3 = Motor(4, 28, 29, 22);
Motor motor4 = Motor(5, 30, 31, 22);

void setup() {
  Serial.begin(9600);
  Serial.println("Program starting...");
}

void loop() {
  driveForward(255);
  delay(3000);
  robotBrake();
  driveLeft(255);
  delay(1000);
  robotBrake();
  driveBackward(255);
  delay(3000);
  robotBrake();
  driveRight(255);
  delay(1000);
  robotBrake();
  while (true) delay(1000);
}


void driveForward(int x) {
  motor1.drive(x, 1);
  motor2.drive(x, 1);
  motor3.drive(x, 1);
  motor4.drive(x, 1);
}

void driveBackward(int x) {
  motor1.drive(x, 0);
  motor2.drive(x, 0);
  motor3.drive(x, 0);
  motor4.drive(x, 0);
}

void driveLeft(int x) {
  motor1.drive(x, 1);
  motor2.drive(x, 0);
  motor3.drive(x, 1);
  motor4.drive(x, 0);
}

void driveRight(int x) {
  motor1.drive(x, 0);
  motor2.drive(x, 1);
  motor3.drive(x, 0);
  motor4.drive(x, 1);
}

void robotBrake() {
  motor1.brake();
  motor2.brake();
  motor3.brake();
  motor4.brake();
}


