from time import sleep
import Adafruit_BBIO.GPIO as GPIO
from Adafruit_I2C import Adafruit_I2C

class Dist:
    SENS_ADDR  = 0x029
    JUST_RESET = 0x016
    START_READ = 0x018
    RANGE_RDY  = 0x04f
    RANGE_VAL  = 0x062
    i2c = 0x29

    def __init__(self, on_mode=True, sensor_num=1):
	#sensor_pins = ["P9_12", "P9_15", "P9_23", "P9_25", "P9_27"]
        #for pin in sensor_pins:
        #    GPIO.setup(pin, GPIO.OUT)
        #    GPIO.output(pin, GPIO.LOW)
        #if on_mode is True: 
        #    GPIO.output(sensor_pins[sensor_num], GPIO.HIGH)
	pin = "GPIO_48"
	GPIO.setup(pin,GPIO.OUT)
	GPIO.output(pin, GPIO.HIGH)

	self.i2c = Adafruit_I2C(self.SENS_ADDR,1,True)
        reset = self.readByte(self.JUST_RESET)
	print reset
	sleep(2)
       # if reset is 1: # check to see has it be Initialised already
        self.__set_default_settings()
        self.writeByte(self.JUST_RESET, 0x00); # change fresh out of set status to 0
        self.writeByte(0x015, 0x07) # clear interrupt

    def __del__(self):
        GPIO.cleanup()

    def get_range(self):
        retVal = -1
        self.writeByte(self.START_READ, 0x01) # start reading range
        self.__poll_range() # poll range
        retVal = self.readByte(self.RANGE_VAL) # readRangeValue()
        self.writeByte(0x015, 0x07) # clear interrupt
        return retVal

    def __set_default_settings(self):
    # private method
    # Mandatory : private registers
        self.writeByte(0x0207, 0x01);
        self.writeByte(0x0208, 0x01);
        self.writeByte(0x0096, 0x00);
        self.writeByte(0x0097, 0xfd);
        self.writeByte(0x00e3, 0x00);
        self.writeByte(0x00e4, 0x04);
        self.writeByte(0x00e5, 0x02);
	self.writeByte(0x00e6, 0x01);
	self.writeByte(0x00e7, 0x03);
	self.writeByte(0x00f5, 0x02);
        self.writeByte(0x00d9, 0x05);
        self.writeByte(0x00db, 0xce);
        self.writeByte(0x00dc, 0x03);
        self.writeByte(0x00dd, 0xf8);
        self.writeByte(0x009f, 0x00);
        self.writeByte(0x00a3, 0x3c);
        self.writeByte(0x00b7, 0x00);
        self.writeByte(0x00bb, 0x3c);
        self.writeByte(0x00b2, 0x09);
        self.writeByte(0x00ca, 0x09);
        self.writeByte(0x0198, 0x01);
        self.writeByte(0x01b0, 0x17);
        self.writeByte(0x01ad, 0x00);
        self.writeByte(0x00ff, 0x05);
        self.writeByte(0x0100, 0x05);
        self.writeByte(0x0199, 0x05);
        self.writeByte(0x01a6, 0x1b);
        self.writeByte(0x01ac, 0x3e);
        self.writeByte(0x01a7, 0x1f);
        self.writeByte(0x0030, 0x00);

    # Recommended : Public registers - See data sheet for more detail
        self.writeByte(0x0011, 0x10);# Enables polling for New Sample ready when measurement completes
        self.writeByte(0x010a, 0x30);# Set the averaging sample period (compromise between lower noise and increased execution time)
        self.writeByte(0x003f, 0x46);# Sets the light and dark gain (upper nibble). Dark gain should not be changed.
        self.writeByte(0x0031, 0xFF);# sets the # of range measurements after which auto calibration of system is performed
        self.writeByte(0x0040, 0x63);# Set ALS integration time to 100ms
        self.writeByte(0x002e, 0x01);# perform a single temperature calibration of the ranging sensor
        self.writeByte(0x001b, 0x09);# Set default ranging inter-measurement period to 100ms
        self.writeByte(0x003e, 0x31);# Set default ALS inter-measurement period to 500ms
        self.writeByte(0x0014, 0x24);# Configures interrupt on New Sample Ready threshold event 
    
    def __poll_range(self): 
    # private method
	count = 0
        while True:
            status = self.readByte(self.RANGE_RDY)
            sleep(0.001) # sleep 1 ms
	    count += 1
	    if (count > 100):
           # if (status & 0x07) == 0x04:
                break;

    def readByte(self, reg):
       return self.i2c.readU8( reg )

    def writeByte(self, reg, data):
        self.i2c.write8( reg, data )

