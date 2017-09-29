// Beginning of code ///////////////////////////////////////////////////////////////////
#include "mbed.h"
Serial pc(SERIAL_TX, SERIAL_RX); // set-up serial to pc
I2C i2c(I2C_SDA, I2C_SCL); // Set up I2C on the STM32 NUCLEO-401RE
#define addr (0x52) // I2C address of VL6180X shifted by 1 bit
                    //(0x29 << 1) so the R/W command can be added
///////////////////////////////////////////////////////////////////
// Split 16-bit register address into two bytes and write
// the address + data via I2C ///////////////////////////////////////////////////////////////////
void WriteByte(wchar_t reg,char data) {
    char data_write[3];
    data_write[0] = (reg >> 8) & 0xFF; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    data_write[2] = data & 0xFF;
    i2c.write(addr, data_write, 3);
}
///////////////////////////////////////////////////////////////////
// Split 16-bit register address into two bytes and write
// required register address to VL6180X and read the data back ///////////////////////////////////////////////////////////////////
char ReadByte(wchar_t reg) {
    char data_write[2]; char data_read[1];
    data_write[0] = (reg >> 8) & 0xFF; // MSB of register address
    data_write[1] = reg & 0xFF; // LSB of register address
    i2c.write(addr, data_write, 2);
    i2c.read(addr, data_read, 1);
    return data_read[0];
}
///////////////////////////////////////////////////////////////////
// load settings
///////////////////////////////////////////////////////////////////
int VL6180X_Init() {
    char reset;
    reset = ReadByte(0x016);
    if (reset==1){ // check to see has it be Initialised already
            /////////////////////////////////////////////////////////////////// // Added latest settings here - see Section 8
            ///////////////////////////////////////////////////////////////////
            WriteByte(0x016, 0x00); //change fresh out of set status to 0
    }
    return 0;
}
///////////////////////////////////////////////////////////////////
 // Start a range measurement in single shot mode ///////////////////////////////////////////////////////////////////
int VL6180X_Start_Range() {
    WriteByte(0x018,0x01);
    return 0;
}
///////////////////////////////////////////////////////////////////
// poll for new sample ready ready ///////////////////////////////////////////////////////////////////
int VL6180X_Poll_Range() {
    char status;
    char range_status;
    // check the status
    status = ReadByte(0x04f);
    range_status = status & 0x07;
    // wait for new measurement ready status
    while (range_status != 0x04) {
        status = ReadByte(0x04f);
        range_status = status & 0x07;
        wait_ms(1); // (can be removed)
    }
    return 0;
}
///////////////////////////////////////////////////////////////////
// Read range result (mm) ///////////////////////////////////////////////////////////////////
int VL6180X_Read_Range() {
    int range; range=ReadByte(0x062); return range;
}
///////////////////////////////////////////////////////////////////
// clear interrupts ///////////////////////////////////////////////////////////////////
int VL6180X_Clear_Interrupts() {
    WriteByte(0x015,0x07);
    return 0;
}
///////////////////////////////////////////////////////////////////
// Main Program loop ///////////////////////////////////////////////////////////////////
int main() {
    int range;
    // load settings onto VL6180X
    VL6180X_Init();
    while (1) {
        // start single range measurement
        VL6180X_Start_Range();
    }
    // poll the VL6180X till new sample ready
    VL6180X_Poll_Range();
    // read range result
    range = VL6180X_Read_Range();
    // clear the interrupt on VL6180X
    VL6180X_Clear_Interrupts();
    // send range to pc by serial
    pc.printf("%d\r\n", range);
    wait(0.1);
}
