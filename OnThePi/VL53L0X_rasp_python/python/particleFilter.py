import numpy as np
#from sensorBus import *
#import time

#delay = .5

#gpio0_arr = [20, 26, 13, 6]
#gpio1_arr = [12, 16, 19, 21]

#addr_arr_bus0 = [0x20,0x21,0x22,0x23]
#addr_arr_bus1 = [0x24,0x25,0x26,0x27]

#tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)
#tof_arr1 = initBus(1, gpio1_arr, addr_arr_bus1)


vertices_startingPoint = [40, 180, 160, 180, 160, 300, 40, 300]
vertices_water = [213, 0, 308, 0, 308, 480, 213, 480]
vertices_stageb_top = [510, 0, 570, 0, 570, 30, 510, 30]
vertices_stageb_bottom = [510, 450, 570, 450, 570, 480, 510, 480]
vertices_flagturner = [840, 180, 960, 180, 960, 300, 840, 300]
vertices_ramp = [213, 150, 333, 150, 333, 330, 213, 330]
vertices_pushButton1 = [90, 0, 110, 0, 110, 20, 90, 20]
vertices_pushButton2 = [90, 480, 110, 480, 110, 460, 90, 460]

def getSensorReadings():
  oneBus = readBus(tof_arr1)
  time.sleep(delay)

  zeroBus = readBus(tof_arr0)
  time.sleep(delay)

  distanceArray = oneBus + zeroBus
  dumm = distanceArray[3]
  del distanceArray[3]
  distanceArray.append(dumm)
#  print distanceArray
  return distanceArray


def create_gaussian_particles(x,y,theta,N):
    particles = np.empty((N,3))
    particles[:,0] = x
    particles[:,1] = y
    particles[:,2] = theta
    return particles


def motionUpdate(particles, direction, movement):
    """ move according to control input u (heading change, velocity)
    with noise Q (std heading change, std velocity)`"""

    N = len(particles)
    # update heading
    particles[:, 2] += u[0] + (randn(N) * std[0])
    particles[:, 2] %= 2 * np.pi

    # move in the (noisy) commanded direction
    dist = (u[1] * dt) + (randn(N) * std[1])
    particles[:, 0] += np.cos(particles[:, 2]) * dist
    particles[:, 1] += np.sin(particles[:, 2]) * dist
    return particles

#sensors = getSensorReadings()
cluster = create_gaussian_particles(10, 24, 0, 10)
print cluster

