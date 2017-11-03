import serial
import sys
import time

ser = serial.Serial("/dev/ttyACM0", 9600)

ser.write("1 100 1000")

while (True):
#print(sys.argv[0], sys.argv[1], sys.argv[2], sys.argv[3])
    print(sys.argv[1] + " " + sys.argv[2] + " " + sys.argv[3])
    ser.write(sys.argv[1] + " " + sys.argv[2] + " " + sys.argv[3] + " ")
    time.sleep(1)
    print("wtf")
