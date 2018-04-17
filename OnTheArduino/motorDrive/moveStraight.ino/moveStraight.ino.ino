#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <PID_v1.h>

// put your setup code here, to run once:
// F = forward, B = backward
// R = right side, L = left side
// define pins for each motor speed & direction:
// not sure on these but I'm guessing:
#define BR (8)
#define BL (9)
#define FR (10)
#define FL (11)

#define TURN_SPEED 30

LSM9DS1 imu;
double setPointHeading;
double currHeading;
double rightVel = 30;
double leftVel = 30;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 5.167 // Declination (degrees) in Boulder, CO.

// PID
double Kp = 1, Ki = 0, Kd = 0; //double Kp = 2, Ki = 2, Kd = 0.5;
PID leftPID1(&currHeading, &leftVel, &setPointHeading, Kp, Ki, Kd, REVERSE);
PID rightPID1(&currHeading, &rightVel, &setPointHeading, Kp, Ki, Kd, DIRECT);
PID* leftPID = &leftPID1;
PID* rightPID = &rightPID1;

//Serial communication with pi
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void initPIDs() {
  leftPID->ResetFunction();
  rightPID->ResetFunction();
  leftPID->Compute();
  rightPID->Compute();
}

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

  //imu power gpio
  pinMode(30, OUTPUT);
  digitalWrite(30, HIGH);
  //initPIDs();

  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1) {
      digitalWrite(30, LOW);
      delay(100);
      digitalWrite(30, HIGH);
      if (imu.begin()) {
        break;
      }
    }
      ;
  }

  setPointHeading = getHeading();
  leftPID->SetMode(AUTOMATIC);
  rightPID->SetMode(AUTOMATIC);

  //serial communication setup with pi
  inputString.reserve(200);
  //delay(100);
}

boolean shouldRun = true;



//avoid using delays in loop because
//will mess up serial pi communication
void loop() {
  currHeading = getHeading();

  leftPID->Compute();
  rightPID->Compute();

  if (inputString == "FORWARD") {
    driveForward((int) leftVel, (int) rightVel);
  } else if (inputString == "BACKWARD") {
    driveBackward((int) leftVel, (int) rightVel);
  } else if (inputString == "LEFT") {
    driveLeft((int) leftVel, (int) rightVel);
  } else if (inputString == "RIGHT") {
    driveRight((int) leftVel, (int) rightVel);
  } else if (inputString == "CW") {
    rotateCW();
  } else if (inputString == "CCW") {
    rotateCCW();
  } else if (inputString == "STOP") {
    stopRobot();
  } else if (inputString == "NEWHEADING") {
    Serial.print("Heading: ");
    Serial.println(setPointHeading);
    setPointHeading = getHeading();
    initPIDs();
    Serial.print("New Heading: ");
    Serial.println(setPointHeading);
  }

  //reads the input from the pi
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n'){
      int dumm = inputString.indexOf("@");
      String speedString = inputString.substring(dumm+1, inputString.length() - 1);
      inputString = inputString.substring(0,dumm);
      leftVel = speedString.toInt();
      rightVel = speedString.toInt();
      stringComplete = true;
    }
  }
  Serial.println(inputString);
}

void setDirs(uint8_t dirs[]) {
  digitalWrite(46, dirs[0]);
  digitalWrite(48, dirs[1]);
  digitalWrite(50, dirs[2]);
  digitalWrite(52, dirs[3]);
}

void setSpeeds(int leftVel, int rightVel) {
  analogWrite(FL, leftVel);
  analogWrite(BL, leftVel);
  analogWrite(FR, rightVel);
  analogWrite(BR, rightVel);
}

void driveForward(int leftVel, int rightVel) {
  // direction
//  digitalWrite(46, LOW);
//  digitalWrite(48, LOW);
//  digitalWrite(50, LOW);
//  digitalWrite(52, LOW);  
  uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  setDirs(dirs);


  // speed
  setSpeeds(leftVel, rightVel);
//  analogWrite(FL, leftVel);
//  analogWrite(BL, leftVel);
//  analogWrite(FR, rightVel);
//  analogWrite(BR, rightVel);
}

void driveBackward(int leftVel, int rightVel) {
  // direction
//  digitalWrite(46, HIGH);
//  digitalWrite(48, HIGH);
//  digitalWrite(50, HIGH);
//  digitalWrite(52, HIGH);
  uint8_t dirs[4] = {HIGH, HIGH, HIGH, HIGH};
  setDirs(dirs);

  // speed
  setSpeeds(leftVel, rightVel);
//  analogWrite(FL, leftVel);
//  analogWrite(BL, leftVel);
//  analogWrite(FR, rightVel);
//  analogWrite(BR, rightVel);
}

