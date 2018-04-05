from sensorBus0 import *
from sensorBus1 import *
import time


initBus0()
initBus1()

delay = 0.1

def prettyPrint(busnum, arr):
    print 'bus%d: %3s %3s %3s %3s' % busnum, arr[0], arr[1], arr[2], arr[3]

while(1):
    zeroBus = readBus0()
    prettyPrint(0, zeroBus)
    time.sleep(delay)

    oneBus = readBus1()
    prettyPrint(1, oneBus)
    time.sleep(delay)
    print ()



