import subprocess
command1 = 'rm build/lib.linux-armv7l-2.7/RangeFinder_C.so'
command2 = 'python setup.py build'
command3 = 'cp build/lib.linux-armv7l-2.7/RangeFinder_C.so RangeFinder_C.so'
subprocess.call(command1, shell=True)
subprocess.call(command2, shell=True)
subprocess.call(command3, shell=True)
print ""

import Adafruit_BBIO.GPIO as GPIO
import RangeFinder_C as sensor

GPIO.setup("P9_12", GPIO.OUT)
GPIO.output("P9_12", GPIO.LOW)
GPIO.setup("P9_15", GPIO.OUT)
GPIO.output("P9_15", GPIO.LOW)

# sensor.say_hello("motherfuckers")
#sensor.getDistance(0x29) #not gonna work with gpio low

GPIO.output("P9_12",GPIO.HIGH)
sensor.setAddress(0x31) # sets 0x29 addr to the provided addr
sensor.getDistance(0x31)

GPIO.output("P9_15",GPIO.HIGH)
sensor.setAddress(0x32) # sets 0x29 addr to the provided addr
sensor.getDistance(0x32)

print 'testing both now\n'
for i in range(400):
    dist1 = sensor.getDistance(0x31)
    dist2 = sensor.getDistance(0x32)
    print 'dist1: ',dist1,', dist2: ',dist2

GPIO.cleanup()

#for i in range(500):
#    print sens1.getDistance()
    

