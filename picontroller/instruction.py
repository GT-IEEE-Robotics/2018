import logging #This is to send logs of instructions sent directly to robot.
import serial # Serial interface to talk to robot's motor controllers

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# create a file handler
handler = logging.FileHandler('instruction.log')
handler.setLevel(logging.INFO)
logger.addHandler(handler)

class Instruction(object):
  <<instructionInit>>
  <<instructionExecute>>