void driveRight(int leftVel, int rightVel) {
  // direction
//  digitalWrite(46, LOW);
//  digitalWrite(48, HIGH);
//  digitalWrite(50, HIGH);
//  digitalWrite(52, LOW);
  uint8_t dirs[4] = {LOW, HIGH, HIGH, LOW};
  setDirs(dirs);


  // speed
  setSpeeds(leftVel, rightVel);
//  analogWrite(FL, leftVel);
//  analogWrite(BL, leftVel);
//  analogWrite(FR, rightVel);
//  analogWrite(BR, rightVel);
}

void driveLeft(int leftVel, int rightVel) {
  // direction
//  digitalWrite(46, HIGH);
//  digitalWrite(48, LOW);
//  digitalWrite(50, LOW);
//  digitalWrite(52, HIGH);
  uint8_t dirs[4] = {HIGH, LOW, LOW, HIGH};
  setDirs(dirs);

  // speed
  setSpeeds(leftVel, rightVel);
//  analogWrite(FL, leftVel);
//  analogWrite(BL, leftVel);
//  analogWrite(FR, rightVel);
//  analogWrite(BR, rightVel);
}

void rotateCCW() {
  // direction
//  digitalWrite(46, LOW);
//  digitalWrite(48, HIGH);
//  digitalWrite(50, LOW);
//  digitalWrite(52, HIGH);
  uint8_t dirs[4] = {LOW, HIGH, LOW, HIGH};
  setDirs(dirs);

  // speed
  setSpeeds(TURN_SPEED, TURN_SPEED);
//  analogWrite(FL, TURN_SPEED);
//  analogWrite(BL, TURN_SPEED);
//  analogWrite(FR, TURN_SPEED);
//  analogWrite(BR, TURN_SPEED);
}

void rotateCW() {
  // direction
//  digitalWrite(46, HIGH);
//  digitalWrite(48, LOW);
//  digitalWrite(50, HIGH);
//  digitalWrite(52, LOW);
  uint8_t dirs[4] = {HIGH, LOW, HIGH, LOW};
  setDirs(dirs);

  // speed
  setSpeeds(TURN_SPEED, TURN_SPEED);
//  analogWrite(FL, TURN_SPEED);
//  analogWrite(BL, TURN_SPEED);
//  analogWrite(FR, TURN_SPEED);
//  analogWrite(BR, TURN_SPEED);
}

void stopRobot() {
//  digitalWrite(46, LOW);
//  digitalWrite(48, LOW);
//  digitalWrite(50, LOW);
//  digitalWrite(52, LOW);
  uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  setDirs(dirs);

  setSpeeds(0, 0);
//  analogWrite(FL, 0);
//  analogWrite(FR, 0);
//  analogWrite(BL, 0);
//  analogWrite(BR, 0);
}

double getHeading() {
  int i = 0;
  double headingSum = 0;
  int averageLength = 100;
  for (i = 0; i < averageLength; i++) {
    if (imu.magAvailable()) {
      imu.readMag();
    }
    //    if (imu.gyroAvailable()) {
    //      imu.readGyro();
    //    }

    //    float xval = -imu.calcGyro(imu.gx);
    //    float yval = -imu.calcGyro(imu.gy);
    float xval = -imu.mx;
    float yval = -imu.my;
    double heading;

    if (yval == 0) {
      heading = (xval < 0) ? PI : 0;
    } else {
      heading = atan2(xval, yval);
    }

    heading -= DECLINATION * PI / 180;

    if (heading > PI) heading -= (2 * PI);
    else if (heading < -PI) heading += (2 * PI);
    else if (heading < 0) heading += 2 * PI;

    // Convert everything from radians to degrees:
    heading *= 180.0 / PI;
    headingSum += heading;
  }

  return headingSum / averageLength;
}

//void driveBackward(int magnitude) {
//  // direction
//  digitalWrite(46,HIGH);
//  digitalWrite(48,HIGH);
//  digitalWrite(50,HIGH);
//  digitalWrite(52,HIGH);
//  // speed
//  analogWrite(8,magnitude);
//  analogWrite(9,magnitude);
//  analogWrite(10,magnitude);
//  analogWrite(11,magnitude);
//}
//
//void driveLeft(int magnitude) {
//  digitalWrite(46,LOW);
//  digitalWrite(48,HIGH); // reverse
//  digitalWrite(50,HIGH); // reverse
//  digitalWrite(52,LOW);
//  analogWrite(8,magnitude);
//  analogWrite(9,magnitude);
//  analogWrite(10,magnitude);
//  analogWrite(11,magnitude);
//}
//
//void driveRight(int magnitude) {
//  digitalWrite(46,HIGH); // FR?
//  digitalWrite(48,LOW);
//  digitalWrite(50,LOW);
//  digitalWrite(52,HIGH); // BL?
//  analogWrite(8,magnitude);
//  analogWrite(9,magnitude);
//  analogWrite(10,magnitude);
//  analogWrite(11,magnitude);
//}

