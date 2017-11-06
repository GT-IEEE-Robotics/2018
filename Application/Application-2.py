# use a class with tinker

#import serial
import ttk
from Tkinter import *

# ser = serial.Serial("/dev/ttyACM0", 9600)

class Application(Frame):

    def __init__(self, master):
        Frame.__init__(self, master, background="#00629B")
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

        self.button0 = Button(self, text="Stop", width=15, highlightbackground="#00629B")
        self.button0.grid(row = 1, column = 1, padx=(10, 0), pady=(10, 0))
        self.button0["command"] = self.stop

        self.button1 = Button(self, text="Forward", width=15, highlightbackground="#00629B")
        self.button1.grid(row = 0, column = 1, padx=(10, 0), pady=(10, 0))
        self.button1["command"] = self.forward

        self.button2 = Button(self, text="Forward Right", width=15, highlightbackground="#00629B")
        self.button2.grid(row = 0, column = 2, padx=(10, 10), pady=(10, 0))
        self.button2["command"] = self.forwardRight

        self.button3 = Button(self, text="Right", width=15, highlightbackground="#00629B")
        self.button3.grid(row = 1, column = 2, padx=(10, 10), pady=(10, 0))
        self.button3["command"] = self.right

        self.button4 = Button(self, text="Backward Right", width=15, highlightbackground="#00629B")
        self.button4.grid(row = 2, column = 2, padx=(10, 10), pady=(10, 0))
        self.button4["command"] = self.backwardRight

        self.button5 = Button(self, text="Backward", width=15, highlightbackground="#00629B")
        self.button5.grid(row = 2, column = 1, padx=(10, 0), pady=(10, 0))
        self.button5["command"] = self.backward

        self.button6 = Button(self, text="Backward Left", width=15, highlightbackground="#00629B")
        self.button6.grid(row = 2, column = 0, padx=(10, 0), pady=(10, 0))
        self.button6["command"] = self.backwardLeft

        self.button7 = Button(self, text="Left", width=15, highlightbackground="#00629B")
        self.button7.grid(row = 1, column = 0, padx=(10, 0), pady=(10, 0))
        self.button7["command"] = self.left

        self.button8 = Button(self, text="Forward Left", width=15, highlightbackground="#00629B")
        self.button8.grid(row = 0, column = 0, padx=(10, 0), pady=(10, 0))
        self.button8["command"] = self.forwardLeft

        self.separator0 = ttk.Separator(self, orient="horizontal")
        self.separator0.grid(row = 3, column = 0)

        self.button9 = Button(self, text="Clockwise", width=15, highlightbackground="#00629B")
        self.button9.grid(row = 4, column = 0, padx=(10, 0), pady=(10, 0))
        self.button9["command"] = self.clockwise

        self.button10 = Button(self, text="Counter Clockwise", width=15, highlightbackground="#00629B")
        self.button10.grid(row = 4, column = 1, padx=(10, 0), pady=(10, 0))
        self.button10["command"] = self.counterClockwise

        self.entry0 = Entry(self, text="Speed", width=15, highlightbackground="#00629B")
        self.entry0.grid(row = 6, column = 0, padx=(10, 0), pady=(10, 10))

        self.button11 = Button(self, text="Speed", width=15, highlightbackground="#00629B")
        self.button11.grid(row = 6, column = 1, padx=(10, 0), pady=(10, 10))
        self.button11["command"] = self.speedInput

    def speedInput(self):
        try:
            self.speed = int(self.entry0.get())
            print "Speed:", self.speed
        except Exception as e:
            print(e.args)

    def stop(self):
        # ser.write("0 0 1000")
        print("Stop")

    def forward(self):
        # ser.write("1 100 1000")
        print("Forward")

    def forwardRight(self):
        # ser.write("2 100 1000")
        print("Forward Right")

    def right(self):
        # ser.write("3 100 1000")
        print("Right")

    def backwardRight(self):
        # ser.write("4 100 1000")
        print("Backward Right")

    def backward(self):
        # ser.write("5 100 1000")
        print("Backward")

    def backwardLeft(self):
        # ser.write("6 100 1000")
        print("Backward Left")

    def left(self):
        # ser.write("7 100 1000")
        print("Left")

    def forwardLeft(self):
        # ser.write("8 100 1000")
        print("Forward Left")

    def clockwise(self):
        # ser.write("9 100 1000")
        print("Clockwise")

    def counterClockwise(self):
        # ser.write("10 100 1000")
        print("Counter Clockwise")


root = Tk()
root.title("GT IEEE Robot GUI")
root.geometry("530x200")
app = Application(root)
root.mainloop()