# **************************************************************************** #
#                                                          LE - /              #
#                                                              /               #
#   pyvis.py                                         .::    .:/ .      .::     #
#                                                 +:+:+   +:    +:  +:+:+      #
#   By: eruaud <eruaud@student.42.fr>              +:+   +:    +:    +:+       #
#                                                 #+#   #+    #+    #+#        #
#   Created: 2017/12/28 15:26:42 by eruaud       #+#   ##    ##    #+#         #
#   Updated: 2018/02/20 17:10:14 by eruaud      ###    #+. /#+    ###.fr     # #
#                                                         /                    #
#                                                        /                     #
# **************************************************************************** #

from tkinter import *
import sys
import time
import subprocess
import os

'''
This python script was created to visualize your work with the PUSH_SWAP
42 Project.
You must put this script in the same path or in a sibling path of your program
Of course you need Python3 with the builtin Tkinter.
You can install it with Brew.
--> Brew install python3
Execute the script with : 
--> python3 pyvis.py `ruby -e "puts (-200..200).to_a.shuffle.join(' ')"` 
You can change the PUSHS_PATH to get to the relative path of your push_swap
You can decrease the speed by pressing repeatedly the LEFT KEY 
or increase by pressing repeatedly the RIGHT KEY
'''

RELATIVE_PATH = r'push_swap'

class PsGui:
	def __init__(self, master):
		self.a_color = 'MediumOrchid4'
		self.b_color = 'dark slate blue'
		ww = 600
		wh = 600
		self.i = 0
		self.speed = 0
		dirname = os.path.dirname(os.path.abspath(__file__))
		PUSHS_PATH = os.path.join(dirname, RELATIVE_PATH)
		self.pile_a = [int(num) for num in sys.argv[1:]]
		self.first_pile = self.pile_a[:]
		self.pile_b = []
		cp = subprocess.run([PUSHS_PATH] + sys.argv[1:], stdout=subprocess.PIPE)
		self.cmds = cp.stdout.splitlines()
		self.prespeed = len(self.cmds) * 100
		self.master = master
		master.title("Push_swap viewer")
		self.can = Canvas(root, width=ww, height=wh, bg="black")
		self.can.pack(side=LEFT)
		self.toolframe = Frame(master)
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
		self.listbox = Listbox(self.toolframe, bg='black', fg='light cyan')
		self.listbox.pack(fill=BOTH, expand=1)
		for cmd in self.cmds:
			self.listbox.insert(END, cmd)
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
			self.PauseCtl.config(text='>')
		else:
			self.speed = self.prespeed
			self.PauseCtl.config(text='||')

	def speed_up(self):
		if self.speed == 0:
			self.PauseCtl.config(text='||')
			self.speed = self.prespeed
		self.speed *= 10

	def speed_down(self):
		if self.speed > 10:
			self.speed /= 10

	def launch_cmds(self, cmd):
		if cmd == b'sa' and len(self.pile_a) >= 2:
			self.pile_a[0], self.pile_a[1] = self.pile_a[1], self.pile_a[0]
		if cmd == b'sb' and len(self.pile_b) >= 2:
			self.pile_b[0], self.pile_b[1] = self.pile_b[1], self.pile_b[0]
		if cmd == b'ss' and len(self.pile_a) >= 2 and len(self.pile_b) >= 2:
			self.pile_a[0], self.pile_a[1] = self.pile_a[1], self.pile_a[0]
			self.pile_b[0], self.pile_b[1] = self.pile_b[1], self.pile_b[0]
		if cmd == b'ra' and len(self.pile_a) >= 2:
			self.pile_a.append(self.pile_a[0])
			del self.pile_a[0]
		if cmd == b'rb' and len(self.pile_b) >= 2:
			self.pile_b.append(self.pile_b[0])
			del self.pile_b[0]
		if cmd == b'rr' and len(self.pile_a) >= 2 and len(self.pile_b) >= 2:
			self.pile_a.append(self.pile_a[0])
			del self.pile_a[0]
			self.pile_b.append(self.pile_b[0])
			del self.pile_b[0]
		if cmd == b'rra' and len(self.pile_a) >= 2:
			self.pile_a = [self.pile_a[-1]] + self.pile_a
			del self.pile_a[-1]
		if cmd == b'rrb' and len(self.pile_b) >= 2:
			self.pile_b = [self.pile_b[-1]] + self.pile_b
			del self.pile_b[-1]
		if cmd == b'rrr' and len(self.pile_a) >= 2 and len(self.pile_b) >= 2:
			self.pile_a = [self.pile_a[-1]] + self.pile_a
			del self.pile_a[-1]
			self.pile_b = [self.pile_b[-1]] + self.pile_b
			del self.pile_b[-1]
		if cmd == b'pa' and len(self.pile_b) >= 1:
			self.pile_a = [self.pile_b[0]] + self.pile_a
			del self.pile_b[0]
		if cmd == b'pb' and len(self.pile_a) >= 1:
			self.pile_b = [self.pile_a[0]] + self.pile_b
			del self.pile_a[0]
		return self.pile_a, self.pile_b

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
							fill=self.a_color, outline=""))
				vi += wh / hm
		vi = 0
		if len(self.pile_b) > 0:
			b_val = [(num - mn) / (mx - mn) for num in self.pile_b]
			for valb in b_val:
				rects.append(self.can.create_rectangle(hw, vi,
					hw + 10 + valb * (hw - 100), vi + wh / hm,
							fill=self.b_color, outline=""))
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
					time.sleep(0.25 / self.speed)
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
