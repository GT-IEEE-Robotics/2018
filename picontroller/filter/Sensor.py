import numpy as np
import warnings #Used primarily to give warnings about default values
import logging  #Used to log information that might help with debugging


from ...2018.picontroller import coordinate


logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)



class IIR(object):

  def __init__(self,parameter,
                    resolution,
                    initialEstimate,
                    linearTransform,
                    offset):
  
    # Creates a logger for this class.
    logger.info('Creating a Sensor Object')
  
    if parameter is None:
      raise ValueError("""No sensitivity parameter passed to Sensor. Must lie between 1 & 0.
                          This parameter decides the relative importance between your current estimate and the measurements you give it.
                          The closer to zero, the less sensitive you are to new inputs and vice versa.""")
    elif not 0 < parameter < 1:
      raise ValueError("Parameter must lie between zero and one.")
    else:
      self.parameter = parameter
    
    logger.debug('Parameter passed to Sensor object: %s',self.parameter)
    if initialEstimate is None:
      warnings.warn("""Initial sensor estimate is not provided.
                       Defaulting to numpy array of zeros.
                       Sensor is better if initial estimate is given.""")
      self.estimate = np.array([0.,   #1
                                0.,   #2
                                0.,   #3
                                0.,   #4
                                0.,   #5
                                0.,   #6
                                0.,   #7
                                0.])  #8
    else:
      self.estimate = initialEstimate
    
    logger.debug('Initial Estimate passed to Sensor object: %s',self.estimate)
    if resolution is None:
      raise ValueError("Invalid argument: Enter valid resolution")
    else:
      self.resolution = resolution
    
    logger.debug('Resolution passed to Sensor object: %s',self.resolution)
    if linearTransform is None:
      self.linearTransform = np.eye(2)*100
    else:
      self.linearTransform = linearTransform
    
    logger.debug('linear transform passed to Sensor object: %s',self.linearTransform)
    if offset is None: 
      self.offset = np.array([0,0])
      warnings.warn("""Initial offset is not provided.
                     Defaulting to numpy array of zeros.""")
    else:
      self.offset = offset
    
    logger.debug('Offset passed to Sensor object: %s',self.offset)
  
    logger.info('Sensor Object created')
  def update(self, current):
    if current is None:
      logger.debug("No new measurement passed to filter.")
      raise ValueError("No new measurement passed to the filter.")
    elif current.shape is not self.estimate.shape:
      logger.info("Current estimate & Measurement mismatch")
      logger.debug("Current measurement shape  : %s", current.shape)
      logger.debug("Estimated measurement shape: %s", self.estimate.shape)
      raise ValueError("The new measurement has a different dimension than the estimate.")
    else:
      logger.debug("New measurement passed to filter ")
      self.estimate = self.estimate * (1. - self.parameter) + current * (self.parameter)
  def errorEstimate(self,distance):
    # insert a dict for the distance error estimates.
    # Make it a vectorized function for this.
  
    return np.ones(distance.shape)
  def query(self):
    A = self.estimate
  
    #Get the average of every two intervals.   
    A = A.reshape(reshape((A.size/2, 2)))
    A = A.sum(axis=1) / 2
  
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

  print("Hello")
  print(sys.modules[__name__])
