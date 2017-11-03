//FIle: RangeFinder.h

// sensor register address constants
#define SENS_ADDR 0x29
#define JUST_RESET 0x016
#define START_READ 0x018
#define RANGE_RDY 0x04f
#define RANGE_VAL 0x062

//i2c bus constant
#define MAX_BUS 64

class RangeFinder {

  public:
    RangeFinder();
    RangeFinder(int bus);
    ~RangeFinder() {};
    int getRange();
    void closeFile();
    static int file;

  private:
    void writeByte( wchar_t reg, char data);
    char readByte( wchar_t reg );
    int init();
    void setDefaultSettings();
    int startReadingRange();
    int pollRange();
    int readRangeValue();
    void clearInterrupt();

    int i2cBus;
};
