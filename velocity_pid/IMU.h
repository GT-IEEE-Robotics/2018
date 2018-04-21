// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>


// uncomment if you want to print internal imu gyro calculations in the print function
//#define PRINT_CALCULATED

class imuGyro {
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
    PID * pid;
    float kp, ki, kd;
    float previous_z = 0.0, target = 0.0;

  public:

    imuGyro(float p, float i, float d) {
        kp = p; ki = i; kd = d;
        pid = new PID(p, i, d, 100.0);
    }

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
      if (!imu.begin()) {
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
    void setTarget(float new_target) {
        target = new_target;
        pid->reset();
    }
    float update() {
        float error = target - getZ();

        float output = pid->update(error);

        return constrain(output, -100.0, 100.0);
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