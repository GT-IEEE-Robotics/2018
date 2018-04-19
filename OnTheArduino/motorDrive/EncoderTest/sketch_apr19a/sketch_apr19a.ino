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
#define BR_CONTROL 52
#define BL (9)
#define BL_CONTROL 50
#define FR (10)
#define FR_CONTROL 48
#define FL (11)
#define FL_CONTROL 46

#define BR_PIN_1 32
#define BR_PIN_2 34
#define BL_PIN_1 36
#define BL_PIN_2 38
#define FR_PIN_1 40
#define FR_PIN_2 42
#define FL_PIN_1 28
#define FL_PIN_2 26

#define TURN_SPEED 30

//Encoder PID setup
const double TARGET_POSITION_REVS = 0.0;
const double ENCODER_TICKS_PER_REV = 4741.44;
double target = ENCODER_TICKS_PER_REV * TARGET_POSITION_REVS;
double brTarget = target, blTarget = target, frTarget = target, flTarget = target;

double brVel = 50;
double blVel = 50;
double frVel = 50;
double flVel = 50;

volatile int brCount = 0;
volatile int brCountPrev = 0;
volatile int brRevs = 0;

volatile int blCount = 0;
volatile int blCountPrev = 0;
volatile int blRevs = 0;

volatile int frCount = 0;
volatile int frCountPrev = 0;
volatile int frRevs = 0;

volatile int flCount = 0;
volatile int flCountPrev = 0;
volatile int flRevs = 0;
const int8_t encoder_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

double Ep = 1, Ei = 0, Ed = 0; //double Kp = 2, Ki = 2, Kd = 0.5;
//PID backRightPID(&brRevs, &brVel, &brTarget, Ep, Ei, Ed, DIRECT);
//PID backLeftPID(&blRevs, &blVel, &blTarget, Ep, Ei, Ed, DIRECT);
//PID frontRightPID(&frRevs, &frVel, &frTarget, Ep, Ei, Ed, DIRECT);
//PID frontLeftPID(&flRevs, &flVel, &flTarget, Ep, Ei, Ed, DIRECT);

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
//  leftPID->ResetFunction();
//  rightPID->ResetFunction();
  leftPID->Compute();
  rightPID->Compute();
}

void writeMotor(int motorControlPin, int motorSpeedPin, int val) {
  if (val < 0) {
    digitalWrite(motorControlPin, LOW);
  } else {
    digitalWrite(motorControlPin, HIGH);
  }

  analogWrite(motorSpeedPin, abs(val));
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
      digitalWrite(30, HIGH);
      Serial.println("Retrying IMU");
      delay(500);
      if (imu.begin()) {
        break;
      }
      digitalWrite(30, LOW);
      delay(300);

    };
  }

//  backRightPID.SetMode(AUTOMATIC);
  //backLeftPID.SetMode(AUTOMATIC);
  //frontRightPID.SetMode(AUTOMATIC);
  //frontLeftPID.SetMode(AUTOMATIC);

  attachInterrupt(digitalPinToInterrupt(FL_PIN_1), econder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FL_PIN_2), econder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_PIN_1), econder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_PIN_2), econder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_PIN_1), econder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_PIN_2), econder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_PIN_1), econder_interrupt_br, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_PIN_2), econder_interrupt_br, CHANGE);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("brCount = ");
  Serial.print(brCount);
  Serial.print(" blCount = ");
  Serial.print(blCount);
  Serial.print(" frCount = ");
  Serial.print(frCount);
  Serial.print(" flCount = ");
  Serial.print(flCount);
  Serial.print("\n");

}

void econder_interrupt_br() {
  static uint8_t br_enc_val = 0;
  br_enc_val = (br_enc_val << 2) | (digitalRead(BR_PIN_1) << 1) | digitalRead(BR_PIN_2);
  brCount = encoder_table[br_enc_val & 0b1111];
}

void econder_interrupt_bl() {
  static uint8_t bl_enc_val = 0;
  bl_enc_val = (bl_enc_val << 2) | (digitalRead(BL_PIN_1) << 1) | digitalRead(BL_PIN_2);
  blCount = encoder_table[bl_enc_val & 0b1111];
}

void econder_interrupt_fr() {
  static uint8_t fr_enc_val = 0;
  fr_enc_val = (fr_enc_val << 2) | (digitalRead(FR_PIN_1) << 1) | digitalRead(FR_PIN_2);
  frCount = encoder_table[fr_enc_val & 0b1111];
}

void econder_interrupt_fl() {
  static uint8_t fl_enc_val = 0;
  fl_enc_val = (fl_enc_val << 2) | (digitalRead(FL_PIN_1) << 1) | digitalRead(FL_PIN_2);
  flCount = encoder_table[fl_enc_val & 0b1111];
}
