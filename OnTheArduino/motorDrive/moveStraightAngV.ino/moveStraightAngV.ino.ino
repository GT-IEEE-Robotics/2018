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

double brVel = 0;
double blVel = 0;
double frVel = 0;
double flVel = 0;

double brCount = 0;
double brCountPrev = 0;
double brRevs = 0;

double blCount = 0;
double blCountPrev = 0;
double blRevs = 0;

double frCount = 0;
double frCountPrev = 0;
double frRevs = 0;

double flCount = 0;
double flCountPrev = 0;
double flRevs = 0;
const int8_t encoder_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

double Ep = 1, Ei = 0, Ed = 0; //double Kp = 2, Ki = 2, Kd = 0.5;
PID backRightPID(&brRevs, &brVel, &brTarget, Ep, Ei, Ed, DIRECT);
PID backLeftPID(&blRevs, &blVel, &blTarget, Ep, Ei, Ed, DIRECT);
PID frontRightPID(&frRevs, &frVel, &frTarget, Ep, Ei, Ed, DIRECT);
PID frontLeftPID(&flRevs, &flVel, &flTarget, Ep, Ei, Ed, DIRECT);

//double setPointHeading;
//double currHeading;
//double rightVel = 30;
//double leftVel = 30;



// PID
//double Kp = 1, Ki = 0, Kd = 0; //double Kp = 2, Ki = 2, Kd = 0.5;
//PID leftPID1(&currHeading, &leftVel, &setPointHeading, Kp, Ki, Kd, REVERSE);
//PID rightPID1(&currHeading, &rightVel, &setPointHeading, Kp, Ki, Kd, DIRECT);
//PID* leftPID = &leftPID1;
//PID* rightPID = &rightPID1;

//Serial communication with pi
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void initPIDs() {
  //leftPID->ResetFunction();
  //rightPID->ResetFunction();
  //leftPID->Compute();
  //rightPID->Compute();
}

void writeMotor(int motorControlPin, int motorSpeedPin, int val) {
  if (val < 0) {
    digitalWrite(motorControlPin, LOW);
  } else {
    digitalWrite(motorControlPin, HIGH);
  }

  analogWrite(motorSpeedPin, abs(val));
}

class Gyro {
    // SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

  private:
    double sum_x = 0;
    double sum_y = 0;
    double sum_z = 0;
    double mill = 0;
    unsigned long prevTime = 0;
    LSM9DS1 imu;

  public:

    // pin number is the GPIO powering the IMU (that can be used to reset IMU if necessary)
    void init(int pinNumber) {
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH);
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
        // added a resetting the imu loop for robustness
        while (1) {
          digitalWrite(pinNumber, HIGH);
          Serial.println("Retrying IMU");
          delay(100);
          if (imu.begin()) {
            break;
          }
          digitalWrite(pinNumber, LOW);
          delay(100);
        };
      }
    }

    void reset() {
      sum_x = 0;
      sum_y = 0;
      sum_z = 0;
    }

    void addGyro() {
      if (imu.gyroAvailable()) {
        imu.readGyro();
        unsigned long curTime = millis();
        sum_x = sum_x + (imu.calcGyro(imu.gx)) * (curTime - prevTime) / 1000.0;
        sum_y = sum_y + (imu.calcGyro(imu.gy)) * (curTime - prevTime) / 1000.0;
        sum_z = sum_z + (imu.calcGyro(imu.gz)) * (curTime - prevTime) / 1000.0;
        prevTime = curTime;
      }
    }
    void addGyroZ() {
      if (imu.gyroAvailable()) {
        double tolerance = 0.02;
        //imu.readGyro(lsm9ds1_axis::Z_AXIS);
        imu.readGyro();
        unsigned long curTime = millis();
        double dumm = (imu.calcGyro(imu.gz)) * (curTime - prevTime) / 1000.0;
        if (dumm > tolerance || dumm < -(tolerance)) {
          sum_z = sum_z + dumm;
        }
        prevTime = curTime;
      }
    }

    double getX() {
      return sum_x;
    }
    double getY() {
      return sum_y;
    }
    double getZ() {
      return sum_z;
    }
    void printGyro()
    {
      if ( imu.gyroAvailable() )
      {
        imu.readGyro();
        // Now we can use the gx, gy, and gz variables as we please.
        // Either print them as raw ADC values, or calculated in DPS.
        Serial.print("G: ");
#ifdef PRINT_CALCULATED
        // If you want to print calculated values, you can use the
        // calcGyro helper function to convert a raw ADC value to
        // DPS. Give the function the value that you want to convert.
        Serial.print(imu.calcGyro(imu.gx), 2);
        Serial.print(", ");
        Serial.print(imu.calcGyro(imu.gy), 2);
        Serial.print(", ");
        Serial.print(imu.calcGyro(imu.gz), 2);
        Serial.println(" deg/s");
#endif
        Serial.print("sum_x = ");
        Serial.print(sum_x);
        Serial.print(" sum_y = ");
        Serial.print(sum_y);
        Serial.print(" sum_z = ");
        Serial.println(sum_z);
      }
    }
};

