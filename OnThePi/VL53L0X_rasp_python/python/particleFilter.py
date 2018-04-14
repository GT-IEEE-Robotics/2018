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


def create_gaussian_particles(mean, std, N):
    particles = np.empty((N, 3))
    particles[:, 0] = mean[0] + (randn(N) * std[0])
    particles[:, 1] = mean[1] + (randn(N) * std[1])
    particles[:, 2] = mean[2] + (randn(N) * std[2])
    particles[:, 2] %= 2 * np.pi
    return particles


def predict(particles, u, std, dt=1.):
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
u = [5,2]
std = [6,3]
cluster = create_gaussian_particles(10,2,10)
print cluster
cluster = predict(cluster,u,std,1)
print cluster

