#!/usr/bin/python

import time
import VL53L0X
import RPi.GPIO as GPIO



# GPIO for Sensor 1 shutdown pin
sensor1_shutdown = 20
# GPIO for Sensor 2 shutdown pin
sensor2_shutdown = 16
# GPIO for sensor 3 shutdown pin
sensor3_shutdown = 26
# GPIO for sensor 4 shutdown pin
sensor4_shutdown = 12

global tof = None
global tof1 = None
global tof2 = None
global tof3 = None

def distance_sensor_startup():
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
    tof = VL53L0X.VL53L0X(address=0x2B)
    tof1 = VL53L0X.VL53L0X(address=0x2D)
    tof2 = VL53L0X.VL53L0X(address=0x2A)
    tof3 = VL53L0X.VL53L0X(address=0x2C)

    # Set shutdown pin high for the first VL53L0X then
    # call to start ranging
    GPIO.output(sensor1_shutdown, GPIO.HIGH)
    time.sleep(0.50)
    tof.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

    # Set shutdown pin high for the second VL53L0X then
    # call to start ranging
    GPIO.output(sensor2_shutdown, GPIO.HIGH)
    time.sleep(0.50)
    tof1.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

    # Set shutdown pin high for the first VL53L0X then
    # call to start ranging
    GPIO.output(sensor3_shutdown, GPIO.HIGH)
    time.sleep(0.50)
    tof2.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)

    # Set shutdown pin high for the first VL53L0X then
    # call to start ranging
    GPIO.output(sensor4_shutdown, GPIO.HIGH)
    time.sleep(0.50)
    tof3.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)



    timing = tof.get_timing()
    if (timing < 20000):
        timing = 20000
    print ("Timing %d ms" % (timing/1000))

## Returns dist of sensor_num in mm
def get_dist(sensor_num):
    val = -1
    if sensor_num == 0:
        val = tof.get_distance()
    elif sensor_num == 1:
        val = tof1.get_distance()
    elif sensor_num == 2:
        val = tof2.get_distance()
    elif sensor_num == 3:
        val = tof3.get_distance()
    else:
        print("Invalid sensor num %d".format(sensor_num))

    if val < 0:
        print("Error reading from sensor %d".format(sensor_num))

def distance_sensor_shutdown():
    tof.stop_ranging()
    GPIO.output(sensor1_shutdown, GPIO.LOW)
    tof1.stop_ranging()
    GPIO.output(sensor2_shutdown, GPIO.LOW)
    tof2.stop_ranging()
    GPIO.output(sensor3_shutdown, GPIO.LOW)
    tof3.stop_ranging()
    GPIO.output(sensor4_shutdown, GPIO.LOW)

