import numpy as np
class Coordinate(np.ndarray):
  def __new__(cls, x,                  # Required argument - x coordinate
                   y,                  # Required argument - y coordinate
                   theta,              # Required argument - inclination of the robot with respect to the x axis.
                   info = None):              # Optional argument - Info about the numpy array in case you want to tag it with some information.
  
  
    # Sanitizing x and y values
    if (
        x is None or 
        y is None or 
        theta is None
       ):
      raise ValueError('Incomplete coordinate input. Please enter valid x, y & theta')
    
    def is_number(s):
        try:
            float(s)
            return True
        except ValueError:
            return False
    
    if (
        not (is_number(x) and 
             is_number(y) and
             is_number(theta)
            )
       ):
      raise ValueError('Incorrect input. Please use numbers only for x, y & theta arguments')
    # We need to make ndarray instance using x, y & theta values.
    dimension = np.dtype({'names':  ('x',  'y',  'theta'),
                          'formats':('f8', 'f8', 'f8')})
    input_array = np.array([(x,y,theta)],dimension)
    # We first cast to be our class type
    obj = np.asarray(input_array).view(cls)
    # add the new attribute to the created instance
    obj.info = info
  
    # Finally, we must return the newly created object:
    return obj
  def __array_finalize__(self, obj):
    # see InfoArray.__array_finalize__ for comments
    if obj is None: return
    self.info = getattr(obj, 'info', None)
  def __add__(self,other):
  
    return Coordinate(self["x"][0]     + other["x"][0],
                      self["y"][0]     + other["y"][0],
                      self["theta"][0] + other["theta"][0])
  def __sub__(self,other):
  
    return Coordinate(self["x"][0]     - other["x"][0],
                      self["y"][0]     - other["y"][0],
                      self["theta"][0] - other["theta"][0])

if __name__=="__main__":
  start = Coordinate(1,2,0)
  finish = Coordinate(4,5,0)
   
  print("The distance between start and finish is")
  distance = finish - start
  print(distance)
