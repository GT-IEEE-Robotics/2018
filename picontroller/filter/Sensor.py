import numpy as np

class Sensor(object):

  def __init__(self,parameter,initialEstimate,linearTransform, offset):

    if parameter is None:
      raise ValueError("No parameter passed to Sensor")
    elif not 0 <= parameter <= 1:
      raise ValueError("Parameter must lie between zero and one.")

    if initialEstimate is None:
      self.estimate = np.array([0.,   
                                0.,
                                0.,
                                0.,
                                0.,
                                0.,
                                0.,
                                0.])
    else:
      self.estimate = initialEstimate

    if linearTransform is None:
      self.linearTransform = np.array([1,0],
                                      [0,1])
    else:
      self.linearTransform = linearTransform


    if offset is None: 
      self.offset = np.array([0,0])
    else:
      self.offset = offset

  def update(self, current):
    if current is None:
      raise ValueError("No current measurement passed to the filter")
    self.estimate = self.estimate * (1. - self.parameter) + current * (self.parameter)
    
  def errorEstimate(self,distance):

    # insert a dict for the distance error estimates.
    # Make it a vectorized function for this.
    return distance

  def query(self):
    A = self.estimate         

    #Get the average of every two intervals.       
    A = (A[::2] + A[1::2]) / 2

    # Weight our measurements in terms of the error estimates
    eA = errorEstimate(A)
    denom = eA[:2] + eA[2:]
    denom = np.concat(denom,denom)
    A     = np.multiply(A,eA[2,3,0,1]) / denom

    # Finding the difference between every other element of form [C - A, D - B]
    coordinate = (A[2::2]  - A[0:(len(A) - 2):2]) / 2      # of form x & y

    # Converting our coordinate into something someone else can use intuitively
    coordinate = coordinate * linearTransform + offset
    coordinate = coordinate  //  self.resolution                 # divides it by the required resolution


    # Finding the "theta" of the inclination of the robot.
    A = self.estimate

    #Get the average of every two intervals.       
    A = A[::2] - A[1::2]
    A = A[np.argsort(eA)]       # Sort in terms of lower errorEstimate
    theta = np.sum(A[:2:1])

    ans["x"] = 
    return np.concat(coordinate,np.array([theta]))
