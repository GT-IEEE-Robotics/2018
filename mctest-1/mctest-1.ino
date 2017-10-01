#define pwm1 3
#define dra1 2
#define drb1 1

#define pwm2 6
#define dra2 4
#define drb2 5

#define pwm3 10
#define dra3 8
#define drb3 9

#define pwm4 11
#define dra4 12
#define drb4 13


void setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(dra1, OUTPUT);
  pinMode(drb1, OUTPUT);

  pinMode(pwm2, OUTPUT);
  pinMode(dra2, OUTPUT);
  pinMode(drb2, OUTPUT);
}

void loop() {
  // forward
  forwardTime(3000);

  // stop
  stopTime(1000);

  // backward
  backwardTime(3000);

  // stop
  stopTime(1000);

  // left
  leftTime(3000);

  // stop
  stopTime(1000);

  // right
  rightTime(3000);
  
  // stop
  stopTime(1000);
}

void motor1(bool dir, int speed) {
  analogWrite(pwm1, speed);
  if (dir) {
    digitalWrite(dra1, LOW);
    digitalWrite(drb1, HIGH);
  } else {
    digitalWrite(dra1, HIGH);
    digitalWrite(drb1, LOW);
  }
}

void motor2(bool dir, int speed) {
  analogWrite(pwm2, speed);
  if (dir) {
    digitalWrite(dra2, LOW);
    digitalWrite(drb2, HIGH);
  } else {
    digitalWrite(dra2, HIGH);
    digitalWrite(drb2, LOW);
  }
}

void motor3(bool dir, int speed) {
  analogWrite(pwm3, speed);
  if (dir) {
    digitalWrite(dra3, LOW);
    digitalWrite(drb3, HIGH);
  } else {
    digitalWrite(dra3, HIGH);
    digitalWrite(drb3, LOW);
  }
}

void motor4(bool dir, int speed) {
  analogWrite(pwm4, speed);
  if (dir) {
    digitalWrite(dra4, LOW);
    digitalWrite(drb4, HIGH);
  } else {
    digitalWrite(dra4, HIGH);
    digitalWrite(drb4, LOW);
  }
}

void stopTime(int microseconds) {
  motor1(true, 0);
  motor2(true, 0);
  motor3(true, 0);
  motor4(true, 0);
  delay(microseconds);
}

void forwardTime(int microseconds) {
  motor1(true, 100);
  motor2(true, 100);
  motor3(true, 100);
  motor4(true, 100);
  delay(microseconds);
}

void backwardTime(int microseconds) {
  motor1(false, 100);
  motor2(false, 100);
  motor3(false, 100);
  motor4(false, 100);
  delay(microseconds);
}

void leftTime(int microseconds) {
  motor1(false, 100);
  motor2(true, 100);
  motor3(true, 100);
  motor4(false, 100);
  delay(microseconds);
}

void rightTime(int microseconds) {
  motor1(true, 100);
  motor2(false, 100);
  motor3(false, 100);
  motor4(true, 100);
  delay(microseconds);
}



