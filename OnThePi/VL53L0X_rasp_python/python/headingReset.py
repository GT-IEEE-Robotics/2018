from sensorBus import *
import time
import numpy as np
import math

delay = .1

gpio0_arr = [26, 13, 20, 6]
gpio1_arr = [21, 16, 19, 12]

addr_arr_bus0 = [0x20,0x21,0x22,0x23]
addr_arr_bus1 = [0x24,0x25,0x26,0x27]

tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)
tof_arr1 = initBus(1, gpio1_arr, addr_arr_bus1)

def getSensorReadings():
  oneBus = readBus(tof_arr1)
  #time.sleep(delay)
  b10 = oneBus[0]
  b11 = oneBus[1]
  b12 = oneBus[2]
  b13 = oneBus[3]

  zeroBus = readBus(tof_arr0)
  #time.sleep(delay)
  b00 = zeroBus[0]
  b01 = zeroBus[1]
  b02 = zeroBus[2]
  b03 = zeroBus[3]
  distanceArray = [b12, b01, b02, b13, b11, b00, b03, b10]

  #dumm = distanceArray[0]
  #distanceArray.remove(distanceArray[0])
  #distanceArray.append(dumm)
  #print distanceArray
  return distanceArray

def getHeadingBeach():
  arr = getSensorReadings()
  length = 11 #length of robot
  back = arr[0]
  front = arr[1]
  leftWallMeasure = math.atan2((back - front), length)
  leftWallMeasure = leftWallMeasure / math.pi * 180
#  print leftWallMeasure

while(1):
  print getSensorReadings()
stopBus(tof_arr0, gpio0_arr)
stopBus(tof_arr1, gpio1_arr)

