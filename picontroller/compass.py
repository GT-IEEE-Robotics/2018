class Compass(object):
  N, NE, E, SE, S, SW, W, NW = range(1,9)
  CW, CCW = range(9,11)

  def __init__(self,value):
    if isinstance(value,basestring):
      self.value = Compass.convert(value) 
      #If the user enters in a string instead of a number or the class defined static variables, convert it to the string.
    elif 1 <= value <= 10:
      self.value = value
    else:
      raise ValueError("Compass is given invalid argument")
  def __repr__(self):
    return "Compass Direction" + Compass.convert(self.value)  #Should return the string representation of the value
  @staticmethod
  def convert(direction = None):
    #Sanitizing inputs
    if direction == None:
        raise ValueError('Compass direction is not given. Please enter valid input')
  
    # If the input is a number, return a string
    if 1 <= direction <= 10:
       directionList = {
        1:"N",
        2:"NE",
        3:"E",
        4:"SE",
        5:"S",
        6:"SW",
        7:"W",
        8:"NW",
        9:"CW",
        10:"CCW"
       }
       direction_raw = directionList.get(direction, None)
       if direction_raw is not None:
         return direction_raw
       else:
         raise ValueError('Compass direction should be a valid integer number from 1 to 10')
    # If the input is a string, return a number
  
    if isinstance(direction, basestring):
      directionList = {
          # Actual Directions
          "N"   : Compass.N,
          "NE"  : Compass.NE,
          "E"   : Compass.E,
          "SE"  : Compass.SE,
          "S"   : Compass.S,
          "SW"  : Compass.SW,
          "W"   : Compass.W,
          "NW"  : Compass.NW,
          # Spins the robot
          "CW"  : Compass.CW,
          "CCW" : Compass.CCW
       }
      direction_raw = directionList.get(direction, None)
      if 1 <= direction_raw <= 10:
        return direction_raw
      else:
        raise ValueError('Compass direction should be a valid string as an input.')
       # Somehow, you've reached here. This should not happen but whatever, raise the error
      raise ValueError('Invalid input - input entered is neither string nor number')

# Defining keywords for people to use
# When this package is imported, the user should be able to use the keywords without worrying about refering to the correct class name.
# In short, they can use N, NW and so on without saying CompassDirection.N or anything like that.
N   = Compass.N
NE  = Compass.NE
E   = Compass.E
SE  = Compass.SE
S   = Compass.S
SW  = Compass.SW
W   = Compass.W
NW  = Compass.NW
CW  = Compass.CW
CCW = Compass.CCW
