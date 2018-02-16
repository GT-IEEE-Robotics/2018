import numpy as np

class Sensor(object):

  def __init__(self,parameter,resolution, initialEstimate = None,linearTransform = None, offset = None):

    if parameter is None:
      raise ValueError("No parameter passed to Sensor")
    elif not 0 <= parameter <= 1:
      raise ValueError("Parameter must lie between zero and one.")
    else:
      self.parameter = parameter

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

    if resolution is None:
      raise ValueError("Enter valid resolution")
    else:
      self.resolution = resolution


    if linearTransform is None:
      self.linearTransform = np.eye(2)*100
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
    return np.ones(distance.shape)

  def query(self):
    A = self.estimate

    #Get the average of every two intervals.       
    A = (A[::2] + A[1::2]) / 2

    # Weight our measurements in terms of the error estimates
    eA = self.errorEstimate(A)
    denom = eA[:2] + eA[2:]

    denom = np.concatenate((denom,denom))
    A     = np.multiply(A,eA[   [2,3,0,1]   ]) / denom




    # Finding the difference between every other element of form [C - A, D - B]
    coordinate = (A[[2,3]]  - A[[0,1]]) / 2      # of form x & y
    print "poop"
    print coordinate




    # Converting our coordinate into something someone else can use intuitively
    coordinate = coordinate

    coordinate = np.dot(self.linearTransform,coordinate) + self.offset

    print coordinate
    coordinate = coordinate  //  self.resolution                 # divides it by the required resolution
    print coordinate

    # Finding the "theta" of the inclination of the robot.
    A = self.estimate

    #Get the average of every two intervals.       
    A = A[::2] - A[1::2]
    A = A[np.argsort(eA)]       # Sort in terms of lower errorEstimate
    theta = np.sum(A[:2:1])

    ans = {}
    ans["x"]     = coordinate[0]
    ans["y"]     = coordinate[1]
    ans["theta"] = theta

    return ans



if __name__ == "__main__":
  k = Sensor(parameter = 0.5,resolution = 1)
  k.update(np.array([1,2,3,4,5,6,7,8]))
  k.update(np.array([1,2,3,4,5,6,7,8]))
  k.update(np.array([1,2,3,4,5,6,7,8]))
  k.update(np.array([1,2,3,4,5,6,7,8]))
  print k.query()
