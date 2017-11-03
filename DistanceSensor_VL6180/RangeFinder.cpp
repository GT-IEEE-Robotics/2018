#include "stdio.h"
#include "RangeFinder.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h> // for O_RDWR
#include <fcntl.h>  // for open()

int RangeFinder::file = 0;

RangeFinder::RangeFinder() {
    RangeFinder( 1 ); // default i2cBus = 1
}

RangeFinder::RangeFinder( int bus ) {
    i2cBus = bus;
    init();
}

int RangeFinder::init(){
    char namebuf[MAX_BUS]; //name of i2c bus to be used
    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", i2cBus);
    if ((file = open(namebuf, O_RDWR)) < 0){
            printf("Failed to open sensor on %s I2C Bus\n", namebuf);
            return 1;
    }
    if (ioctl(file, I2C_SLAVE, 0x29) < 0){
            printf("I2C_SLAVE address %s failed...\n", SENS_ADDR);
            return 2;
    }

    char reset;
    reset = readByte(JUST_RESET);
    if (reset==1){ // check to see has it be Initialised already
        setDefaultSettings();
        writeByte(JUST_RESET, 0x00); //change fresh out of set status to 0
    }
    clearInterrupt();
    return 0;
}

void RangeFinder::setDefaultSettings() {
// Mandatory : private registers
    writeByte(0x0207, 0x01);
    writeByte(0x0208, 0x01);
    writeByte(0x0096, 0x00);
    writeByte(0x0097, 0xfd);
    writeByte(0x00e3, 0x00);
    writeByte(0x00e4, 0x04);
    writeByte(0x00e5, 0x02);
    writeByte(0x00e6, 0x01);
    writeByte(0x00e7, 0x03);
    writeByte(0x00f5, 0x02);
    writeByte(0x00d9, 0x05);
    writeByte(0x00db, 0xce);
    writeByte(0x00dc, 0x03);
    writeByte(0x00dd, 0xf8);
    writeByte(0x009f, 0x00);
    writeByte(0x00a3, 0x3c);
    writeByte(0x00b7, 0x00);
    writeByte(0x00bb, 0x3c);
    writeByte(0x00b2, 0x09);
    writeByte(0x00ca, 0x09);
    writeByte(0x0198, 0x01);
    writeByte(0x01b0, 0x17);
    writeByte(0x01ad, 0x00);
    writeByte(0x00ff, 0x05);
    writeByte(0x0100, 0x05);
    writeByte(0x0199, 0x05);
    writeByte(0x01a6, 0x1b);
    writeByte(0x01ac, 0x3e);
    writeByte(0x01a7, 0x1f);
    writeByte(0x0030, 0x00);

// Recommended : Public registers - See data sheet for more detail
    writeByte(0x0011, 0x10);// Enables polling for ‘New Sample ready’
                            // when measurement completes
    writeByte(0x010a, 0x30);// Set the averaging sample period
                            // (compromise between lower noise and
                            // increased execution time)
    writeByte(0x003f, 0x46);// Sets the light and dark gain (upper
                            // nibble). Dark gain should not be
                            // changed.
    writeByte(0x0031, 0xFF);// sets the # of range measurements after
                            // which auto calibration of system is
                            // performed
    writeByte(0x0040, 0x63);// Set ALS integration time to 100ms
    writeByte(0x002e, 0x01);// perform a single temperature calibration
                            // of the ranging sensor
    writeByte(0x001b, 0x09);// Set default ranging inter-measurement
                            // period to 100ms
    writeByte(0x003e, 0x31);// Set default ALS inter-measurement period
                            // to 500ms
    writeByte(0x0014, 0x24);// Configures interrupt on New Sample
                            // Ready threshold event 
}

void RangeFinder::writeByte(wchar_t reg, char data) {
    char data_write[3];
    data_write[0] = (reg >> 8) & 0xFF;; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    data_write[2] = data & 0xFF;
    write(file, data_write, 3);
}

char RangeFinder::readByte(wchar_t reg) {
    char data_write[2];
    char data_read[1];
    data_write[0] = (reg >> 8) & 0xFF; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    write(file, data_write, 2);
    read(file, data_read, 1);
    return data_read[0];
}

int RangeFinder::startReadingRange() {
    writeByte(START_READ,0x01);
    return 0;
}
int RangeFinder::pollRange() {
    // printf("poll RANGE_RDY\n");
    char status;
    char range_status;
    do {
        status = readByte(RANGE_RDY);
        sleep(0.001); // sleep 1 ms
    } while( (status&0x07) != 0x04 ) ;
    return 0;
}
int RangeFinder::readRangeValue(){
    return readByte(RANGE_VAL);
}

void RangeFinder::clearInterrupt(){
    writeByte(0x015,0x07);
}

// grabs it all
int RangeFinder::getRange() {
    int retVal = -1;
    startReadingRange();
    pollRange();
    retVal = readRangeValue();
    clearInterrupt();
    return retVal;
}

void RangeFinder::closeFile() {
    close(file);
}

