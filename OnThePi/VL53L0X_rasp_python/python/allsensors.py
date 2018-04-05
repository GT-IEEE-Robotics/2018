from sensorBus0 import *
from sensorBus1 import *
import time


while(1):
  zeroBus = readBus0()
  oneBus = readBus1()
  print zeroBus
  time.sleep(.1)
  print oneBus
  print "\n"
  time.sleep(.1)
