from gameboard import *

#Functions that you are allowed to use and usage:

#robotMove(magnitude, direction), magnitude needs to be inches * 10
#direction can be "North", "South", "East", "West"

#robotRotate(magnitude, direction), magnitude is the amount of degrees you  want to turn
#direction can be "cw" for clockwise and "ccw" for counter-clockwise

#sensorReadings[0:7] = getDistanceSensorReadings() #no inputs but return 1x8 array
#of distance sensor readings

#printDistances(sensorReadings) input is a 1x8 array of distance sensor readings
#will simply print them to the console

#bool = treasurePickerUpper() #no inputs, will return a 0 or 1 depending if it
#worked or not. The only way this function will work if it is executed while the
#robot is in a 12x12 inch box to the RIGHT of the location of the treasure chest

#bool = flagturner() #no inputs, will return a 0 or a 1 depending if it worked or
#not. Will only work if the robot is in a 12x12 box directly in front of the
#flag turner

#IRCode = getIRCode() will return a list of 3 ints ~ either 0 or 1. Only call it once
#at the beginning of your function

#setRateOfTranslationMovement(time) this will set the rate of translation movement
#this has nothing to do with velocity control, it simply speeds up the animation
#time is in seconds, no return value
#default value is time = .01, smaller values increase the rate

#setRateOfRotationMovement(time) this will set the rate of rotational movement
#again, this has nothing to do with the angular velocty, it will simply speed
#up the animation. time is in seconds, no return value
#default value is time = .01, smaller values increase the rate

#partAC() this will complete part A and part C assuming that you are in a 12x12
#inch square in front of the pushbutton

#treasurePickerUpper() will pickup the treasure chest if you are in a 12x12 inch
#square to the right of the chest

#flagTurner() will light up the square in front of the pirate wheel green
#if you are in a 12x12 inch square in front of the flag


def test():
   IRcode = getIRCode()
   print IRcode[:]
   distanceSensors = [0, 0, 0, 0, 0, 0, 0, 0]
   distanceSensors = getDistanceSensorReadings()
   printDistances(distanceSensors)
   #raw_input("Press Enter to return")
   robotMove(120, "South")
   dididoit = partAC()
   #print "dididoit = ", dididoit
   robotMove(120, "North")
   raw_input("Press Enter to return")

random.seed()
init()
test()
