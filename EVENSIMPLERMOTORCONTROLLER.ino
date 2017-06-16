void brake();
void motor1(int, bool);
void motor2(int, bool);
void motor3(int, bool);
void motor4(int, bool);
void forward(int);
void backward(int);
void left(int);
void right(int);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  brake();
}

void loop() {
  forward(128);
  delay(3000);
  left(128);
  delay(3000);
  backward(128);
  delay(3000);
  right(128);
  delay(3000);
  brake();
  while (true) delay(1000); // the end
}

void brake() {
  analogWrite(2, 0);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(7, 0);
  analogWrite(8, 0);
  analogWrite(9, 0);
}

void forward(int speed) {
  motor1(speed, 0);
  motor2(speed, 0);
  motor3(speed, 0);
  motor4(speed, 0);
}

void backward(int speed) {
  motor1(speed, 1);
  motor2(speed, 1);
  motor3(speed, 1);
  motor4(speed, 1);
}

void left(int speed) {
  motor1(speed, 1);
  motor2(speed, 0);
  motor3(speed, 1);
  motor4(speed, 0);
}

void right(int speed) {
  motor1(speed, 0);
  motor2(speed, 1);
  motor3(speed, 0);
  motor4(speed, 1);
}

void motor1(int speed, bool direction) {
  analogWrite(8, 0);
  analogWrite(9, 0);
  if (!direction) {
    analogWrite(8, speed);
  } else {
    analogWrite(9, speed);
  }
}

void motor2(int speed, bool direction) {
  analogWrite(6, 0);
  analogWrite(7, 0);
  if (direction) {
    analogWrite(6, speed);
  } else {
    analogWrite(7, speed);
  }
}

void motor3(int speed, bool direction) {
  analogWrite(4, 0);
  analogWrite(5, 0);
  if (direction) {
    analogWrite(4, speed);
  } else {
    analogWrite(5, speed);
  }
}

void motor4(int speed, bool direction) {
  analogWrite(2, 0);
  analogWrite(3, 0);
  if (!direction) {
    analogWrite(2, speed);
  } else {
    analogWrite(3, speed);
  }
}
