#import Adafruit_BBIO.GPIO as GPIO
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
import RangeFinder_C as sensor

class RangeFinder:

    def __init__(self):
        sensor_pins = [12, 15, 23, 25, 27]
	self.addresses   = [0x31, 0x32, 0x33, 0x34, 0x35]
	for pin in sensor_pins:
            GPIO.setup(pin, GPIO.OUT)
            GPIO.output(pin, 0)
	for i in range(1):
	    GPIO.output(sensor_pins[i], 0)
	    sensor.setAddress(self.addresses[i])

    def __del__(self):
        GPIO.cleanup()

    def getDistance(self, sensNum):
        addr = self.addresses[sensNum-1]
        return sensor.getDistance(addr)

