#import serial

#ser = serial.Serial("/dev/ttyACM0", 9600)


# Welcome to Vi's magical interactive tutorial!
# Here we're going to be making an interactive control for our robot because I hate never ending loops and by consequence most of embedded electronics.
# Let's get started!



def sendInstructionsToRobot(direction,power,time):

    #Alright, listen up nitwits. And I mean you, future Vi since you're probably the biggest one out there and both of us know it.
    # This command is what you use to send stuff to the robot. You do not deal with serial interfaces everywhere, including what you pull out of your ass.
    # If you want a different name because your fingers hurt so much, go ahead.

    # Converts the direction into the number the arduino needs.
    direction_raw = convertDirectionsToNumber(direction)
    power_raw = power         # value is from 0 to 100 - denotes percentage of max power.
    time_raw  = time*1000     # time_raw in milliseconds. I like to think in seconds because I'm a fucking human

    def convertToSerialString(direction,power,time):
        return str(direction) + " " + str(power) + " " + str(time)


    serialString = convertToSerialString(direction_raw,power_raw,time_raw)
    return serialString

# What you actually do
#    inputData = raw_input("dir speed interval\n")
#    #print(type(inputData))
#    ser.write(inputData)

def convertDirectionsToNumber(direction = None ):
    #So I like directions to be actual directions instead of numbers. Sue me. And yes, it's gonna be an compass point. Long live my shitty code.
    # Converting my direction into an actual number.
    #Quick Reference
    #Starts at 1, rotate and increase clockwise and stops at 8. 9 spins clockwise and 10 is counterclockwise

    #Sanitizing convertDirectionToNumber
    if direction == None:
        direction = 1 # let's assume it wants to move forward.

    # Python's somewhat graceful implementation of dictionaries.
    directionList = {
        #Actual Directions
        "N"   : 1,
        "NE"  : 2,
        "E"   : 3,
        "SE"  : 4,
        "S"   : 5,
        "SW"  : 6,
        "W"   : 7,
        "NW"  : 8,

        # Spins the robot
        "CW"  : 9,
        "CCW" : 10
    }
    direction_raw = directionList.get(direction, direction)    # 0 is the error code for this stuff anyway. For now, it's the direction itself.

    if 1 <= direction_raw <= 10:
        return direction_raw
    else:
        raise ValueError('Invalid input. Please enter compass points or CW or CCW') # Definitely a bit of paranoia but I don't know who's going to be looking at this code.






def rotate(degrees, spinDirection = None, power = None):
    #degrees is the values given to us in degrees.
    #I'm gonna assume that you have two types of people in the world, those who think a negative number is counterclockwise and those who have no idea what you're talking about.
    #Let's cater to both using the second argument that's assumed to be clockwise.


    # All default arguments in Python's shitty way.
    if spinDirection is None:
        spinDirection = "CCW"
        # If the argument isn't given, let's assume it's clockwise.
    if power is None:
        power = 50
        # If the argument isn't given, let's assume it's clockwise.



    # Sanitizing values given to me to play with
    if degrees < 0:
        # if value is negative, switch the sign and change the direction.
        # Company policy is to always be positive. I hate it. I'm just joking here.
        degrees = -degrees
        if spinDirection == "CCW":
            spinDirection = "CW"
        elif spinDirection == "CW":
            spinDirection = "CCW"


    # Converting degrees to actual time
    # This might be a bit tricky and there's a better solution than hardcoding it. Philip, if you're reading this, please read data and actually do something better.
    # Must add code here
    power = power #This is pretty dumb. I know

    #Actual command after all these shenanigans.

    return sendInstructionsToRobot(spinDirection,power,1)


if __name__ == "__main__":
    print(convertDirectionsToNumber("NW"))
    print(sendInstructionsToRobot("NW",50,1))
    print(sendInstructionsToRobot("N",50,1))

    print(rotate(degrees = -90,
                 power = 50,
                 spinDirection = "CW"))











