#include <Python.h>
#include "stdio.h"
//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h> // for O_RDWR
#include <fcntl.h>  // for open()

// ******************* Sensor Functions ********************** //

// default 7bit sensor address is 0x29 
#define JUST_RESET 0x016
#define START_READ 0x018
#define RANGE_RDY 0x04f
#define RANGE_VAL 0x062
#define MAX_BUS 64 //i2c bus constant
#define I2CBUS 1

int SENS_ADDR = 0x29;
int file = 0;

int getRange(void);
void writeByte( wchar_t reg, char data);
char readByte( wchar_t reg );
int init(void);
void setDefaultSettings(void);
int pollRange(void);
void clearInterrupt(void);
void closeFile(void);
void setAddr(int);

int getRange(void){
    //printf("getting range\n");

    int retVal = -1;
    writeByte(START_READ,0x01); // start reading range

    if(!pollRange()){
        retVal = readByte(RANGE_VAL); // read range value
    } else {
	retVal = -1;
    }

    clearInterrupt();
    return retVal;
}

char readByte(wchar_t reg) {
    char data_write[2];
    char data_read[1];
    data_write[0] = (reg >> 8) & 0xFF; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    int temp = write(file, data_write, 2);
    temp = read(file, data_read, 1);
    return data_read[0];
}

void writeByte(wchar_t reg, char data) {
    char data_write[3];
    data_write[0] = (reg >> 8) & 0xFF;; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    data_write[2] = data & 0xFF;
    write(file, data_write, 3);
}

void clearInterrupt(void){
    writeByte(0x015,0x07); // clears interrupt
}

int pollRange(void) {
    //printf("polling range\n");
    char status;
    int ctr = 0; // watchdog counter
    do {
        status = readByte(RANGE_RDY);
        sleep(0.001); // sleep 1 ms

	ctr++;	
	if(ctr > 3000){
	    return -1;
	}

    } while( (status&0x07) != 0x04 ) ;
    return 0;
}

int init(void){
    //printf("initializing...\n");

    char namebuf[MAX_BUS];
    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBUS);
    if ((file = open(namebuf, O_RDWR)) < 0){
	printf("Failed to open sensor on %d I2C Bus\n", namebuf);
	exit(1);
    }
    if (ioctl(file, I2C_SLAVE, SENS_ADDR) < 0){
	printf("I2C_SLAVE address %s failed...\n", SENS_ADDR);
	exit(1);
    }

    char reset;
    reset = readByte(JUST_RESET);
    //printf("checking if initialized\n");
    if (reset == 1) { //checking if already initialized
	setDefaultSettings();
	writeByte(JUST_RESET, 0x00); // change fresh out of set status to 0
    }
    clearInterrupt();
    return 0;
}  

void setDefaultSettings(void) {
    //printf("now setting default settings\n");
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
    writeByte(0x0011, 0x10);// Enables polling for New Sample ready
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

void closeFile(void) {
//    printf("closing...\n");
    close(file);
}

void setAddr(int addr) { // calibrates i2c slave address after turnon
    writeByte(0x212, addr);
}

// ******************** Python Wrapper *********************** //

static PyObject*
say_hello(PyObject* self, PyObject* args)
{
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    printf("Hell %s!\n", name );
    Py_RETURN_NONE;
}

static PyObject*
setAddress(PyObject* self, PyObject* args)
{
    int addr = 0;
    if (!PyArg_ParseTuple(args, "i", &addr))
        return NULL;
    printf("setting addr: %d\n", addr);   
 
    SENS_ADDR = 0x29;
    init();
    setAddr(addr);
    closeFile();

 //   printf("success?\n");
    Py_RETURN_NONE;
}

static PyObject*
getDistance(PyObject* self, PyObject* args)
{
    if(!PyArg_ParseTuple(args, "i", &SENS_ADDR))
        return NULL;
//    printf("getting distance from %d\n", SENS_ADDR);

    int range = -1;
    init(); //opens file with SENS_ADDR
    range = getRange(); // gets range of currenlty open file
    closeFile(); // closes currently open file
//    printf("got range: %d\n", range);
    return Py_BuildValue("i", range);
}

static PyMethodDef HelloMethods[] = 
{
    {"say_hello", say_hello, METH_VARARGS, "Greet somebody."},
    {"setAddress", setAddress, METH_VARARGS, "sets 0x29 to addr."},
    {"getDistance", getDistance, METH_VARARGS, "get distance in mm"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initRangeFinder_C(void)
{
    (void) Py_InitModule("RangeFinder_C", HelloMethods);
}
