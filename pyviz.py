#!/usr/bin/env python3


from tkinter import *
import sys
import time
import subprocess
import os
from math import sqrt


"""
__project__ = "push_swap visualizer"
__author__ = "Emmanuel Ruaud"
__email__ = "eruaud@student.le-101.fr"
This python script was created to visualize your work with the PUSH_SWAP
42 Project.
You must put this script in the same path or in a sibling path of your program
Of course you need Python3 with the builtin Tkinter.
You can install it with Brew.
--> Brew install python3
Execute the script with :
--> python3 pyviz.py `ruby -e "puts (-200..200).to_a.shuffle.join(' ')"`
You can change the PUSHS_PATH to get to the relative path of your push_swap
You can decrease or increase the speed with the matching buttons.
"""


RELATIVE_PATH = r'push_swap'


class PsGui:
    def __init__(self, master):
        ww = 600
        wh = 600
        self.i = 0
        self.speed = 0
        dirname = os.path.dirname(os.path.abspath(__file__))
        PUSHS_PATH = os.path.join(dirname, RELATIVE_PATH)
        self.pile_a = [int(num) for num in sys.argv[1:]]
        self.first_pile = self.pile_a[:]
        self.pile_b = []
        self.cmds = subprocess.check_output([PUSHS_PATH] + sys.argv[1:], stderr=subprocess.STDOUT,
                                            timeout=12).splitlines()
        self.prespeed = 1 / len(self.pile_a)
        self.master = master
        master.title("Push_swap viewer")
        self.mainframe = Frame(master)
        self.mainframe.pack(fill=BOTH)
        self.can = Canvas(self.mainframe, width=ww, height=wh, bg="black")
        self.can.pack(side=LEFT)
        self.toolframe = Frame(self.mainframe)
        self.toolframe.pack(side=RIGHT, fill=BOTH)
        self.butframe = Frame(self.toolframe)
        self.butframe.pack(side=TOP, fill=Y)
        self.PrevCtl = Button(self.butframe, text="<<", command=self.speed_down)
        self.PrevCtl.pack(side=LEFT)
        self.PauseCtl = Button(self.butframe, text=">", command=self.pause)
        self.PauseCtl.pack(side=LEFT)
        self.NextCtl = Button(self.butframe, text=">>", command=self.speed_up)
        self.NextCtl.pack(side=LEFT)
        self.ResetCtl = Button(self.butframe, text="R", command=self.reset)
        self.ResetCtl.pack(side=LEFT)
        self.listbox = Listbox(self.toolframe, bg='black', fg='light cyan',
                               font=("monospace", 12), relief=FLAT)
        self.listbox.pack(fill=BOTH, expand=1)
        for cmd in self.cmds:
            self.listbox.insert(END, cmd)
        self.statusframe = Frame(master)
        self.statusframe.pack(side=BOTTOM, fill=X)
        self.speedmeter = Label(self.statusframe,
                                text='frame rate = ' + str(self.speed),
                                font=("monospace", 10))
        self.speedmeter.pack(side=LEFT)
        self.totalcount = Label(self.statusframe,
                                text='- operations = ' + str(len(self.cmds)),
                                font=("monospace", 10))
        self.totalcount.pack(side=LEFT)
        self.draw_rectangles()
        self.launch()

    def reset(self):
        self.speed = 0
        self.i = 0
        del self.pile_a[:]
        self.pile_a = self.first_pile[:]
        del self.pile_b[:]
        self.can.delete("all")
        self.draw_rectangles()
        self.listbox.see(0)
        self.PauseCtl.config(text='>')
        self.launch()

    def pause(self):
        if self.speed != 0:
            self.prespeed = self.speed
            self.speed = 0
            self.speedmeter.config(text='frame rate = 0')
            self.PauseCtl.config(text='>')
        else:
            self.speed = self.prespeed
            self.speedmeter.config(text='frame rate = ' \
                                        + '{:.2e}'.format(self.speed))
            self.PauseCtl.config(text='||')

    def speed_up(self):
        if self.speed == 0:
            self.PauseCtl.config(text='||')
            self.speed = self.prespeed
        self.speed = self.speed ** 2
        self.speedmeter.config(text='frame rate = ' \
                                    + '{:.2e}'.format(self.speed))

    def speed_down(self):
        self.speed = sqrt(self.speed)
        self.speedmeter.config(text='frame rate = ' \
                                    + '{:.2e}'.format(self.speed))

    def launch_cmds(self, cmd):
        if cmd == b'sa' and len(self.pile_a) >= 2:
            self.pile_a[0], self.pile_a[1] = self.pile_a[1], self.pile_a[0]
        if cmd == b'sb' and len(self.pile_b) >= 2:
            self.pile_b[0], self.pile_b[1] = self.pile_b[1], self.pile_b[0]
        if cmd == b'ss':
            if (len(self.pile_a) >= 2):
                self.pile_a[0], self.pile_a[1] = self.pile_a[1], self.pile_a[0]
            if (len(self.pile_b) >= 2):
                self.pile_b[0], self.pile_b[1] = self.pile_b[1], self.pile_b[0]
        if cmd == b'ra' and len(self.pile_a) >= 2:
            self.pile_a.append(self.pile_a[0])
            del self.pile_a[0]
        if cmd == b'rb' and len(self.pile_b) >= 2:
            self.pile_b.append(self.pile_b[0])
            del self.pile_b[0]
        if cmd == b'rr':
            if (len(self.pile_a) >= 2):
                self.pile_a.append(self.pile_a[0])
                del self.pile_a[0]
            if (len(self.pile_b) >= 2):
                self.pile_b.append(self.pile_b[0])
                del self.pile_b[0]
        if cmd == b'rra' and len(self.pile_a) >= 2:
            self.pile_a = [self.pile_a[-1]] + self.pile_a
            del self.pile_a[-1]
        if cmd == b'rrb' and len(self.pile_b) >= 2:
            self.pile_b = [self.pile_b[-1]] + self.pile_b
            del self.pile_b[-1]
        if cmd == b'rrr':
            if (len(self.pile_a) >= 2):
                self.pile_a = [self.pile_a[-1]] + self.pile_a
                del self.pile_a[-1]
            if (len(self.pile_b) >= 2):
                self.pile_b = [self.pile_b[-1]] + self.pile_b
                del self.pile_b[-1]
        if cmd == b'pa' and len(self.pile_b) >= 1:
            self.pile_a = [self.pile_b[0]] + self.pile_a
            del self.pile_b[0]
        if cmd == b'pb' and len(self.pile_a) >= 1:
            self.pile_b = [self.pile_a[0]] + self.pile_b
            del self.pile_a[0]
        return self.pile_a, self.pile_b

    def set_color(self, index):
        col = '#%02x%02x%02x' % (int(255 * (index - 0.3) * (index > 0.3)),
                                 int(255 * index
                                     - ((510 * (index - 0.6)) * (index > 0.6))),
                                 int((255 - 510 * index) * (index < 0.5)))
        return col

    def draw_rectangles(self):
        vi = 0
        ww = 600
        wh = 600
        hw = ww / 2
        hm = len(self.pile_a) + len(self.pile_b)
        mx = max(self.pile_a + self.pile_b)
        mn = min(self.pile_a + self.pile_b)
        rects = []
        if len(self.pile_a) > 0:
            a_val = [(num - mn) / (mx - mn) for num in self.pile_a]
            for vala in a_val:
                rects.append(self.can.create_rectangle(0, vi,
                                                       10 + vala * (hw - 100), vi + wh / hm,
                                                       fill=self.set_color(vala), outline=""))
                vi += wh / hm
        vi = 0
        if len(self.pile_b) > 0:
            b_val = [(num - mn) / (mx - mn) for num in self.pile_b]
            for valb in b_val:
                rects.append(self.can.create_rectangle(hw, vi,
                                                       hw + 10 + valb * (hw - 100), vi + wh / hm,
                                                       fill=self.set_color(valb), outline=""))
                vi += wh / hm

    def launch(self):
        while self.i < len(self.cmds):
            if self.speed != 0:
                while self.i < len(self.cmds):
                    self.listbox.activate(self.i)
                    self.can.delete("all")
                    self.pile_a, self.pile_b = \
                        self.launch_cmds(self.cmds[self.i])
                    self.draw_rectangles()
                    time.sleep(2 * self.speed)
                    self.can.update()
                    self.listbox.yview_scroll(1, 'units')
                    self.i += 1
                    if self.speed == 0:
                        break
            time.sleep(0.25)
            self.can.update()
        self.PauseCtl.config(text='>')


root = Tk()
root.resizable(width=False, height=False)
gui = PsGui(root)
root.mainloop()
