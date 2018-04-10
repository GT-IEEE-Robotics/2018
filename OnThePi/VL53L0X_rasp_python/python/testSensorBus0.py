
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
import VL53L0X
import RPi.GPIO as GPIO

# GPIO for Sensor 1 shutdown pin
sensor1_shutdown = 20
# GPIO for sensor 3 shutdown pin
sensor2_shutdown = 26
# GPIO for Sensor 6 shutdown pin
sensor3_shutdown = 13
# GPIO for sensor 8 shutdown pin
sensor4_shutdown = 6


GPIO.setwarnings(False)

# Setup GPIO for shutdown pins on each VL53L0X
GPIO.setmode(GPIO.BCM)
GPIO.setup(sensor1_shutdown, GPIO.OUT)
GPIO.setup(sensor2_shutdown, GPIO.OUT)
GPIO.setup(sensor3_shutdown, GPIO.OUT)
GPIO.setup(sensor4_shutdown, GPIO.OUT)


# Set all shutdown pins low to turn off each VL53L0X
GPIO.output(sensor1_shutdown, GPIO.LOW)
GPIO.output(sensor2_shutdown, GPIO.LOW)
GPIO.output(sensor3_shutdown, GPIO.LOW)
GPIO.output(sensor4_shutdown, GPIO.LOW)

# Keep all low for 500 ms or so to make sure they reset
time.sleep(0.50)

# Create one object per VL53L0X passing the address to give to
# each.
tof1 = VL53L0X.VL53L0X(address=0x20)
tof2 = VL53L0X.VL53L0X(address=0x21)
tof3 = VL53L0X.VL53L0X(address=0x22)
tof4 = VL53L0X.VL53L0X(address=0x23)


# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor1_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof1.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor2_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof2.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor3_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof3.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

# Set shutdown pin high for the first VL53L0X then 
# call to start ranging 
GPIO.output(sensor4_shutdown, GPIO.HIGH)
time.sleep(0.50)
tof4.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

timing = tof1.get_timing()
if (timing < 20000):
    timing = 20000
print ("Timing %d ms" % (timing/1000))

while(1):
    distance = tof1.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof1.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof1.my_object_number)

    distance = tof2.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof2.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof2.my_object_number)

    distance = tof3.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof3.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof3.my_object_number)

    distance = tof4.get_distance()
    if (distance > 0):
        print ("sensor %3d - %3d mm, %3d cm" % (tof4.my_object_number, distance, (distance/10)))
    else:
        print ("%d - Error" % tof4.my_object_number)



    #time.sleep(timing/1000000.00)
    time.sleep(.10)

tof1.stop_ranging()
GPIO.output(sensor1_shutdown, GPIO.LOW)
tof3.stop_ranging()
GPIO.output(sensor2_shutdown, GPIO.LOW)
tof6.stop_ranging()
GPIO.output(sensor3_shutdown, GPIO.LOW)
tof8.stop_ranging()
GPIO.output(sensor4_shutdown, GPIO.LOW)




