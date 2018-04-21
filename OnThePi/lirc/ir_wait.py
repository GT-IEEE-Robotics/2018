#!/bin/python

#package python-lirc https://pypi.python.org/pypi/python-lirc/
import lirc

sockid = lirc.init("ieee_southeastcon_program")
input = lirc.nextcode()
while(input == ['pos']):
  print("Positioning IR Received")
  input = lirc.nextcode()

input = input[0]
button0 = input[0]
key = input[1]
button1 = input[2]

print("Path: ", button0, " ", key, " ", button1)
