import numpy as np
from sensorBus import *
import time
import serial


delay = .001

gpio0_arr = [20, 26, 13, 6]
gpio1_arr = [12, 16, 19, 21]

addr_arr_bus0 = [0x20,0x21,0x22,0x23]
addr_arr_bus1 = [0x24,0x25,0x26,0x27]

tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)
tof_arr1 = initBus(1, gpio1_arr, addr_arr_bus1)


vertices_startingPoint = [40, 180, 160, 180, 160, 300, 40, 300]
vertices_water = [213, 0, 308, 0, 308, 480, 213, 480]
vertices_stageb_top = [510, 0, 570, 0, 570, 30, 510, 30]
vertices_stageb_bottom = [510, 450, 570, 450, 570, 480, 510, 480]
vertices_flagturner = [840, 180, 960, 180, 960, 300, 840, 300]
vertices_ramp = [213, 150, 333, 150, 333, 330, 213, 330]
vertices_pushButton1 = [90, 0, 110, 0, 110, 20, 90, 20]
vertices_pushButton2 = [90, 480, 110, 480, 110, 460, 90, 460]

SENSOR_MAP = {
  "left": (0, 1),
  "front": (2, 3),
  "right": (4, 5),
  "back": (6, 7)
}


port = '/dev/ttyACM0'
ard = serial.Serial(port,115200)

def sendCommand(command, speed=30):
  print(command)
  commandString = command.upper() + "@" + str(speed) + "\n"
  ard.write(commandString)
  time.sleep(.2)

def getSensorReadings(const):
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
  
  distanceArray = [b12, b02, b00, b10, b11, b01, b03, b13]
  for i in range(len(const)):
    distanceArray[i] = distanceArray[i] + const[i]
  #dumm = distanceArray[0]
  #distanceArray.remove(distanceArray[0])
  #distanceArray.append(dumm)
  #print distanceArray
  return distanceArray

distDict = {
  "front": ("forward", "backward"),
  "back": ("backward", "forward"),
  "left": ("left", "right"),
  "right": ("right", "left")
}

def setDistance(wall, distance):
  arr = getAvgSensors()
  tolerance = 15
  timestep = .3
  sensorNums = SENSOR_MAP[wall]
  directions = distDict[wall]

  currDist = (arr[sensorNums[0]] + arr[sensorNums[1]]) / 2
  while(1):
    print "Curr dist: ", currDist
    if (abs(currDist - distance) < tolerance):
      break
    else:
      if ((currDist - distance) < 0):
        sendCommand(directions[1])
        time.sleep(timestep)
        sendCommand("stop")
      if ((currDist - distance) > 0):
        sendCommand(directions[0])
        time.sleep(timestep)
        sendCommand("stop")

    arr = getAvgSensors()
    currDist = (arr[sensorNums[0]] + arr[sensorNums[1]]) / 2
    #print currDist

def center(side1, side2):
  side1S = SENSOR_MAP[side1]
  side2S = SENSOR_MAP[side2]
  arr = getAvgSensors([0, 40, 0, 0, 40, 0])
  tolerance = 10
  timestep = 0.1
  avgDist = (arr[side1S[0]] + arr[side1S[1]] +arr[side2S[0]] + arr[side2S[1]] + 80) / 4
  setDistance(side1, avgDist)
  straight("front")
  #setDistance(side2, avgDist)
  while(1):
    time.sleep(.1)
    arr = getAvgSensors([0, 40, 0, 0, 40, 0])
#    straight(side1)
#    straight(side2)
    straight("front")
    side1Dist = (arr[side1S[0]] + 40 + arr[side1S[1]]) / 2
    side2Dist = (arr[side2S[0]] + arr[side2S[1]] + 40) / 2
    diff = side1Dist- side2Dist
    print("Side 1: ", side1Dist)
    print("Side 2: ", side2Dist)
    print "diff = ", diff
    if (abs(diff) < tolerance):
      break
    else:
      if diff < 0:
        sendCommand(side2)
        time.sleep(timestep)
      else:
        sendCommand(side1)
        time.sleep(timestep)
      sendCommand("stop")

def straight(side, const=[]):
  arr = getAvgSensors(const)
  tolerance = 10
  timestep = .1
  sensorNumbers = SENSOR_MAP[side]
  print(sensorNumbers)
  diff = arr[sensorNumbers[0]] - arr[sensorNumbers[1]]
  while(1):
    print diff
    if (abs(diff) < tolerance):
      break
    else:
      #delay = abs(timestep * (diff / tolerance))
      if (diff < 0):
  	sendCommand("ccw")
  	sendCommand("stop")
      else:
  	sendCommand("cw")
  	sendCommand("stop")
    arr = getAvgSensors()
    diff = arr[sensorNumbers[0]] - arr[sensorNumbers[1]]

  sendCommand("newHeading")

def getAvgSensors(const=[]):
  N = 5
  sum_arr = np.zeros(8)
  for i in range(0,N):
    arr = getSensorReadings(const)
    sum_arr = sum_arr + arr
  sum_arr = sum_arr / N
  print sum_arr
  return sum_arr

#COURSE_START
#TODO: rest of course
#while(1):
#  print(getAvgSensors([0, 0, 0, 0, 0, 0, 15]))

while(1):
  time.sleep(5)
  sendCommand("right", 60)
#time.sleep(1)
#sendCommand("stop")
