# use a class with tinker

#import serial
from Tkinter import *

# ser = serial.Serial("/dev/ttyACM0", 9600)

class Application(Frame):
    """ Example Docstring """

    def __init__(self, master):
        """ another doc string """
        Frame.__init__(self, master)
        self.grid(row = 0, column = 0)
        self.speed = 0
        self.button0Flag = False
        self.button1Flag = False
        self.button2Flag = False
        self.button3Flag = False
        self.button4Flag = False
        self.button5Flag = False
        self.button6Flag = False
        self.button7Flag = False
        self.button8Flag = False

        self.button0 = Button(self, text="stop", width=15)
        self.button0.grid(row = 1, column = 1, padx=(10, 0), pady=(10, 0))
        self.button0["command"] = self.stop

        self.button1 = Button(self, text="forward", width=15)
        self.button1.grid(row = 0, column = 1, padx=(10, 0), pady=(10, 0))
        self.button1["command"] = self.forward

        self.button2 = Button(self, text="forwardRight", width=15)
        self.button2.grid(row = 0, column = 2, padx=(10, 0), pady=(10, 0))
        self.button2["command"] = self.forwardRight

        self.button3 = Button(self, text="right", width=15)
        self.button3.grid(row = 1, column = 2, padx=(10, 0), pady=(10, 0))
        self.button3["command"] = self.right

        self.button4 = Button(self, text="backwardRight", width=15)
        self.button4.grid(row = 2, column = 2, padx=(10, 0), pady=(10, 0))
        self.button4["command"] = self.backwardRight

        self.button5 = Button(self, text="backward", width=15)
        self.button5.grid(row = 2, column = 1, padx=(10, 0), pady=(10, 0))
        self.button5["command"] = self.backward

        self.button6 = Button(self, text="backwardLeft", width=15)
        self.button6.grid(row = 2, column = 0, padx=(10, 0), pady=(10, 0))
        self.button6["command"] = self.backwardLeft

        self.button7 = Button(self, text="left", width=15)
        self.button7.grid(row = 1, column = 0, padx=(10, 0), pady=(10, 0))
        self.button7["command"] = self.left

        self.button8 = Button(self, text="forwardLeft", width=15)
        self.button8.grid(row = 0, column = 0, padx=(10, 0), pady=(10, 0))
        self.button8["command"] = self.forwardLeft

        self.button9 = Button(self, text="clockwise", width=15)
        self.button9.grid(row = 4, column = 0, padx=(10, 0), pady=(10, 0))
        self.button9["command"] = self.clockwise

        self.button10 = Button(self, text="counterClockwise", width=15)
        self.button10.grid(row = 4, column = 1, padx=(10, 0), pady=(10, 0))
        self.button10["command"] = self.counterClockwise

     
        self.entry0 = Entry(self, text="Speed", width=15)
        self.entry0.grid(row = 3, column = 0, padx=(10, 0), pady=(10, 0))

        self.button11 = Button(self, text="speedInput", width=15)
        self.button11.grid(row = 3, column = 1, padx=(10, 0), pady=(10, 0))
        self.button11["command"] = self.speedInput

    def speedInput(self):
        try:
            self.speed = int(self.entry0.get())
        except Exception as e:
            print(e.printStackTrace())

    def stop(self):
        # ser.write("0 0 1000")
        pass

    def forward(self):
        # ser.write("1 100 1000")
        pass

    def forwardRight(self):
        # ser.write("2 100 1000")
        pass

    def right(self):
        # ser.write("3 100 1000")
        pass

    def backwardRight(self):
        # ser.write("4 100 1000")
        pass

    def backward(self):
        # ser.write("5 100 1000")
        pass

    def backwardLeft(self):
        # ser.write("6 100 1000")
        pass

    def left(self):
        # ser.write("7 100 1000")
        pass

    def forwardLeft(self):
        # ser.write("8 100 1000")
        pass

    def clockwise(self):
        # ser.write("9 100 1000")
        pass

    def counterClockwise(self):
        # ser.write("10 100 1000")
        pass



root = Tk()

root.title("GT IEEE Robot GUI")
root.geometry("530x400")

app = Application(root)

root.mainloop()