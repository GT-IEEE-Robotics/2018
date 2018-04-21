#!/bin/python

#package python-lirc https://pypi.python.org/pypi/python-lirc/
import lirc

sockid = lirc.init("ieee_southeastcon_program")
while (1):
	input = lirc.nextcode()
	print(input)
