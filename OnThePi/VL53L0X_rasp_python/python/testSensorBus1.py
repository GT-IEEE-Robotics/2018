
#!/usr/bin/python

# MIT License
# 
# Copyright (c) 2017 John Bryan Moore
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import time
import VL53L0X_bus1
import RPi.GPIO as GPIO

# GPIO for Sensor 1 shutdown pin
sensor5_shutdown = 12
# GPIO for sensor 3 shutdown pin
sensor6_shutdown = 16
# GPIO for Sensor 6 shutdown pin
sensor7_shutdown = 19
# GPIO for sensor 8 shutdown pin
sensor8_shutdown = 21


GPIO.setwarnings(False)

# Setup GPIO for shutdown pins on each VL53L0X
GPIO.setmode(GPIO.BCM)
GPIO.setup(sensor5_shutdown, GPIO.OUT)
GPIO.setup(sensor6_shutdown, GPIO.OUT)
GPIO.setup(sensor7_shutdown, GPIO.OUT)
GPIO.setup(sensor8_shutdown, GPIO.OUT)


# Set all shutdown pins low to turn off each VL53L0X
GPIO.output(sensor5_shutdown, GPIO.LOW)
GPIO.output(sensor6_shutdown, GPIO.LOW)
GPIO.output(sensor7_shutdown, GPIO.LOW)
GPIO.output(sensor8_shutdown, GPIO.LOW)

# Keep all low for 500 ms or so to make sure they reset
time.sleep(0.50)

# Create one object per VL53L0X passing the address to give to
# each.
tof5 = VL53L0X_bus1.VL53L0X(address=0x24)
tof6 = VL53L0X_bus1.VL53L0X(address=0x25)
tof7 = VL53L0X_bus1.VL53L0X(address=0x26)
tof8 = VL53L0X_bus1.VL53L0X(address=0x27)


# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor5_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof5.start_ranging(VL53L0X_bus1.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor6_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof6.start_ranging(VL53L0X_bus1.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor7_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof7.start_ranging(VL53L0X_bus1.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor8_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof8.start_ranging(VL53L0X_bus1.VL53L0X_BETTER_ACCURACY_MODE)

timing = tof5.get_timing()
if (timing < 20000):
    timing = 20000
print ("Timing %d ms" % (timing/1000))

while(1):
    distance = tof5.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof5.my_object_number, distance, (distance/10)))
    else:
        print ("%3d - Error" % tof5.my_object_number)

    distance = tof6.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof6.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof6.my_object_number)

    distance = tof7.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof7.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof7.my_object_number)

    distance = tof8.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof8.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof8.my_object_number)



    #time.sleep(timing/1000000.00)
    time.sleep(.1)

tof5.stop_ranging()
GPIO.output(sensor5_shutdown, GPIO.LOW)
tof6.stop_ranging()
GPIO.output(sensor6_shutdown, GPIO.LOW)
tof7.stop_ranging()
GPIO.output(sensor7_shutdown, GPIO.LOW)
tof8.stop_ranging()
GPIO.output(sensor8_shutdown, GPIO.LOW)




