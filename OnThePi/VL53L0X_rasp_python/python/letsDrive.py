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
  commandString = command.upper() + "@" + speed + "\n"
  ard.write(commandString)
  time.sleep(delay)

def getSensorReadings():
  oneBus = readBus(tof_arr1)
  #time.sleep(delay)
  dumm = oneBus[0]
  dumm1 = oneBus[1]
  dumm2 = oneBus[2]
  dumm3 = oneBus[3]
  oneBus = [dumm, dumm3, dumm1, dumm2]

  zeroBus = readBus(tof_arr0)
  #time.sleep(delay)
  dumm = zeroBus[0]
  dumm1 = zeroBus[1]
  dumm2 = zeroBus[2]
  dumm3 = zeroBus[3]
  zeroBus = [dumm1, dumm2, dumm, dumm3]

  distanceArray = oneBus[1:] + zeroBus + oneBus[0]
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
  timestep = .1
  sensorNums = SENSOR_MAP[wall]
  directions = distDict[wall]

  currDist = (arr[sensorNums[0]] + arr[sensorNums[1]]) / 2
  while(1):
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
    print currDist

def straight(side):
  arr = getAvgSensors()
  tolerance = 5
  timestep = .1
  sensorNumbers = SENSOR_MAP[side]
  print sensorNumbers
  diff = arr[sensorNumbers[0]] - arr[sensorNumbers[1]]
  while(1):
    print diff
    if (abs(diff) < tolerance):
      break
    else:
      #delay = abs(timestep * (diff / tolerance))
      if (diff < 0):
  	sendCommand("ccw")
  	time.sleep(timestep)
  	sendCommand("stop")
      else:
  	sendCommand("cw")
  	time.sleep(timestep)
  	sendCommand("stop")
    arr = getAvgSensors()
    diff = arr[sensorNumbers[0]] - arr[sensorNumbers[1]]
    print diff
  sendCommand("newHeading")

def getAvgSensors():
  N = 5
  sum_arr = np.zeros(8)
  for i in range(0,N):
    arr = getSensorReadings()
    sum_arr = sum_arr + arr
  sum_arr = sum_arr / N
#  print sum_arr
  return sum_arr

sensors = getAvgSensors()
getCoord(sensors, [0,0,0])
now = time.time()
future = now + 5
#COURSE_START
#sendCommand("left")
#TODO: rest of course, variable turn speed
time.sleep(.1)
straight("back")
time.sleep(.1)
sendCommand("right")
time.sleep(5.5)
sendCommand("stop")
time.sleep(.1)
sendCommand("newHeading")
time.sleep(.1)

sendCommand("left")
time.sleep(5)
sendCommand("stop")
time.sleep(.1)
straight("back")

time.sleep(.1)
sendCommand("forward")
time.sleep(6.5)
sendCommand("stop")
time.sleep(.1)
sendCommand("newHeading")
time.sleep(.1)

sendCommand("cw")
time.sleep(2.75)
sendCommand("stop")
time.sleep(.1)
sendCommand("newHeading")
time.sleep(.1)

sendCommand("forward")
time.sleep(4.5)
sendCommand("stop")
time.sleep(.1)

sendCommand("backward")
time.sleep(1)
sendCommand("ccw")
time.sleep(2.75)
sendCommand("forward")
time.sleep(1)
straight("right")
setDistance("right", 500)


sendCommand("stop")
sensors = getAvgSensors()
sensors = getSensorReadings()
print(getAvgSensors())

