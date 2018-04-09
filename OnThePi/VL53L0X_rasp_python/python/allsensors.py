from sensorBus import *
import time

delay = .5

gpio0_arr = [20, 26, 13, 6]
gpio1_arr = [12, 16, 19, 21]

addr_arr_bus0 = [0x20,0x21,0x22,0x23]
addr_arr_bus1 = [0x24,0x25,0x26,0x27]

#tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)
tof_arr1 = initBus(1, gpio1_arr, addr_arr_bus1)
tof_arr0 = initBus(0, gpio0_arr, addr_arr_bus0)

def prettyPrint(busnum, arr):
    print 'bus%d: %3s %3s %3s %3s' % (busnum, arr[0], arr[1], arr[2], arr[3])

while(1):
    oneBus = readBus(tof_arr1)
    prettyPrint(1, oneBus)
    time.sleep(delay)

    zeroBus = readBus(tof_arr0)
    prettyPrint(0, zeroBus)
    time.sleep(delay)

    #oneBus = readBus(tof_arr1)
    #prettyPrint(1, oneBus)
    #time.sleep(delay)

stopBus(tof_arr0, gpio0_arr)
stopBus(tof_arr1, gpio1_arr)
