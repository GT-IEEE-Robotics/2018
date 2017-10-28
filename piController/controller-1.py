import serial

ser = serial.Serial("/dev/ttyACM0", 9600)

while (True):
    inputData = raw_input("dir speed interval\n")
    #print(type(inputData))
    ser.write(inputData)
