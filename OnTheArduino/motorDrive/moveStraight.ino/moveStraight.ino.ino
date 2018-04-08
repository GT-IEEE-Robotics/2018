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

LSM9DS1 imu;
double setPointHeading;
double currHeading;
double rightVel = 50;
double leftVel = 50;

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
double Kp=2, Ki=2, Kd=0.5;
PID leftPID(&currHeading, &leftVel, &setPointHeading, Kp, Ki, Kd, REVERSE);
PID rightPID(&currHeading, &rightVel, &setPointHeading, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(115200);
  
  // speed pins (pwm. analog write values from 0-255)
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  // motor direction pins (GPIOs)
  pinMode(46,OUTPUT); 
  pinMode(48,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(52,OUTPUT);

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
    while (1)
      ;
  }

  setPointHeading = getHeading();
  setPointHeading = getHeading();
  leftPID.SetMode(AUTOMATIC);
  rightPID.SetMode(AUTOMATIC);
}

boolean shouldRun = true;

void loop() {
//  driveForward(100, 150);
//  delay(3000);+

//  stopRobot();
//  while(1) {
//    };
  if (shouldRun) {
    Serial.print("Set Heading: ");
    Serial.println(setPointHeading);
    currHeading = getHeading();
    Serial.print("Heading: ");
    Serial.println(currHeading);
    leftPID.Compute();
    rightPID.Compute();
    Serial.print("leftVel: ");
    Serial.println(leftVel);
    Serial.print("rightVel: ");
    Serial.println(rightVel);
    driveForward((int) leftVel, (int) rightVel);
  }
//  delay(100);
  if(Serial.available() > 0) {
    while(Serial.available()) {
      Serial.read();
    }
    stopRobot();
    if (shouldRun) {
      shouldRun = false;
    } else {
      shouldRun = true;
    }
  }
}

void driveForward(int leftVel, int rightVel) {
  // direction
  digitalWrite(46, LOW);
  digitalWrite(48, LOW);
  digitalWrite(50, LOW);
  digitalWrite(52, LOW);
  
  // speed
  analogWrite(FL, leftVel);
  analogWrite(BL, leftVel);
  analogWrite(FR, rightVel);
  analogWrite(BR, rightVel);
}

void stopRobot() {
  digitalWrite(46,LOW);
  digitalWrite(48,LOW);
  digitalWrite(50,LOW);
  digitalWrite(52,LOW);
  analogWrite(FL,0);
  analogWrite(FR,0);
  analogWrite(BL,0);
  analogWrite(BR,0);
}

double getHeading() {
  if (imu.magAvailable()) {
    imu.readMag();
  }
  
  float mx = -imu.mx;
  float my = -imu.my;
  double heading;
  
  if (my == 0) {
    heading = (mx < 0) ? PI : 0;
  } else {
    heading = atan2(mx, my);
  }
    
  heading -= DECLINATION * PI / 180;
  
  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
  else if (heading < 0) heading += 2 * PI;
  
  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;

  return heading;
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

