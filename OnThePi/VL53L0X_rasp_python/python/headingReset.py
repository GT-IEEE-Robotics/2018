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
  time.sleep(delay)

  zeroBus = readBus(tof_arr0)
  time.sleep(delay)

  distanceArray = oneBus + zeroBus
  dumm = distanceArray[3]
  del distanceArray[3]
  distanceArray.append(dumm)
  print distanceArray
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
  getHeadingBeach()

stopBus(tof_arr0, gpio0_arr)
stopBus(tof_arr1, gpio1_arr)

