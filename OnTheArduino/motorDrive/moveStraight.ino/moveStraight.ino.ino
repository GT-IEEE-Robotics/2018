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


// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. CalculatePIPI
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 5.167 // Declination (degrees) in Boulder, CO.

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
      addGyroZ();
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

//imu global
Gyro gyro1;

// PID
double Kp = 1, Ki = 0, Kd = 0.01; //double Kp = 2, Ki = 2, Kd = 0.5;
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



  //serial communication setup with pi
  inputString.reserve(200);

  //imu setup
  gyro1.init(30);
  gyro1.reset();
  setPointHeading = gyro1.getZ();
  leftPID->SetMode(AUTOMATIC);
  rightPID->SetMode(AUTOMATIC);
}

boolean shouldRun = true;



//avoid using delays in loop because
//will mess up serial pi communication
void loop() {
  currHeading = gyro1.getZ();

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
    gyro1.reset();
    setPointHeading = gyro1.getZ();
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
    Serial.print(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == 33) {
      inputString = "";
    } else if (inChar == '\n') {
      int dumm = inputString.indexOf("@");
      String speedString = inputString.substring(dumm + 1, inputString.length() - 1);
      inputString = inputString.substring(0, dumm);
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

