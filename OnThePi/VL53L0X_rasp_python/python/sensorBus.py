
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
import VL53L0X_bus1
import RPi.GPIO as GPIO



def initBus(bus_num, gpio_arr, addr_arr):
    GPIO.setwarnings(False)

    if bus_num == 0:
	import VL53L0X as vl_lib
    else:
	import VL53L0X_bus1 as vl_lib

    print ('vllib', vl_lib)

    # Setup GPIO for shutdown pins on each VL53L0X
    # Set all shutdown pins low to turn off each VL53L0X
    GPIO.setmode(GPIO.BCM)
    for pin in gpio_arr:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)

    # Keep all low for 500 ms or so to make sure they reset
    time.sleep(0.50)

    # Create one object per VL53L0X passing the address to give to
    # each.
    tof_arr = [vl_lib.VL53L0X(address=addr) for addr in addr_arr]


    for i in range(len(gpio_arr)):
        pin = gpio_arr[i]
        tof = tof_arr[i]

        GPIO.output(pin, GPIO.HIGH)
        time.sleep(0.50)
        tof.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)


    return tof_arr

def stopBus(tof_arr, gpio_arr):
    for i in range(len(tof_arr)):
        tof_arr[i].stop_ranging()
        GPIO.output(gpio_arr[i], GPIO.LOW)

def readBus(tof_arr):
    timing = tof_arr[0].get_timing()
    if (timing < 20000):
        timing = 20000

    distances = [tof.get_distance() for tof in tof_arr]
    time.sleep(timing/1000000)

    return distances


 
