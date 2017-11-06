import Tkinter as tk
import time

class Example(tk.Frame):
    def __init__(self, *args, **kwargs):
        tk.Frame.__init__(self, *args, **kwargs)
        self.button = tk.Button(self, text="Press me!")
        self.text = tk.Text(self, width=40, height=6)
        self.vsb = tk.Scrollbar(self, command=self.text.yview)
        self.text.configure(yscrollcommand=self.vsb.set)

        self.button.pack(side="top")
        self.vsb.pack(side="right", fill="y")
        self.text.pack(side="bottom", fill="x")

        self.button.bind("<ButtonPress>", self.on_press)
        self.button.bind("<ButtonRelease>", self.on_release)

    def on_press(self, event):
        self.log("button was pressed")

    def on_release(self, event):
        self.log("button was released")

    def log(self, message):
        now = time.strftime("%I:%M:%S", time.localtime())
        self.text.insert("end", now + " " + message.strip() + "\n")
        self.text.see("end")

if __name__ == "__main__":
    root = tk.Tk()
    Example(root).pack(side="top", fill="both", expand=True)
    root.mainloop()