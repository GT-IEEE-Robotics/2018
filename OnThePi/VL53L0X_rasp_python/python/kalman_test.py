import numpy as np
from time import sleep

import time
import VL53L0X
import RPi.GPIO as GPIO

tof = None
tof1 = None
tof2 = None
tof3 = None


def kalman_xy(x, P, measurement, R,
              motion = np.matrix('0. 0. 0. 0.').T,
              Q = np.matrix(np.eye(4))):
    """
    Parameters:
    x: initial state 4-tuple of location and velocity: (x0, x1, x0_dot, x1_dot)
    P: initial uncertainty convariance matrix
    measurement: observed position
    R: measurement noise
    motion: external motion added to state vector x
    Q: motion noise (same shape as P)
    """
    return kalman(x, P, measurement, R, motion, Q,
                  F = np.matrix('''
                      1. 0. 1. 0.;
                      0. 1. 0. 1.;
                      0. 0. 1. 0.;
                      0. 0. 0. 1.
                      '''),
                  H = np.matrix('''
                      1. 0. 0. 0.;
                      0. 1. 0. 0.'''))

def kalman(x, P, measurement, R, motion, Q, F, H):
    '''
    Parameters:
    x: initial state
    P: initial uncertainty convariance matrix
    measurement: observed position (same shape as H*x)
    R: measurement noise (same shape as H)
    motion: external motion added to state vector x
    Q: motion noise (same shape as P)
    F: next state function: x_prime = F*x
    H: measurement function: position = H*x

    Return: the updated and predicted new values for (x, P)

    See also http://en.wikipedia.org/wiki/Kalman_filter

    This version of kalman can be applied to many different situations by
    appropriately defining F and H
    '''
    # UPDATE x, P based on measurement m
    # distance between measured and current position-belief
    y = np.matrix(measurement).T - H * x
    S = H * P * H.T + R  # residual convariance
    K = P * H.T * S.I    # Kalman gain
    x = x + K*y
    I = np.matrix(np.eye(F.shape[0])) # identity matrix
    P = (I - K*H)*P

    # PREDICT x, P based on motion
    x = F*x + motion
    P = F*P*F.T + Q

    return x, P

##def getXY():
##    X = 0.0
##    Y = 0.0
##    ## get X and Y
##    v0 = tof.get_distance()
##    v1 = tof1.get_distance()
##    v2 = tof2.get_distance()
##    v3 = tof3.get_distance()
##
##    totalX = v0 + v3 + 76
##
##    X = v0 / totalX
##
##    totalY = v1 + v2 + 76
##
##    Y = v1 / totalY
##
##    return [X, Y]

#assuming no motion

def demo_measurement():
    # GPIO for Sensor 1 shutdown pin
    sensor1_shutdown = 20
    # GPIO for Sensor 2 shutdown pin
    sensor2_shutdown = 16
    # GPIO for sensor 3 shutdown pin
    sensor3_shutdown = 26
    # GPIO for sensor 4 shutdown pin
    sensor4_shutdown = 12

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

    x = np.matrix('0. 0. 0. 0.').T
    P = np.matrix(np.eye(4))*1000 # initial uncertainty
    R = 0.01**2

    while(True):
        v0 = tof.get_distance()
        v1 = tof1.get_distance()
        v2 = tof2.get_distance()
        v3 = tof3.get_distance()

        print v0
        print v1
        print v2
        print v3

        totalX = v0 + v3 + 76

        X = float(v0) / totalX

        totalY = v1 + v2 + 76

        Y = float(v1) / totalY
        meas = [X, Y]
        x, P = kalman_xy(x, P, meas, R)
        print x
        sleep(0.5)

    tof.stop_ranging()
    GPIO.output(sensor1_shutdown, GPIO.LOW)
    tof1.stop_ranging()
    GPIO.output(sensor2_shutdown, GPIO.LOW)
    tof2.stop_ranging()
    GPIO.output(sensor3_shutdown, GPIO.LOW)
    tof3.stop_ranging()
    GPIO.output(sensor4_shutdown, GPIO.LOW)


demo_measurement()

