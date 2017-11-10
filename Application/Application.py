#import serial
import time
import ttk
from Tkinter import *

# higher level Controller so that I can stop writing serial strings
import picontroller.instruction as instruction

# ser = serial.Serial("/dev/ttyACM0", 9600)



class Application(Frame):

    def __init__(self, master):
        Frame.__init__(self, master, background="#00629B")
        self.grid(row = 0, column = 0)
        self.speed = 0

        self.button0 = Button(self, text="Stop", width=15, highlightbackground="#f00", bg="red")
        self.button0.grid(row = 1, column = 1, padx=(10, 0), pady=(10, 0))
        self.button0.bind("<ButtonRelease>", self.stop)

        self.button1 = Button(self, text="Forward", width=15, highlightbackground="#00629B")
        self.button1.grid(row = 0, column = 1, padx=(10, 0), pady=(10, 0))
        self.button1.bind("<ButtonPress>", self.forward)
        self.button1.bind("<ButtonRelease>", self.stop)

        self.button2 = Button(self, text="Forward Right", width=15, highlightbackground="#00629B")
        self.button2.grid(row = 0, column = 2, padx=(10, 10), pady=(10, 0))
        self.button2.bind("<ButtonPress>", self.forwardRight)
        self.button2.bind("<ButtonRelease>", self.stop)

        self.button3 = Button(self, text="Right", width=15, highlightbackground="#00629B")
        self.button3.grid(row = 1, column = 2, padx=(10, 10), pady=(10, 0))
        self.button3.bind("<ButtonPress>", self.right)
        self.button3.bind("<ButtonRelease>", self.stop)

        self.button4 = Button(self, text="Backward Right", width=15, highlightbackground="#00629B")
        self.button4.grid(row = 2, column = 2, padx=(10, 10), pady=(10, 0))
        self.button4.bind("<ButtonPress>", self.backwardRight)
        self.button4.bind("<ButtonRelease>", self.stop)

        self.button5 = Button(self, text="Backward", width=15, highlightbackground="#00629B")
        self.button5.grid(row = 2, column = 1, padx=(10, 0), pady=(10, 0))
        self.button5.bind("<ButtonPress>", self.backward)
        self.button5.bind("<ButtonRelease>", self.stop)

        self.button6 = Button(self, text="Backward Left", width=15, highlightbackground="#00629B")
        self.button6.grid(row = 2, column = 0, padx=(10, 0), pady=(10, 0))
        self.button6.bind("<ButtonPress>", self.backwardLeft)
        self.button6.bind("<ButtonRelease>", self.stop)

        self.button7 = Button(self, text="Left", width=15, highlightbackground="#00629B")
        self.button7.grid(row = 1, column = 0, padx=(10, 0), pady=(10, 0))
        self.button7.bind("<ButtonPress>", self.left)
        self.button7.bind("<ButtonRelease>", self.stop)

        self.button8 = Button(self, text="Forward Left", width=15, highlightbackground="#00629B")
        self.button8.grid(row = 0, column = 0, padx=(10, 0), pady=(10, 0))
        self.button8.bind("<ButtonPress>", self.forwardLeft)
        self.button8.bind("<ButtonRelease>", self.stop)

        self.separator0 = ttk.Separator(self, orient="horizontal")
        self.separator0.grid(row = 3, column = 0)

        self.button9 = Button(self, text="Clockwise", width=15, highlightbackground="#00629B")
        self.button9.grid(row = 4, column = 0, padx=(10, 0), pady=(10, 0))
        self.button9.bind("<ButtonPress>", self.clockwise)
        self.button9.bind("<ButtonRelease>", self.stop)

        self.button10 = Button(self, text="Counter Clockwise", width=15, highlightbackground="#00629B")
        self.button10.grid(row = 4, column = 1, padx=(10, 0), pady=(10, 0))
        self.button10.bind("<ButtonPress>", self.counterClockwise)
        self.button10.bind("<ButtonRelease>", self.stop)

        self.entry0 = Entry(self, text="Speed", width=15, highlightbackground="#00629B")
        self.entry0.grid(row = 6, column = 0, padx=(10, 0), pady=(10, 0))

        self.button11 = Button(self, text="Speed", width=15, highlightbackground="#00629B")
        self.button11.grid(row = 6, column = 1, padx=(10, 0), pady=(10, 0))
        self.button11["command"] = self.speedInput

        self.text = Text(self, width=60, height=6)
        self.vsb = Scrollbar(self, command=self.text.yview)
        self.text.configure(yscrollcommand=self.vsb.set)
        #self.vsb.pack(side="right", fill="y")
        self.text.grid(row = 7, columnspan=3, padx=(10, 10), pady=(10, 10))




    def stop(self, event):
        # ser.write("0 0 1000")
        instruction.Instruction(0, self.speed,1000).execute()
        self.log("Stop")

    def forward(self, event):
        # ser.write("1 100 1000")
        instruction.Instruction(1, self.speed,1000).execute()
        self.log("Forward")

    def forwardRight(self, event):
        # ser.write("2 100 1000")
        instruction.Instruction(2, self.speed,1000).execute()
        self.log("Forward Right")

    def right(self, event):
        # ser.write("3 100 1000")
        instruction.Instruction(3, self.speed,1000).execute()
        self.log("Right")

    def backwardRight(self, event):
        # ser.write("4 100 1000")
        instruction.Instruction(4, self.speed,1000).execute()
        self.log("Backward Right")

    def backward(self, event):
        # ser.write("5 100 1000")
        instruction.Instruction(5, self.speed,1000).execute()
        self.log("Backward")

    def backwardLeft(self, event):
        # ser.write("6 100 1000")
        instruction.Instruction(6, self.speed,1000).execute()
        self.log("Backward Left")

    def left(self, event):
        # ser.write("7 100 1000")
        instruction.Instruction(7, self.speed,1000).execute()
        self.log("Left")

    def forwardLeft(self, event):
        # ser.write("8 100 1000")
        instruction.Instruction(8, self.speed,1000).execute()
        self.log("Forward Left")

    def clockwise(self, event):
        # ser.write("9 100 1000")
        instruction.Instruction(9, self.speed,1000).execute()
        self.log("Clockwise")

    def counterClockwise(self, event):
        # ser.write("10 100 1000")
        instruction.Instruction(10,self.speed,1000).execute()
        self.log("Counter Clockwise")

    def speedInput(self):
        try:
            self.speed = int(self.entry0.get())
            if (self.speed > 100):
                self.speed = 100
            elif (self.speed < 0):
                self.speed = 0
            self.log("Speed: " + str(self.speed))
        except Exception as e:
            print(e.args)

    def log(self, message):
        now = time.strftime("%I:%M:%S", time.localtime())
        self.text.insert("end", now + " " + message.strip() + "\n")
        self.text.see("end") # autoscroll

if __name__ == "__main__":
    root = Tk()
    root.title("GT IEEE HWTeam 2018 Robot GUI")
    root.geometry("530x310")
    app = Application(root).pack(side="top", fill="both", expand=True)
    root.mainloop()
