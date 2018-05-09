from tkinter import *


TITLE = "Window Monkey Simulator"
SIZE = "400x300"


class Window(Frame):

    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master = master
        self.init_window()

    def init_window(self):
        self.master.title(TITLE)

        self.pack(fill=BOTH, expand=1)

        menu = Menu(self.master)
        self.master.config(menu=menu)

        file = Menu(menu)

        file.add_command(label="Exit", command=self.client_exit)

        menu.add_cascade(label="File", menu=file)

        edit = Menu(menu)

        edit.add_command(label="Undo")

        menu.add_cascade(label="Edit", menu=edit)

    def client_exit(self):
        exit()


root = Tk()

root.geometry(SIZE)
app = Window(root)
root.mainloop()
