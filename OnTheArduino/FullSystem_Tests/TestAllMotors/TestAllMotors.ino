// put your setup code here, to run once:
// F = forward, B = backward
// R = right side, L = left side
// define pins for each motor speed & direction:
// not sure on these but I'm guessing:
#define BR (11)
#define BL (10)
#define FR (8)
#define FL (9)

#define TURN_SPEED 30
double rightVel = 30;
double leftVel = 30;


void setup() {
  Serial.begin(115200);

  // speed pins (pwm. analog write values from 0-255)
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // motor direction pins (GPIOs)
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(52, OUTPUT);
}

boolean shouldRun = true;


#define BL_DIR 50
#define FL_DIR 48
#define FR_DIR 46
#define BR_DIR 52

//avoid using delays in loop because
//will mess up serial pi communication
void testMotor(int motorPin, int motorDir) {
  digitalWrite(motorDir, HIGH);
  analogWrite(motorPin, 60);
  delay(500);
  analogWrite(motorPin, 0);
  digitalWrite(motorDir, LOW);
  analogWrite(motorPin, 60);
  delay(500);
  analogWrite(motorPin, 0);
}

void loop() {
  testMotor(BL, BL_DIR);
  testMotor(FL, FL_DIR);
  testMotor(FR, FR_DIR);
  testMotor(BR, BR_DIR);
  while(1);
}

void setDirs(uint8_t dirs[]) {
  digitalWrite(BL_DIR, dirs[0]);
  digitalWrite(FL_DIR, dirs[1]);
  digitalWrite(FR_DIR, dirs[2]);
  digitalWrite(BR_DIR, dirs[3]);
}

void setSpeeds(int leftVel, int rightVel) {
  analogWrite(FL, leftVel);
  analogWrite(BL, leftVel);
  analogWrite(FR, rightVel);
  analogWrite(BR, rightVel);
}

void driveForward(int leftVel, int rightVel) {
  // direction
  uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  setDirs(dirs);


  // speed
  setSpeeds(leftVel, rightVel);
}

void driveBackward(int leftVel, int rightVel) {
  // direction
  uint8_t dirs[4] = {HIGH, HIGH, HIGH, HIGH};
  setDirs(dirs);

  // speed
  setSpeeds(leftVel, rightVel);
}

void driveRight(int leftVel, int rightVel) {
  // direction
  uint8_t dirs[4] = {LOW, HIGH, HIGH, LOW};
  setDirs(dirs);


  // speed
  analogWrite(FL, leftVel);
  analogWrite(BL, rightVel);
  analogWrite(FR, leftVel);
  analogWrite(BR, rightVel);
}

void driveLeft(int leftVel, int rightVel) {
  // direction
  uint8_t dirs[4] = {HIGH, LOW, LOW, HIGH};
  setDirs(dirs);

  // speed
  analogWrite(FL, leftVel);
  analogWrite(BL, leftVel);
  analogWrite(FR, rightVel);
  analogWrite(BR, rightVel);
}

void rotateCCW() {
  // direction
  uint8_t dirs[4] = {LOW, HIGH, LOW, HIGH};
  setDirs(dirs);

  // speed
  setSpeeds(TURN_SPEED, TURN_SPEED);
}

void rotateCW() {
  // direction
  uint8_t dirs[4] = {HIGH, LOW, HIGH, LOW};
  setDirs(dirs);

  // speed
  setSpeeds(TURN_SPEED, TURN_SPEED);
}

void stopRobot() {
  uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  setDirs(dirs);

  setSpeeds(0, 0);
}
