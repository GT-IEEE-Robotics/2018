#include "MotorVelocity.h"
#include "MotorPosition.h"
#include "IMU.h"

#define REV     (4741.44)  // revolution is 1920 counts

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

/* PIDs */
// left front
#define P (6.0f)
#define I (0.00001f)
#define D (0.0f)

// right front

// left rear

// right rear

uint32_t last_run = 0,      // last PID run in miliseconds
         curr_run = 0;

/* control flow */
#define PID_PERIOD  (10000)    // rate at which PID updates in microseconds

MotorVelocity left_front(PWM1, DIR1, ENC1_A, ENC1_B, P, I, D);
MotorVelocity right_front(PWM2, DIR2, ENC2_A, ENC2_B, P*1.8, I, D);
MotorVelocity left_rear(PWM3, DIR3, ENC3_A, ENC3_B, P, I, D);
MotorVelocity right_rear(PWM4, DIR4, ENC4_A, ENC4_B, P, I, D);

//MotorPosition 

// MotorPosition left(PWM1, DIR1, ENC1_A, ENC1_B, 3.0f, 0.0000001f, 0.0f);
// MotorPosition right(PWM2, DIR2, ENC2_A, ENC2_B, 3.0f, 0.0000001f, 0.0f);

// Define global IMU Gyro Sensor
//imuGyro gyro(0, 0, 0);

void left_front_encoder_isr(void) { left_front.encoder_isr(); }
void right_front_encoder_isr(void) { right_front.encoder_isr(); }
void left_rear_encoder_isr(void) { left_rear.encoder_isr(); }
void right_rear_encoder_isr(void) { right_rear.encoder_isr(); }

void setup() {

    Serial.begin(115200);

//    gyro.init(30);

    // set directions
    //right_front.reverseMotor();
    //right_rear.reverseMotor();
    left_rear.reverseMotor();
    left_front.reverseMotor();
    right_rear.reverseMotor();
//    right_front.reverseMotor();

    // set targets
    left_front.setTarget(5);
    right_front.setTarget(5*.125);
    left_rear.setTarget(5);
    right_rear.setTarget(5);

//    gyro.setTarget(0);
    // left.setTarget(2*REV);
    // right.setTarget(2*REV);
    
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

//         left_front.updateTarget(5 + gyro_command);
//         right_front.updateTarget(5 + gyro_command);
//         left_rear.updateTarget(5 + gyro_command);
//         right_rear.updateTarget(5 + gyro_command);

        //int left_front_command = left_front.update();
        int right_front_command = right_front.update();
        //int left_rear_command = left_rear.update();
        //int right_rear_command = right_rear.update();

        // Serial.print("left: "); Serial.println(left_command);
//         Serial.print("left rear command: "); Serial.println(left_rear_command);

//        left_front.setSpeed(left_front_command);
//        right_front.setSpeed(right_front_command);
//        left_rear.setSpeed(left_rear_command);
//        right_rear.setSpeed(right_rear_command);
//         Serial.println("Update!");
        last_run = micros();
    }
    // Serial.println(gyro1.getZ());
}
