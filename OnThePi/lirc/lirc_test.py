#!/bin/python

#package python-lirc https://pypi.python.org/pypi/python-lirc/
import lirc

sockid = lirc.init("ieee_southeastcon_program")
input = lirc.nextcode()
print(input)
lirc.deinit()
