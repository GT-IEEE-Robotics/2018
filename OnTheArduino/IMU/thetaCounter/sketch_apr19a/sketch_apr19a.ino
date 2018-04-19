// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

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
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

class imuGyro {
  private:
    double sum_x = 0;
    double sum_y = 0;
    double sum_z = 0;
    double mill = 0;
    unsigned long prevTime = 0;
  public:
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
        sum_x = sum_x + (imu.calcGyro(imu.gx)) * (curTime - prevTime)/1000.0;
        sum_y = sum_y + (imu.calcGyro(imu.gy)) * (curTime - prevTime)/1000.0;
        sum_z = sum_z + (imu.calcGyro(imu.gz)) * (curTime - prevTime)/1000.0;
        prevTime = curTime;
      }
    }
    double getx() {
      return sum_x;
    }
    double gety() {
      return sum_y;
    }
    double getz() {
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
        Serial.print("sum_x = ");
        Serial.print(sum_x);
        Serial.print(" sum_y = ");
        Serial.print(sum_y);
        Serial.print(" sum_z = ");
        Serial.println(sum_z);
#endif
      }
    }
};


imuGyro gyro1;



void setup()
{

  Serial.begin(115200);
  //imu power gpio
  gyro1.init(30);

}
void loop() {
  // put your main code here, to run repeatedly:
  gyro1.addGyro();
  //gyro1.addx();
  //gyro1.addy();
  //gyro1.addz();
  gyro1.printGyro();
  //delay(.1);

}

