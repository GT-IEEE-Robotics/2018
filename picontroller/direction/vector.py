import numpy

#SDSDFDSFSD

class Vector(numpy.ndarray):

    def __new__(cls, x=None, y=None, info=None):

        # Sanitizing x and y values
        if x == None or y == None:
          raise ValueError('Incomplete vector input')

        def is_number(s):
            try:
                float(s)
                return True
            except ValueError:
                return False
        
        if not (is_number(x) and is_number(y)):
          raise ValueError('Incorrect vector input. Please use numbers only')
      
        # We need to make ndarray instance using x and y values.
        input_array = numpy.array([x,y])

        # We first cast to be our class type
        obj = numpy.asarray(input_array).view(cls)
        # add the new attribute to the created instance
        obj.info = info
        # Finally, we must return the newly created object:
        return obj

    def __array_finalize__(self, obj):
        # see InfoArray.__array_finalize__ for comments
        if obj is None: return
        self.info = getattr(obj, 'info', None)

    def __repr__(self):
        return "< "+str(self[0])+" "+str(self[1])+" >"

if __name__=="__main__":
    start = Vector(1,2)
    finish = Vector(4,5)

    distance = finish - start
    print(distance)