Gyro gyro1;

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

  backRightPID.SetMode(AUTOMATIC);
  backLeftPID.SetMode(AUTOMATIC);
  frontRightPID.SetMode(AUTOMATIC);
  frontLeftPID.SetMode(AUTOMATIC);

  attachInterrupt(digitalPinToInterrupt(FL_PIN_1), econder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FL_PIN_2), econder_interrupt_fl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_PIN_1), econder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FR_PIN_2), econder_interrupt_fr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_PIN_1), econder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BL_PIN_2), econder_interrupt_bl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_PIN_1), econder_interrupt_br, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BR_PIN_2), econder_interrupt_br, CHANGE);
  
  

//  setPointHeading = getHeading();
  //leftPID->SetMode(AUTOMATIC);
  //rightPID->SetMode(AUTOMATIC);

  //serial communication setup with pi
  inputString.reserve(200);

  //imu setup
  gyro1.init(30);
}

boolean shouldRun = true;



//avoid using delays in loop because
//will mess up serial pi communication
void loop() {
//  currHeading = getHeading();
//
//  leftPID->Compute();
//  rightPID->Compute();
  pidEncoders();
  writeMotor(FL_CONTROL, FL, flVel);
  writeMotor(FR_CONTROL, FR, frVel);
  writeMotor(BL_CONTROL, BL, blVel);
  writeMotor(BR_CONTROL, BR, brVel);

  if (inputString == "FORWARD") {
    driveForward();
  } else if (inputString == "BACKWARD") {
    driveBackward();
  } else if (inputString == "LEFT") {
    driveLeft();
  } else if (inputString == "RIGHT") {
    driveRight();
  } else if (inputString == "CW") {
    rotateCW();
  } else if (inputString == "CCW") {
    rotateCCW();
  } else if (inputString == "STOP") {
    stopRobot();
  } else if (inputString == "NEWHEADING") {
    //setPointHeading = getHeading();
    initPIDs();
  }

  //reads the input from the pi
  if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //Serial.print(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      int dumm = inputString.indexOf("@");
      String speedString = inputString.substring(dumm + 1, inputString.length() - 1);
      inputString = inputString.substring(0, dumm);
      Serial.println(inputString);
      //leftVel = speedString.toInt();
      //rightVel = speedString.toInt();
      stringComplete = true;
    }
  }
  //Serial.println(inputString);
}

void pidEncoders() {
  static uint32_t lastBRTime = 0;
  static uint32_t lastBLTime = 0;
  static uint32_t lastFRTime = 0;
  static uint32_t lastFLTime = 0;  
  uint32_t timeDiff = millis() - lastBRTime;
  brRevs = (brCount - brCountPrev) / double(timeDiff);
  lastBRTime = millis();
  brCountPrev = brCount;
  
  timeDiff = millis() - lastBLTime;
  blRevs = (blCount - blCountPrev) / double(timeDiff);
  lastBLTime = millis();
  blCountPrev = blCount;

  timeDiff = millis() - lastFRTime;
  frRevs = (frCount - frCountPrev) / double(timeDiff);
  lastFRTime = millis();
  frCountPrev = frCount;

  timeDiff = millis() - lastFLTime;
  flRevs = (flCount - flCountPrev) / double(timeDiff);
  lastFLTime = millis();
  flCountPrev = flCount;

  backRightPID.Compute();
  backLeftPID.Compute();
  frontRightPID.Compute();
  frontLeftPID.Compute();
  //Serial.print("computeDone");
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

void driveForward() {
  // direction
  //uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  //setDirs(dirs);

  brTarget = 2.0;
  blTarget = 2.0;
  frTarget = 2.0;
  flTarget = 2.0;
}

void driveBackward() {
  // directionpi
  //uint8_t dirs[4] = {HIGH, HIGH, HIGH, HIGH};
  //setDirs(dirs);

  brTarget = -2.0;
  blTarget = -2.0;
  frTarget = -2.0;
  flTarget = -2.0;
}

void driveRight() {
  // direction
//  uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
//  setDirs(dirs);
//
//
//  // speed
//  setSpeeds(leftVel, rightVel);
  flTarget = -50.0;
  frTarget = 50.0;
  blTarget = 50.0;
  brTarget = -50.0;
}

void driveLeft() {
  // direction
  //uint8_t dirs[4] = {HIGH, LOW, LOW, HIGH};
  //setDirs(dirs);

  flTarget = 2.0;
  frTarget = -2.0;
  blTarget = -2.0;
  brTarget = 2.0;
}

void rotateCCW() {
  // direction
  //uint8_t dirs[4] = {LOW, HIGH, LOW, HIGH};
  //setDirs(dirs);

  flTarget = -2.0;
  frTarget = 2.0;
  blTarget = -2.0;
  brTarget = 2.0;
}

void rotateCW() {
  // direction
  //uint8_t dirs[4] = {HIGH, LOW, HIGH, LOW};
  //setDirs(dirs);

  flTarget = 2.0;
  frTarget = -2.0;
  blTarget = 2.0;
  brTarget = -2.0;
}

void stopRobot() {
  //uint8_t dirs[4] = {LOW, LOW, LOW, LOW};
  //setDirs(dirs);

  flTarget = 0.0;
  frTarget = 0.0;
  blTarget = 0.0;
  brTarget = 0.0;
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

