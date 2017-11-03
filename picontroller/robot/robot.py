import position.coordinate as coordinate
import direction.vector as vector
import direction.compass as compass

class Robot(object):
#  def __init__(self):

  def __init__(self,position=None):
    if (position is None) or (type(position) is not Coordinate):
      raise ValueError('Initial location is not specified')
    self.position = position

  def move(self, direction=None,distance=None):
    
    if type(direction) is compass.Compass:
      # The user has given a compass point and expects us to move to that location. This is where things can get a littlw awry.

    if type(direction) is vector.Vector:
      # The user has given a vector and expects us to move to that location. 
      #If the distance is not specified, simply take the length of the vector. If distance is specified, use the distance instead.

  
  def vectorMove(self,vector=None,distance=None):
    if vector is None:
      raise ValueError("The vector input is not specified.")
    if type(vector) is not vector.Vector:
      raise ValueError("The vector input needs to be a vector")

    if distance is None:
    # If distance is none, change distance to the magnitude of the vector and use that.
      distance = vector.mag()
      
    #Convert the vector input into its norm. We're just going to divide the vector by its magnitude.
    vector = vector/vector.mag()


  def directionMove(self,vector=None,distance=None):
    if vector is None:
      raise ValueError("The vector input is not specified.")
    if type(vector) is not vector.Vector:
      raise ValueError("The vector input needs to be a vector")

    if distance is None:
      raise ValueError("")
      
    #Convert the vector input into its norm. We're just going to divide the vector by its magnitude.
    vector = vector/vector.mag()





    # Now, we need to convert a vector & distance into instructions for the robot. I'm implementing a naive way of doing it (assuming that
