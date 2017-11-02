# /usr/lib/python2.7/dist-packages/qrtools.py

import qrtools
from qrtools import QR

#set up color dictionary
colors = {'yellow', 'red', 'blue','green'}

#function definitions
def filterColors(symList):
    if not symList:
	print 'failed to filter colors. list is emtpy'
	return symList

    for element in symList:
	if element[0] not in colors:
	    symList.remove(element)


def get_UpperRightColor(symList):
    # Note that I made symList to be a list with tuples as elements.
    # each element is of form:
    #         (color_string, location_tuple)
    # where location_tuple is a tuple of form:
    #         (x_coordinate, y_coordinate)
    #
    # so overall:
    #   ( color_string, (x_coordinate,y_coordinate) )
    #

    rightMostX = 0;
    upperMostY = 9001; #it's over 9000
    resultColor = 'emptyList'
    if not symList:
	print 'failed to get upper right color. list is empty'
	return symList

    for element in symList:
        x = element[1][0] / 10 # access x coordinate & divide by 10 to filter
        y = element[1][1] / 10 # access y coordinate & divide by 10 to filter
	color = element[0]     # access element's color
        #print x,y,color,x>=rightMostX,y<=upperMostY,resultColor #debug print
	if x >= rightMostX and y <= upperMostY:
	    rightMostX = x
	    upperMostY = y
	    resultColor = color
	    #print 'new result: ',resultColor #debug print

    return resultColor

# main code:

myCode = QR()
myCode.set_timeOut(5)
maxTimeoutCount = 3
timeoutCount = 0

list = []
while not list:
    myCode.decode_webcam()
    list = myCode.get_symList()
    if not list:
	print 'failed to read a code, trying again...'
	timeoutCount+=1
	if timeoutCount >= maxTimeoutCount:
	    print 'max timouts exceeded. now exiting'
	    break
	else:
            continue
    print 'successful read'
    print 'Raw List: ', list
    filterColors(list)
    print 'Filtered List: ',list
    if not list:
        print 'Filtered list is empty, retrying...'

print 'Upper Right: ', get_UpperRightColor(list)
