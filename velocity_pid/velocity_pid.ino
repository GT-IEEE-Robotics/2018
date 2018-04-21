// motor pid libraries
#include "MotorVelocity.h"
#include "MotorPosition.h"
// gyro
// #include "IMU.h"
// 7 seg
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
// servo
#include <Servo.h>

int SPEED = 3.5;

#define REV_BASE (4741.44)  // revolution is 1920 counts
#define REV_FLAG (464.64)   // https://www.pololu.com/category/115/25d-mm-metal-gearmotors

/* motor hookups */
// left front
#define PWM1    (9)
#define DIR1    (48)
// right front
#define PWM2    (8)
#define DIR2    (46)
// left rear
#define PWM3    (10)
#define DIR3    (50)
// right rear
#define PWM4    (11)
#define DIR4    (52)
// flag turner
#define PWM5    (12)
#define DIR5    (41)
// flag turner servo pwm
#define FLAG_SERVO  (7)
// treasure box
#define PWM6    (13)
#define DIR6    (39)

/* encoders */
// left front
#define ENC1_A  (42)
#define ENC1_B  (44)
// right front
#define ENC2_A  (24)
#define ENC2_B  (26)
// left rear
#define ENC3_A  (32)
#define ENC3_B  (34)
// right rear
#define ENC4_A  (36)
#define ENC4_B  (38)
// flag turner
#define ENC5_A  (45)
#define ENC5_B  (43)
// treausre box
// #define ENC6_A  ()
// #define ENC6_B  ()

/* PIDs */
// left front
#define P1 (6.0f)
#define I1 (0.00001f)
#define D1 (0.0f)
// right front
#define P2 (6.0f)
#define I2 (0.00001f)
#define D2 (0.0f)
// left rear
#define P3 (6.0f)
#define I3 (0.00001f)
#define D3 (0.0f)
// right rear
#define P4 (6.0f)
#define I4 (0.00001f)
#define D4 (0.0f)
// flag
#define P5 (2.0f)
#define I5 (0.00001f)
#define D5 (0.0f)
// treasure
#define P6 (0.005f)
#define I6 (0.0f)
#define D6 (0.0f)

/* control flow */
#define PID_PERIOD  (10000)    // rate at which PID updates in microseconds

uint32_t last_run = 0,      // last PID run in miliseconds
         curr_run = 0;

MotorVelocity left_front(PWM1, DIR1, ENC1_A, ENC1_B, P1, I1, D1);
MotorVelocity right_front(PWM2, DIR2, ENC2_A, ENC2_B, P2, I2, D2);
MotorVelocity left_rear(PWM3, DIR3, ENC3_A, ENC3_B, P3, I3, D3);
MotorVelocity right_rear(PWM4, DIR4, ENC4_A, ENC4_B, P4, I4, D4);

//MotorPosition flag(PWM5, DIR5, ENC5_A, ENC5_B, P5, P5, P5);
Servo flagServo;
// MotorPosition treasure(PWM6, DIR6, ENC6_A, ENC6_B, P6, P6, P6);

// Define global IMU Gyro Sensor
//imuGyro gyro(0, 0, 0);

void left_front_encoder_isr(void) { left_front.encoder_isr(); }
void right_front_encoder_isr(void) { right_front.encoder_isr(); }
void left_rear_encoder_isr(void) { left_rear.encoder_isr(); }
void right_rear_encoder_isr(void) { right_rear.encoder_isr(); }
//void flag_encoder_isr(void) { flag.encoder_isr(); }


int flag_enc_val;
volatile int32_t flag_encoder_count;

void flag_encoder_isr() {
    flag_enc_val = (flag_enc_val << 2) | (digitalRead(ENC5_A) << 1) | digitalRead(ENC5_B);

    flag_encoder_count += encoder_table[flag_enc_val & 0b1111];
//    Serial.println(encoder_count);
}

// 7 seg
#define SEVEN_SEG (28)
Adafruit_7segment matrix = Adafruit_7segment();
void displayNum(int num) {
  matrix.writeDigitRaw(2, 0x10);
  if (num == 1)
    matrix.writeDigitRaw(4, 0x30); //dec 1
  else if (num == 2)
    matrix.writeDigitRaw(4, 0x5B); //dec 2
  else if (num == 3)
    matrix.writeDigitRaw(4, 0x79); //dec 3
  else if (num == 4)
    matrix.writeDigitRaw(4, 0x74); //dec 4
  else if (num == 5)
    matrix.writeDigitRaw(4, 0x6D); //dec 5
  else if (num == 6)
    matrix.writeDigitRaw(4, 0x6F); //dec 6
  else if (num == 7)
    matrix.writeDigitRaw(4, 0x38); //Dec 7
  else if (num == 8)
    matrix.writeDigitRaw(4, 0xFF); //Dec 8
  else if (num == 9)
    matrix.writeDigitRaw(4, 0x7D); //Dec 9
  matrix.writeDisplay();
  delay(500);
}

