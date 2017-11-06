import warnings   # Because warnings are wonderful and I don't know why people don't use them. You can write shortcuts in your code AND be safe!


#import serial

#ser = serial.Serial("/dev/ttyACM0", 9600)


# Here we're going to be making an interactive control for our robot because I hate never ending loops and by consequence most of embedded electronics.
# Let's get started!












class robot(object):




def sendInstructionsToRobot(direction,power,time):
    # Converts commands into the format expected by the motor controller

    # Sanitizing inputs to sendInstructionsToRobot will not be done since this particular function is likely to be called repeatedly. I mean honestly, this particular function should be written in C.

    # Converts the direction into the number the arduino needs.
    direction_raw = convertDirectionsToNumber(direction)
    power_raw = power         # value is from 0 to 100 - denotes percentage of max power.
    time_raw  = time*1000     # time_raw in milliseconds. I like to think in seconds because I'm a fucking human
<<<<<<< HEAD:picontroller/oldFiles/controllerInteractive.py
=======

    def convertToSerialString(direction,power,time):
        return str(direction) + " " + str(power) + " " + str(time)


    serialString = convertToSerialString(direction_raw,power_raw,time_raw)
    return serialString
>>>>>>> 567121e... Convert tuple output to Serial String in a nice inside function:piController/controllerInteractive.py

    def convertToSerialString(direction,power,time):
        return str(direction) + " " + str(power) + " " + str(time)

    return convertToSerialString(direction_raw,power_raw,time_raw)
# What you actually do
#    inputData = raw_input("dir speed interval\n")
#    #print(type(inputData))
#    ser.write(inputData)







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


    # Converting negative values to positive values with different directions
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

def move(direction = None ,power = None ,time = None):
    if direction == None:
        direction = "N"
        warnings.warn('Explicit direction not given. Assuming user wants robot to move forward.')
    if power == None:
        power = 50
        warnings.warn('Explicit power not given. Assuming user wants 50% power.')
    if time == None:
        time = 1
        warnings.warn('Explicit time not given. Assuming user wants interval of 1 second.')

    return sendInstructionsToRobot(direction,power,time)




















if __name__ == "__main__":
    print(convertDirectionsToNumber("NW"))
    print(sendInstructionsToRobot("NW",50,1))
    print(sendInstructionsToRobot("N",50,1))

    print(rotate(degrees = -90,
                 power = 50,
                 spinDirection = "CW"))

    print(move(direction = "N",
               power = 50,
               time = 1))



# Do vector implementation
# Make this a nice little library for other people to use
# Write half decent documentation for it
# Keypad implementation in python WASD for movement QE for rotation
# use number keys for speed. Change on the fly.

# Read up on SLAM algorithm and implement a coordinate system if you can.
# 














