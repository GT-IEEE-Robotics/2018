import serial
import sys

ser = serial.Serial("/dev/ttyACM0", 9600)

file = open("demo.txt", "r")

for line in file:
    list = line.split(" ")
    ser.write(list[0] + " " + list[1] + " " + list[2])

