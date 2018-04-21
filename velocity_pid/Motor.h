#pragma once
#include "PID.h"

const int8_t encoder_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

class Motor {
    protected:
        int pwm_pin, dir_pin, enca_pin, encb_pin;
        int direction_coef = 1, velocity_control = 0;

        uint32_t last_micros = 0;
        int32_t last_encoder = 0;

        PID * pid;
        float target = 0.0;

        volatile int32_t encoder_count;
        uint8_t enc_val = 0;

    public:
        // constructor
        Motor(int pwm, int dir,
              int enc_a, int enc_b,
              float p, float i, float d);            // pins
        
        // motor speed commands
        void setSpeed(int new_speed);           // 0-255
        void stop(void);
        virtual int update(void) = 0;

        // motor direction commands
        void reverseMotor(void);   // 1 for forward is CCW (default), 0 for forward is CW
        void setDirection(int new_direction);
        // void changeDirection(void);
        
        // command the PID
        void setTarget(float new_target);
        void updateTarget(float new_target);

        // encoder isr
        void setInterruptHandler(void (*encoder_isr)(void));
        void encoder_isr(void);

};

Motor::Motor(int pwm, int dir,
             int enc_a, int enc_b,
             float p, float i, float d) {
    pwm_pin = pwm; dir_pin = dir;
    enca_pin = enc_a; encb_pin = enc_b;

    pinMode(dir_pin, OUTPUT);

    pid = new PID(p, i, d, 255);
    pid->reset();

}
void Motor::setSpeed(int new_speed) {
    analogWrite(pwm_pin, new_speed);
}
void Motor::stop() {
    analogWrite(pwm_pin, 0);
}
void Motor::reverseMotor() {
    direction_coef = 0;
}
void Motor::setDirection(int new_direction) {
    digitalWrite(dir_pin, new_direction);
}
void Motor::setTarget(float new_target) {
    target = (direction_coef) ? new_target : -new_target;
    pid->reset();
}
void Motor::updateTarget(float new_target) {
    target = (direction_coef) ? new_target : -new_target;
}
void Motor::setInterruptHandler(void (*encoder_isr)(void)) {
    attachInterrupt(digitalPinToInterrupt(enca_pin), encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encb_pin), encoder_isr, CHANGE);
}
void Motor::encoder_isr() {
    enc_val = (enc_val << 2) | (digitalRead(enca_pin) << 1) | digitalRead(encb_pin);

    encoder_count += encoder_table[enc_val & 0b1111];
//    Serial.println(encoder_count);
}




// #include "PID.h"

// const int8_t encoder_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

// class Motor {
//     private:
//         int pwm_pin, dir_pin, enca_pin, encb_pin;
//         int direction_coef = 1;

//         PID * pid;
//         float target = 0.0;

//         volatile int32_t encoder_count;
//         uint8_t enc_val = 0;

//     public:
//         // constructor
//         Motor(int pwm, int dir,
//               int enc_a, int enc_b,
//               float p, float i, float d);            // pins
        
//         // motor speed commands
//         void setSpeed(int new_speed);           // 0-255
//         void stop(void);
//         void update(void);

//         // motor direction commands
//         void reverseMotor(void);   // 1 for forward is CCW (default), 0 for forward is CW
//         void setDirection(int new_direction);
//         // void changeDirection(void);
        
//         // command the PID
//         void setTarget(float new_target);

//         // encoder isr
//         void setInterruptHandler(void (*encoder_isr)(void));
//         void encoder_isr(void);
// };

// Motor::Motor(int pwm, int dir,
//              int enc_a, int enc_b,
//              float p, float i, float d) {
//     pwm_pin = pwm; dir_pin = dir;
//     enca_pin = enc_a; encb_pin = enc_b;

//     pinMode(dir_pin, OUTPUT);
    
//     pid = new PID(p, i, d, 255);
//     pid->reset();

// }
// void Motor::setSpeed(int new_speed) {
//     analogWrite(pwm_pin, new_speed);
// }
// void Motor::stop() {
//     analogWrite(pwm_pin, 0);
// }
// void Motor::reverseMotor() {
//     direction_coef = 0;
// }
// void Motor::setDirection(int new_direction) {
//     digitalWrite(dir_pin, new_direction);
// }
// // void Motor::changeDirection() {
// //     digitalWrite(dir_pin, !digitalRead(dir_pin));
// // }
// void Motor::setTarget(float new_target) {
//     target = (direction_coef) ? new_target : -new_target;
//     pid->reset();
// }
// void Motor::update() {

//     noInterrupts();
//     float error = target - encoder_count;
//     interrupts();

//     Serial.println("target");
//     Serial.println(target);
//     Serial.println(encoder_count);
//     Serial.println(error);

//     float output = pid->update(error);

//     if (output > 0) {
//         setDirection(1);
//         // Serial.println("direction 0");
//     } else {
//         setDirection(0);
//         // Serial.println("direction 1");
//     }

//     Serial.println(output);

//     // constrain output to 0-255
//     output = constrain(abs(output), 0, 255);

//     // Serial.println(output);

//     setSpeed(output);

//     // Serial.println(encoder_count);
//     // Serial.println(error);

// }
// void Motor::setInterruptHandler(void (*encoder_isr)(void)) {
//     attachInterrupt(digitalPinToInterrupt(enca_pin), encoder_isr, CHANGE);
//     attachInterrupt(digitalPinToInterrupt(encb_pin), encoder_isr, CHANGE);
// }
// void Motor::encoder_isr() {
//     enc_val = (enc_val << 2) | (digitalRead(enca_pin) << 1) | digitalRead(encb_pin);

//     encoder_count += encoder_table[enc_val & 0b1111];
// }
