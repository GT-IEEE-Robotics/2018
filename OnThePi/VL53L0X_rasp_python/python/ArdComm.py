import time
import serial


port = '/dev/ttyACM0'
ard = serial.Serial(port,115200)

def sendCommand(command):
  if (command == "stop"):
    ard.write("STOP\n")
  if (command == "forward"):
    ard.write("FORWARD\n")
  if (command == "backward"):
    ard.write("BACKWARD\n")
  if (command == "right"):
    ard.write("RIGHT\n")
  if (command == "left"):
    ard.write("LEFT\n")
  if (command == "cw"):
    ard.write("CW\n")
  if (command == "CCW\n"):
    ard.write("CCW\n")
  if (command == "newHeading"):
    ard.write("NEWHEADING\n")
  time.sleep(.1)

while(1):
  sendCommand("forward")
  time.sleep(2)
  sendCommand("stop")
  time.sleep(2)
  sendCommand("newHeading")
  time.sleep(2)

  sendCommand("backward")
  time.sleep(2)
  sendCommand("stop")
  time.sleep(2)
  sendCommand("newHeading")
  time.sleep(2)

  sendCommand("left")
  time.sleep(2)
  sendCommand("stop")
  time.sleep(2)
  sendCommand("newHeading")
  time.sleep(2)

  sendCommand("right")
  time.sleep(2)
  sendCommand("stop")
  time.sleep(2)
  sendCommand("newHeading")