// serial stuff with Pi
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {

    // setup serial
    Serial.begin(115200);
    inputString.reserve(200);

    // seven segment output
    pinMode(SEVEN_SEG, OUTPUT);
    digitalWrite(SEVEN_SEG, HIGH);
    matrix.begin(0x70);

    // gyro.init(30);
    // gyro.reset();
    // setPointHeading = gyro1.getZ();

    // set directions
    left_rear.reverseMotor();
    left_front.reverseMotor();
    right_rear.reverseMotor();
//    flag.reverseMotor();
//    right_front.reverseMotor();

    // set targets
//     left_front.setTarget(SPEED);
//     right_front.setTarget(SPEED);
//     left_rear.setTarget(SPEED);
//     right_rear.setTarget(SPEED);

//     flag.setTarget(5*REV_FLAG);

    // start servo
    flagServo.attach(FLAG_SERVO);
    flagServo.write(0);

    // gyro.setTarget(0);
    
    left_front.setInterruptHandler(left_front_encoder_isr);
    right_front.setInterruptHandler(right_front_encoder_isr);
    left_rear.setInterruptHandler(left_rear_encoder_isr);
    right_rear.setInterruptHandler(right_rear_encoder_isr);
//    flag.setInterruptHandler(flag_encoder_isr);

    attachInterrupt(digitalPinToInterrupt(ENC5_A), flag_encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC5_B), flag_encoder_isr, CHANGE);

//    extendFlag();
//    grabChest();
}

void loop() {

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
    } else if (inputString == "FLAG") {
        extendFlag();
    } else if (inputString == "CHEST") {
        grabChest();
    }
    // } else if (inputString == "NEWHEADING") {
    //     gyro1.reset();
    //     setPointHeading = gyro1.getZ();
    //     initPIDs();
    // }

    //reads the input from the pi
    if (stringComplete) {
        // clear the string:
        inputString = "";
        stringComplete = false;
    }


    // determine if it's time to run the PID calculations again
    if (micros() - last_run > PID_PERIOD) {

        // float gyro_command = gyro.update();
        // Serial.print("gryo: "); Serial.println(gyro_command);
        // left_front.updateTarget(5 + gyro_command);
        // right_front.updateTarget(5 + gyro_command);
        // left_rear.updateTarget(5 + gyro_command);
        // right_rear.updateTarget(5 + gyro_command);

        int left_front_command = left_front.update();
        int right_front_command = right_front.update();
        int left_rear_command = left_rear.update();
        int right_rear_command = right_rear.update();
//        int flag_command = flag.update();

        // Serial.print("flag command: "); Serial.println(flag_command);

        left_front.setSpeed(left_front_command);
        right_front.setSpeed(right_front_command);
        left_rear.setSpeed(left_rear_command);
        right_rear.setSpeed(right_rear_command);
//        flag.setSpeed(flag_command);

        last_run = micros();
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
      if (inputString != "IRCODE") {
        // leftVel = speedString.toInt();
        // rightVel = speedString.toInt();
      } else {
        displayNum(speedString.toInt());
      }
      stringComplete = true;
    }
  }
  Serial.println(inputString);
}

void setTargets(float lf, float rf, float lr, float rr) { // 1 or -1 for direction, 0 for stop
    left_front.setTarget(lf * SPEED);
    left_front.setTarget(rf * SPEED);
    left_front.setTarget(lr * SPEED);
    left_front.setTarget(rr * SPEED);
}

void driveForward() {
    setTargets(1, 1, 1, 1);
}
void driveBackward() {
    setTargets(-1, -1, -1, -1);
}
void driveLeft() {
    setTargets(1, -1, 1, -1);
}
void driveRight() {
    setTargets(-1, 1, -1, 1);
}
void rotateCW() {
    setTargets(-1, -1, 1, 1);
}
void rotateCCW() {
    setTargets(1, 1, -1, -1);
}
void stopRobot() {
    setTargets(0, 0, 0, 0);
}
void extendFlag() {

    setTargets(0, 0, 0, 0);
    
    flagServo.write(135);   // extend

    delay(400);             // wait for extension

    digitalWrite(DIR5, LOW);
    analogWrite(PWM5, 25);

    while (abs(flag_encoder_count) < 2250) {}
    
    analogWrite(PWM5, 0);

    delay(250);
    flagServo.write(0);

//    flag.setTarget(5*REV_FLAG); // spin 5 times

    delay(5000);    // wait for spin
}
void grabChest() {

    setTargets(0, 0, 0, 0);

    digitalWrite(DIR6, HIGH);  // direction command
    analogWrite(PWM6, 255);

    delay(1000);

    digitalWrite(DIR6, LOW);  // direction command
    analogWrite(PWM6, 255); // write full speed to pick up

    delay(1000);    // wait a second to capture

    analogWrite(PWM6, 0);

//    SPEED = 2.8;    // increase robot speed
}
