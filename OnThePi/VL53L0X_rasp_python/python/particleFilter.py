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

def sendCommand(command):
  print(command)
  if (command == "stop"):
    ard.write("STOP\n")
  if (command == "forward"):
    ard.write("FORWARD\n")
  if (command == "backward"):
    ard.write("BACKWARD\n")
  if (command == "right"):
    ard.write("RIGHT\n")
  if (command == "left"):
    ard.write("LEFT\n")
  if (command == "cw"):
    ard.write("CW\n")
  if (command == "ccw"):
    ard.write("CCW\n")
  if (command == "newHeading"):
    ard.write("NEWHEADING\n")
  #time.sleep(.1)
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

  distanceArray = oneBus + zeroBus
  dumm = distanceArray[0]
  distanceArray.remove(distanceArray[0])
  distanceArray.append(dumm)
  #print distanceArray
  return distanceArray

distDict = {
  "front": ("forward", "backward"),
  "back": ("backward", "forward"),
  "left": ("left", "right"),
  "right": ("right", "left")
}

def setDistance(wall, distance):
  arr = getHeading()
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

    arr = getHeading()
    currDist = (arr[sensorNums[0]] + arr[sensorNums[1]]) / 2
    print currDist

#deprecated
def setDistance2(wall, distance):
  arr = getHeading()
  tolerance = 15
  timestep = .1
  if (wall == "back"):
    currDist = (arr[6] + arr[7]) / 2
    while(1):
      if (abs(currDist - distance) < tolerance):
        break
      else:
        if ((currDist - distance) < 0):
          sendCommand("forward")
          time.sleep(timestep)
          sendCommand("stop")
        if ((currDist - distance) > 0):
          sendCommand("backward")
          time.sleep(timestep)
          sendCommand("stop")
      arr = getHeading()
      currDist = (arr[6] + arr[7]) / 2
      print currDist

  if (wall == "front"):
    currDist = (arr[2] + arr[3]) / 2
    while(1):
      if (abs(currDist - distance) < tolerance):
        break
      else:
        if ((currDist - distance) < 0):
          sendCommand("backward")
          time.sleep(timestep)
          sendCommand("stop")
        if ((currDist - distance) > 0):
          sendCommand("forward")
          time.sleep(timestep)
          sendCommand("stop")
      arr = getHeading()
      currDist = (arr[6] + arr[7]) / 2
      print currDist


def straight(side):
  arr = getHeading()
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
    arr = getHeading()
    diff = arr[sensorNumbers[0]] - arr[sensorNumbers[1]]
    print diff
  sendCommand("newHeading")

#deprecated
def straight2(side): #need to send side to allign with
  arr = getHeading()
  tolerance = 10
  timestep = .3
  if (side == "front"):
    diff = arr[2] - arr[3]
    while(1):
      if (abs(diff) < tolerance):
        break
      else:
        if (diff < 0):
          sendCommand("ccw")
          time.sleep(timestep)
          sendCommand("stop")
        else:
          sendCommand("cw")
          time.sleep(timestep)
          sendCommand("stop")
      arr = getHeading()
      diff = arr[2] - arr[3]
      print diff

  elif side == "back":
    diff = arr[6] - arr[7]
    print diff
    while(1):
      if (abs(diff) < tolerance):
        break
      else:
        if diff < 0:
          sendCommand("ccw")
          time.sleep(timestep)
          sendCommand("stop")
        else:
          sendCommand("cw")
          time.sleep(timestep)
          sendCommand("stop")
      arr = getHeading()
      diff = arr[6] - arr[7]
      print diff

def getHeading():
  N = 5
  sum_arr = np.zeros(8)
  for i in range(0,N):
    arr = getSensorReadings()
    sum_arr = sum_arr + arr
  sum_arr = sum_arr / N
#  print sum_arr
  return sum_arr

def getCoord(prevHeading,prevCoord):
  arr = getHeading()
  deltaHeading = arr - prevHeading
  dxfront = (deltaHeading[6] + deltaHeading[7]) / 2
  dxback = (deltaHeading[2] + deltaHeading[3]) / 2
  dyleft = (deltaHeading[0] + deltaHeading[1]) / 2
  dyright = (deltaHeading[5] + deltaHeading[4]) / 2
  print dxfront, dxback, dyleft, dyright
#  conf = 0
#  if prevCoord[2] <  45 and prevCoord[2] > -45:
#    conf = 0
#  elif prevCoord[2] < 135:
#    conf = 1
#  elif prevCoord[2] < 225:
#    conf = 2
#  else:
#    conf = 3

#  if conf == 0:
#    dy = np.sign(deltaHeading[0]) * (abs(deltaHeading[0] + deltaHeading[1])/4 + abs(deltaHeading[4] + deltaHeading[5])/4)
#    dx = np.sign(deltaHeading[6]) * (abs(deltaHeading[6] + deltaHeading[7])/4 + abs(deltaHeading[2] + deltaHeading[3])/4)

#  newCoord = [prevCoord[0] + dx, prevCoord[1] + dy, prevCoord[2] + theta]
#  print newCoord
#  return arr, newCoord

def create_gaussian_particles(x ,y, theta, N):
    particles = np.empty((N,3))
    particles[:,0] = x
    particles[:,1] = y
    particles[:,2] = theta
    return particles


def motionUpdate(particles, dx, dy, dtheta):
    """ move according to control input u (heading change, velocity)
    with noise Q (std heading change, std velocity)`"""
    for i in range(0,len(particles)):
        particles[i] = particles[i] + np.append(np.random.randn(2), (np.random.randn()*10))
    particles = particles + [dx, dy, dtheta]
    return particles



def measureUpdate(particles):
    #update = getHeadingData() x,y,theta
    err_particles = []
    mag_particles = []
    for particle in particles:
        err = particle - [x, y, theta/10]
        mag = err[0]**2 + err[1]**2 + err[2]**2
        err_particles.append(err)
        mag_particles.append(mag)
    mag_particles = mag_particles/np.sum(mag_particles)
    ideal_x = np.sum(particles[:,0] * mag_particles)
    ideal_y = np.sum(particles[:,1] * mag_particles)
    ideal_theta = np.sum(particles[:,2] * mag_particles)
    #print ideal_x, ideal_y, ideal_theta



x = 10
y = 24
theta = 0
N = 10

#sensors = getSensorReadings()
#cluster = create_gaussian_particles(x, y, theta, N)
#print cluster

dx = 1
dy = 1
dtheta = 40
#cluster = motionUpdate(cluster, dx, dy, dtheta)
#print cluster
#cluster = measureUpdate(cluster)
sensors = getHeading()
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
sensors = getHeading()
sensors = getSensorReadings()
print(getHeading())
    #getCoord(sensors,[0,0,0])
    #if (now > future):
      #sendCommand("stop")
      #break
    #now = time.time()
    #straight("front")
    #sendCommand("newHeading")

