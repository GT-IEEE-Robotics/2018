#include "MotorVelocity.h"
#include "MotorPosition.h"
// #include "IMU.h"

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
#define ENC2_A  (26)
#define ENC2_B  (24)
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
#define P6 (2.0f)
#define I6 (0.00001f)
#define D6 (0.0f)

/* control flow */
#define PID_PERIOD  (10000)    // rate at which PID updates in microseconds

uint32_t last_run = 0,      // last PID run in miliseconds
         curr_run = 0;

MotorVelocity left_front(PWM1, DIR1, ENC1_A, ENC1_B, P1, I1, D1);
MotorVelocity right_front(PWM2, DIR2, ENC2_A, ENC2_B, P2, I2, D2);
MotorVelocity left_rear(PWM3, DIR3, ENC3_A, ENC3_B, P3, I3, D3);
MotorVelocity right_rear(PWM4, DIR4, ENC4_A, ENC4_B, P4, I4, D4);

MotorPosition flag(PWM5, DIR5, ENC5_A, ENC5_B, P5, P5, P5);
// MotorPosition treasure(PWM6, DIR6, ENC6_A, ENC6_B, P6, P6, P6);

// Define global IMU Gyro Sensor
//imuGyro gyro(0, 0, 0);

void left_front_encoder_isr(void) { left_front.encoder_isr(); }
void right_front_encoder_isr(void) { right_front.encoder_isr(); }
void left_rear_encoder_isr(void) { left_rear.encoder_isr(); }
void right_rear_encoder_isr(void) { right_rear.encoder_isr(); }

void setup() {

    Serial.begin(115200);

    // gyro.init(30);

    // set directions
    left_rear.reverseMotor();
    left_front.reverseMotor();
    right_rear.reverseMotor();
    // right_front.reverseMotor();

    // set targets
    left_front.setTarget(5);
    right_front.setTarget(5);
    left_rear.setTarget(5);
    right_rear.setTarget(5);
    // gyro.setTarget(0);
    
    left_front.setInterruptHandler(left_front_encoder_isr);
    right_front.setInterruptHandler(right_front_encoder_isr);
    left_rear.setInterruptHandler(left_rear_encoder_isr);
    right_rear.setInterruptHandler(right_rear_encoder_isr);
}

void loop() {
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

        Serial.print("left: "); Serial.println(left_command);
        Serial.print("left rear command: "); Serial.println(left_rear_command);

        left_front.setSpeed(left_front_command);
        right_front.setSpeed(right_front_command);
        left_rear.setSpeed(left_rear_command);
        right_rear.setSpeed(right_rear_command);
        last_run = micros();
    }
}