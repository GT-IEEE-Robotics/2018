import subprocess
command1 = 'rm build/lib.linux-armv7l-2.7/RangeFinder_C.so'
command2 = 'python setup.py build'
command3 = 'cp build/lib.linux-armv7l-2.7/RangeFinder_C.so RangeFinder_C.so'
subprocess.call(command1, shell=True)
subprocess.call(command2, shell=True)
subprocess.call(command3, shell=True)
print ""
   
from RangeFinder import RangeFinder

x = RangeFinder()
for i in range(800):
    dist1 = x.getDistance(1) #get distance from sensor 1
    dist2 = x.getDistance(2) #get distance from sensor 2
    dist3 = x.getDistance(3)
    dist4 = x.getDistance(4)
    print 'd1: ', dist1, ' d2: ', dist2, ' d3: ', dist3, ' d4: ', dist4

