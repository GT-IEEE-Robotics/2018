from sensorBus import *
import time
import numpy as np
import math

import signal
import sys

def singal_handler(signal, frame):
  file.close()
  print("Exiting, writing to ", fileName)
  stopBus(tof_arr0, gpio0_arr)
  stopBus(tof_arr1, gpio1_arr)
  sys.exit(0)


gpio0_arr = [20, 26, 13, 6]
gpio1_arr = [12, 16, 19, 21]

addr_arr_bus0 = [0x20,0x21,0x22,0x23]
addr_arr_bus1 = [0x24,0x25,0x26,0x27]

tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)
tof_arr1 = initBus(1, gpio1_arr, addr_arr_bus1)

def getSensorReadings():
  oneBus = readBus(tof_arr1)
  b10 = oneBus[0]
  b11 = oneBus[1]
  b12 = oneBus[2]
  b13 = oneBus[3]

  zeroBus = readBus(tof_arr0)
  b00 = zeroBus[0]
  b01 = zeroBus[1]
  b02 = zeroBus[2]
  b03 = zeroBus[3]
  distanceArray = [b12, b02, b00, b10, b11, b01, b03, b13]

  return distanceArray

fileName = "sensorReadingsForwardBackward.txt"
file = open(fileName, 'w')
file.truncate()

while(1):
  outStr = str(getSensorReadings())[1:-1] + "\n"
  time.sleep(.01)
  file.write(outStr)



