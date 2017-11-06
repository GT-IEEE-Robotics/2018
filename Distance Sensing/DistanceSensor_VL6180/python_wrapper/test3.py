
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
GPIO.setup("P9_23", GPIO.OUT)
GPIO.output("P9_23", GPIO.LOW)
GPIO.setup("P9_25", GPIO.OUT)
GPIO.output("P9_25", GPIO.LOW)

# sensor.say_hello("motherfuckers")
#sensor.getDistance(0x29) #not gonna work with gpio low

GPIO.output("P9_12",GPIO.HIGH)
sensor.setAddress(0x31) # sets 0x29 addr to the provided addr
print 'd1: ', sensor.getDistance(0x31)

GPIO.output("P9_15",GPIO.HIGH)
sensor.setAddress(0x32) # sets 0x29 addr to the provided addr
print 'd2: ', sensor.getDistance(0x32)

GPIO.output("P9_23",GPIO.HIGH)
sensor.setAddress(0x33) # sets 0x29 addr to the provided addr
print 'd3: ', sensor.getDistance(0x33)

#GPIO.output("P9_25",GPIO.HIGH)
#sensor.setAddress(0x34) # sets 0x29 addr to the provided addr
#print 'd4: ', sensor.getDistance(0x29)

hityet = False
grab = False
hitcount = 0

print 'testing both now\n'
while True:
    dist1 = dist2 = dist3 = 0
    for i in range(5):
        dist1 += sensor.getDistance(0x31)
        dist2 += sensor.getDistance(0x32)
        dist3 += sensor.getDistance(0x33)
    dist1 /= 5

    dist2 /= 5
    dist2 -= 4

    dist3 /= 5

    if (abs(dist2-dist3) < 20) and (dist2+dist3)/2 < 100:
	hityet = True
	hitcount += 1
    else: 
	hityet = False
        hitcount = 0
	grab = False
    if hitcount > 10:
        grab = True
    print 'd1: ', dist1, '\td2: ', dist2, '\td3: ', dist3, hityet, '\tgrab?: ', grab

GPIO.cleanup()
   

