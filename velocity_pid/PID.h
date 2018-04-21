class PID {
    private:
        float kp, ki, kd,   // PID coefficients
              last_error, error_sum;    // state variables
            
        float threshold;    // saturation threshold for integral windup protection

        uint32_t last_micros;   // last time PID calculated an update

    public:
        // constructor
        PID(float p, float i, float d, float thres) : kp(p), ki(i), kd(d), threshold(thres) {};

        // commands
        float reset(void);       // automatically resets terms
        float update(float error);

};
float PID::reset() {
    error_sum = last_error = 0;
    last_micros = micros();
}
float PID::update(float error) {

    uint16_t now = micros();
    uint16_t dt = now - last_micros;

    float output = kp*error + ki*error_sum*dt + kd*((error - last_error)/dt);
    
    if (fabsf(output) <= threshold) {
        error_sum += error;
        output += ki*error*dt;
    }

    // keep track of last error
    last_error = error;
    last_micros = now;

    return output;
}