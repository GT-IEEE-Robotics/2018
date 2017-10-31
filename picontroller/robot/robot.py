import Position.Coordinate

class Robot(object):
#  def __init__(self):

  def __init__(self,position):

    if (position is None) or (type(position) is Coordinate):
      raise ValueError('Initial location is not specified')
    self.position = position
