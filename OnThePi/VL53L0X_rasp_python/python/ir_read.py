import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

# Define function to measure charge time
def RC_Analog (Pin):
  counter = 0
  # Discharge capacitor
  GPIO.setup(Pin, GPIO.OUT)
  GPIO.output(Pin, GPIO.LOW)
  time.sleep(0.1)
  GPIO.setup(Pin, GPIO.IN)
  # Count loops until voltage across capacitor reads high on GPIO
  while(GPIO.input(Pin)==GPIO.LOW):
        counter =counter+1
  return counter

# Main program loop

while True:
  print RC_Analog(4) # Measure timing using GPIO4

