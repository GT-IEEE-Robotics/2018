from filterpy.kalman import KalmanFilter
class Kalman(object):

  def __init__(self,initialPosition,timeStep):

    # Number of types of data we're getting. Since the distance sensor only cares about position, we only use position
    dimX = 2
    # Number of distance sensor we have
    dimZ = 1
    self.f = KalmanFilter(dim_x=dimX, dim_z=dimZ)
    # Initial Position & Velocity Matrix
    
    if initialPosition is None: 
      self.f.x = np.array([0., 0.,             #1
                           0., 0.,             #2
                           0., 0.,             #3
                           0., 0.,             #4
                           0., 0.,             #5
                           0., 0.,             #6
                           0., 0.,             #7
                           0., 0. ])           #8
      # Insert warning over here when you figure out which library you're using.
    
    elif isinstance(initialPosition,List):  
      initialPosition = nd.array(initialPosition) 
      self.f.x = initialPosition
      # Insert warning over passing non-numpy arrays into this function
    
    
    else:
      self.f.x = initialPosition
      # You should really check if this is a numpy array and not some random bullshit.
    # State transition matrix
    if timeStep is None:
      dt = 0.001     # Time step is in the order of milliseconds
    else:
      dt = timeStep
    
    self.f.F = np.array([[1., dt, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 1., dt, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 1., dt, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 1., dt, 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 1., dt, 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., dt, 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., dt, 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., dt],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1.]])
    # Measurement function
    
    # Effectively reduces the position & velocity vector to just a position vector
    matrixA =  np.array([[1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0.],
                         [0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0.]])
    
    self.f.H = matrixA       # Why am I calling this matrixA instead of just assigning it directly? Because I might needto switch out stuff later. Fuck YAGNI.
    # The process noise is np.eye(dim_x) by default so you can just multiply by some constant
    # This assumes that each sensor is independent from each other.
    self.f.P *= 1000.
    # Measurement noise
    self.f.R = 5

  def predict(self):
    stuff = self.f.predict()

    return [x = ,
            y = ,
            theta = ] 


  def update(self,z):
    if z is None:
      raise ValueError("You have passed no value to update the Kalman Filter")
    
    self.f.update(z)
