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

import pygame
import sys
import time
import subprocess
import os

'''
This python script was created to visualize your work with the PUSH_SWAP
42 Project.
You must put this script in the same path or in a sibling path of your program
Of course you need Python3 with the Pygame Module.
You can install it with Brew.
--> Brew install python3
--> pip3 install pygame
Execute the script with : 
--> python3 pyvis.py `ruby -e "puts (-200..200).to_a.shuffle.join(' ')"` 
You can change the PUSHS_PATH to get to the relative path of your push_swap
You can decrease the speed by pressing repeatedly the LEFT KEY 
or increase by pressing repeatedly the RIGHT KEY
'''

SPEED_FACTOR = 3
RELATIVE_PATH = r'../pushswap/push_swap'


def display_piles(screen, w_width, w_height, pile_a, pile_b):
	v_i = 0
	h_width = w_width / 2
	hm = len(pile_a) + len(pile_b)
	mx = max(pile_a + pile_b)
	mn = min(pile_a + pile_b)
	if len(pile_a) > 0:
		a_val = [(num - mn) / (mx - mn) for num in pile_a]
		for vala in a_val:
			pygame.draw.rect(screen, (0, 128, 180),
							 pygame.Rect(0, v_i, 10 + vala * (h_width - 100),
										 w_height / hm + 1))
			v_i += w_height / hm
	v_i = 0
	if len(pile_b) > 0:
		b_val = [(num - mn) / (mx - mn) for num in pile_b]
		for valb in b_val:
			pygame.draw.rect(screen, (180, 128, 128),
				pygame.Rect(h_width - 80, v_i, 10 + valb * (h_width - 100),
					w_height / hm + 1))
			v_i += w_height / hm


def launch_cmds(pile_a, pile_b, cmd):
	if cmd == b'sa' and len(pile_a) >= 2:
		pile_a[0], pile_a[1] = pile_a[1], pile_a[0]
	if cmd == b'sb' and len(pile_b) >= 2:
		pile_b[0], pile_b[1] = pile_b[1], pile_b[0]
	if cmd == b'ss' and len(pile_a) >= 2 and len(pile_b) >= 2:
		pile_a[0], pile_a[1] = pile_a[1], pile_a[0]
		pile_b[0], pile_b[1] = pile_b[1], pile_b[0]
	if cmd == b'ra' and len(pile_a) >= 2:
		pile_a.append(pile_a[0])
		del pile_a[0]
	if cmd == b'rb' and len(pile_b) >= 2:
		pile_b.append(pile_b[0])
		del pile_b[0]
	if cmd == b'rr' and len(pile_a) >= 2 and len(pile_b) >= 2:
		pile_a.append(pile_a[0])
		del pile_a[0]
		pile_b.append(pile_b[0])
		del pile_b[0]
	if cmd == b'rra' and len(pile_a) >= 2:
		pile_a = [pile_a[-1]] + pile_a
		del pile_a[-1]
	if cmd == b'rrb' and len(pile_b) >= 2:
		pile_b = [pile_b[-1]] + pile_b
		del pile_b[-1]
	if cmd == b'rrr' and len(pile_a) >= 2 and len(pile_b) >= 2:
		pile_a = [pile_a[-1]] + pile_a
		del pile_a[-1]
		pile_b = [pile_b[-1]] + pile_b
		del pile_b[-1]
	if cmd == b'pa' and len(pile_b) >= 1:
		pile_a = [pile_b[0]] + pile_a
		del pile_b[0]
	if cmd == b'pb' and len(pile_a) >= 1:
		pile_b = [pile_a[0]] + pile_b
		del pile_a[0]
	return pile_a, pile_b


def change_speed(SPEED_FACTOR):
	key = pygame.key.get_pressed()
	if key[pygame.K_LEFT]:
		print("LEFT IS PRESSED")
		return SPEED_FACTOR + 1
	if key[pygame.K_RIGHT]:
		print("RIGHT IS PRESSED")
		return SPEED_FACTOR - 1
	return SPEED_FACTOR


def main(SPEED_FACTOR):
	dirname = os.path.dirname(os.path.abspath(__file__))
	PUSHS_PATH = os.path.join(dirname, RELATIVE_PATH)
	pygame.init()
	pygame.display.set_caption('Push_swap viewer')
	w_width = 800
	w_height = 600
	screen = pygame.display.set_mode((w_width, w_height))
	values = [int(num) for num in sys.argv[1:]]
	b_values = []
	cp = subprocess.run([PUSHS_PATH] + sys.argv[1:], stdout=subprocess.PIPE)
	cmds = cp.stdout.splitlines()
	myfont = pygame.font.SysFont("monospace", 20)
	op = 0
	done = False
	while not done:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				done = True
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_RIGHT:
					if SPEED_FACTOR > 4:
						SPEED_FACTOR = SPEED_FACTOR - 4
				elif event.key == pygame.K_LEFT:
					SPEED_FACTOR = SPEED_FACTOR + 4
		screen.fill((0, 0, 0))
		display_piles(screen, w_width, w_height, values, b_values)
		if op < len(cmds):
			pygame.draw.rect(screen, (20, 20, 20),
				pygame.Rect(650, 0, 200, 800))
			label = myfont.render(cmds[op], 1, (255, 255, 0))
			tot = myfont.render('total : ' + str(len(cmds)), 1, (255, 255, 0))
			screen.blit(label, (710, 20))
			screen.blit(tot, (690, 40))
			values, b_values = launch_cmds(values, b_values, cmds[op])
			op += 1
			time.sleep(SPEED_FACTOR / len(cmds))
		elif not all(
				values[i] <= values[i + 1] for i in range(len(values) - 1)):
			pygame.draw.rect(screen, (20, 20, 20),
							 pygame.Rect(650, 0, 200, 800))
			res = myfont.render('Game Over', 1, (255, 255, 0))
			screen.blit(res, (700, 60))
		pygame.display.flip()
	pygame.quit()
	sys.exit()


if __name__ == "__main__":
	main(SPEED_FACTOR)