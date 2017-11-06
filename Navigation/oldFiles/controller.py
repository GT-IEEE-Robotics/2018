import logging #This is to send logs of instructions sent directly to robot.
import serial # Serial interface to talk to robot's motor controllers

ser = serial.Serial("/dev/ttyACM0", 9600) #The only interface we talk to.

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# create a file handler
handler = logging.FileHandler('instruction.log')
handler.setLevel(logging.INFO)
logger.addHandler(handler)

class Instruction(object):
  def __init__(self,direction = None, power = None, time = None):

    #sanitizing input
    if direction_input == None or power_input == None or time_input == None:
      raise ValueError('Invalid input. Please enter valid input.') # Honestly, we should be saying that the default setting is something. But I want the users to actually say something. They can put default values in later.

    if not (0 <= power <= 100):
      raise ValueError('Invalid input. Power is a quantity between 0 and 100.')

    if not (time >= 0):
      raise ValueError('Invalid input. Time must always be a positive quantity.')

    # Actually saving input.
    self.direction = direction
    self.power = power
    self.time = time

  def execute(self):
    
    def convertToSerialString(direction,power,time):
      return str(direction) + " " + str(power) + " " + str(time)

    instruction = convertToSerialString(self.direction,self.power,self.time)
    logger.info(instruction)
    # ser.write(instruction)         #Actually send stuff to the robot.
