from sensorBus import *
import time

delay = 0.1

gpio0_arr = [20, 26, 13, 6]
gpio1_arr = [12, 16, 19, 21]

addr_arr = [0x20,0x21,0x22,0x23]

tof_arr0 = initBus(0, gpio0_arr, addr_arr)
tof_arr1 = initBus(1, gpio1_arr, addr_arr)

def prettyPrint(busnum, arr):
    print 'bus%d: %3s %3s %3s %3s' % (busnum, arr[0], arr[1], arr[2], arr[3])

while(1):
    zeroBus = readBus(tof_arr0)
    prettyPrint(0, zeroBus)
    time.sleep(delay)

    oneBus = readBus(tof_arr1)
    prettyPrint(1, oneBus)
    time.sleep(delay)
    print ()



