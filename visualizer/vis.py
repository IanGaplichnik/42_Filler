from curses.ascii import isalpha, isdigit
import pygame
import sys
import subprocess
import time

pygame.init()

res_div = 1 #MODIFY TO CHANGE RESOLUTION

screen = pygame.display.set_mode((1790 / res_div, 1000 / res_div))
screen_color = (18, 18, 20)
screen.fill(screen_color)
pygame.display.set_caption("42_Filler")

clock = pygame.time.Clock()
game_font = "visualizer/press-start/prstart.ttf"
# p1_old_color = 0x9b5de5
# p1_new_color = 0xf15bb5
# p2_old_color = 0x00bbf9
# p2_new_color = 0x00f5d4

p1_old_color = 0x2a9d8f
p1_new_color = 0xe63946
p2_old_color = 0x8338ec
p2_new_color = 0xffe66d

p1_text = p1_old_color << 8
p2_text = p2_old_color << 8

def print_interface(p1, p2):
	text_out = pygame.font.Font(game_font, int(16 / res_div))
	game_out = pygame.font.Font(game_font, int(60 / res_div))

	text_surface = game_out.render("FIL", True, p1_text)
	screen.blit(text_surface, (130 / res_div, 50 / res_div))
	text_surface = game_out.render("LER", True, p2_text)
	screen.blit(text_surface, (310 / res_div, 50 / res_div))

	text_surface = text_out.render("Controls:", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 50 / res_div))

	text_surface = text_out.render("Arrow Up/Down: Speed Up/Down", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 80 / res_div))

	text_surface = text_out.render("Space: Pause", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 110 / res_div))

	text_surface = text_out.render("Player 1:", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 200 / res_div))

	text_surface = text_out.render(p1, True, p1_text)
	screen.blit(text_surface, (1100 / res_div, 225 / res_div))

	text_surface = text_out.render("Last received piece:", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 250 / res_div))

	text_surface = text_out.render("Player 2:", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 600 / res_div))

	text_surface = text_out.render(p2, True, p2_text)
	screen.blit(text_surface, (1100 / res_div, 625 / res_div))

	text_surface = text_out.render("Last received piece:", True, 'white')
	screen.blit(text_surface, (1100 / res_div, 650 / res_div))

def parse_player_num():
	for _ in range(5):
		sys.stdin.readline()
	str = sys.stdin.readline()
	splitted = str.split("/")
	p1 = splitted[-1]
	p1 = p1.replace("\n","")
	str = sys.stdin.readline()
	str = sys.stdin.readline()
	splitted = str.split("/")
	p2 = splitted[-1]
	p2 = p2.replace("\n","")
	str = sys.stdin.readline()
	print_interface(p1, p2)
	return (p1, p2)

def print_score(moves_p1, moves_p2):
	text_out = pygame.font.Font(game_font, int(16 / res_div))
	text_surface = text_out.render(f'{moves_p1}', True, p1_text)
	screen.blit(text_surface, (130 / res_div, 130 / res_div))
	text_surface = text_out.render(f'{moves_p2}', True, p2_text)
	screen.blit(text_surface, (320 / res_div, 130 / res_div))

def parse_map(rows, columns, moves_p1, moves_p2):
	x = 0;
	y = 0;
	x_coord = 130 / res_div;
	y_coord = 200 / res_div;
	moves_p1_str = f'{moves_p1}'
	moves_p2_str = f'{moves_p2}'

	clear = pygame.Surface((900 / res_div, 100 / res_div))
	clear.fill(screen_color)
	screen.blit(clear, (100 / res_div, 130 / res_div))

	flag_p1 = 0
	flag_p2 = 0
	str = sys.stdin.readline()
	while (y < int(rows)):
		str = sys.stdin.readline()
		while (isdigit(str[x]) or str[x] == ' '):
			x += 1
		while (x < (int(columns) + 4)):
			if str[x] == '.':
				screen.blit(empty, (x_coord, y_coord))
			if str[x] == 'O':
				screen.blit(p1_old, (x_coord, y_coord))
			if str[x] == 'o':
				screen.blit(p1_new, (x_coord, y_coord))
				flag_p1 = 1
			if str[x] == 'x':
				screen.blit(p2_new, (x_coord, y_coord))
				flag_p2 = 1
			if str[x] == 'X':
				screen.blit(p2_old, (x_coord, y_coord))
			x += 1
			x_coord += square_side + 1
		x = 0
		x_coord = 130 / res_div
		y += 1
		y_coord += square_side + 1
	if flag_p1 == 1:
		moves_p1 += 1
	if flag_p2 == 1:
		moves_p2 += 1
	flag_p1 = 0
	flag_p2 = 0
	print_score(moves_p1, moves_p2)
	return (moves_p1, moves_p2)

def parse_piece(p_rows, p_columns, first_player):
	x = 0;
	y = 0;

	if (p_rows < p_columns):
		divider_p = int(p_columns)
	else:
		divider_p = int(p_rows)
	side = 200 / res_div / divider_p
	x_coord = 1100 / res_div
	p1_new = pygame.Surface((side - 2, side - 2))
	p1_new.fill(p1_new_color)
	p2_new = pygame.Surface((side - 2, side - 2))
	p2_new.fill(p2_new_color)
	empty = pygame.Surface((side - 2, side - 2))
	empty.fill('gray19')
	clear_p1 = pygame.Surface((720 / res_div, 200 / res_div))
	clear_p1.fill(screen_color)
	text_out = pygame.font.Font(game_font, 15)
	if (first_player % 2 == 1):
		piece = p1_new
		y_coord = 300 / res_div
		screen.blit(clear_p1, (x_coord, y_coord))
	else:
		piece = p2_new
		y_coord = 700 / res_div
		screen.blit(clear_p1, (x_coord, y_coord))
	while (y < int(p_rows)):
		string = sys.stdin.readline()
		while (x < int(p_columns)):
			if (string[x] == '*'):
				screen.blit(piece, (x_coord, y_coord))
			if (string[x] == '.'):
				screen.blit(empty, (x_coord, y_coord))
			x += 1
			x_coord += side
		x_coord = 1100 / res_div
		x = 0
		y_coord += side
		y += 1

def pause():
	text_out = pygame.font.Font(game_font, int(15 / res_div))
	text_surface = text_out.render("PAUSE", True, 'white')
	empty = pygame.Surface((400 / res_div, 930 / res_div))
	empty.fill(screen_color)

	screen.blit(text_surface, (450 / res_div, 930 / res_div))
	pygame.display.update()
	paused = True
	while paused:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					pygame.quit()
					exit()
				if event.key == pygame.K_SPACE:
					paused = False
					screen.blit(empty, (450 / res_div, 930 / res_div))
					pygame.display.update()
			if event.type == pygame.QUIT:
				pygame.quit()
				exit()

def pause_finish(o_score, x_score, p1, p2):
	paused = True
	text_out = pygame.font.Font(game_font, int(26 / res_div))
	if o_score > x_score:
		text_surface = text_out.render(p1 + " wins", True, p1_text)
	if x_score > o_score:
		text_surface = text_out.render(p2 + " wins", True, p2_text)
	if x_score == o_score:
		text_surface = text_out.render("Draw", True, 'white')
	screen.blit(text_surface, (130 / res_div, 925 / res_div))
	pygame.display.update()

	while paused:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					pygame.quit()
					exit()
			if event.type == pygame.QUIT:
				pygame.quit()
				exit()

set_delay = 500
running = True
first_player = 1
p1, p2 = parse_player_num();
old_symb = " (X):"
moves_p1 = 0;
moves_p2 = 0;
read_str = sys.stdin.readline().rstrip(':\n').split(' ')
rows = int(read_str[1])
columns = int(read_str[2])

if (rows < columns):
	divider = int(columns)
else:
	divider = int(rows)
square_side = 700 / res_div / divider - 1
p1_old = pygame.Surface((square_side, square_side))
p1_old.fill(p1_old_color)
p1_new = pygame.Surface((square_side, square_side))
p1_new.fill(p1_new_color)
p2_old = pygame.Surface((square_side, square_side))
p2_old.fill(p2_old_color)
p2_new = pygame.Surface((square_side, square_side))
p2_new.fill(p2_new_color)
empty = pygame.Surface((square_side, square_side))
empty.fill('gray19')

while running:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
			exit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				pygame.quit()
				exit()
			if event.key == pygame.K_UP:
				set_delay /= 1.5;
			if event.key == pygame.K_DOWN:
				set_delay *= 1.5;
			if event.key == pygame.K_SPACE:
				pause()
	if 'fin' in read_str[2]:
		o_score = int(read_str[3])
		read_str = sys.stdin.readline().rstrip(':\n').split(' ')
		x_score = int(read_str[3])
		pause_finish(o_score, x_score, p1, p2)
	moves_p1, moves_p2 = parse_map(rows, columns, moves_p1, moves_p2)
	read_str = sys.stdin.readline().rstrip(':\n').split(' ')
	while 'Piece' in read_str[0]:
		p_rows = int(read_str[1])
		p_columns = int(read_str[2])
		parse_piece(p_rows, p_columns, first_player)
		read_str = sys.stdin.readline().rstrip(':\n').split(' ')
		if read_str[1] != old_symb:
			first_player += 1
			old_symb = read_str[1]
		else:
			if 'X' in old_symb:
				first_player = 0
			if 'O' in old_symb:
				first_player = 1
		read_str = sys.stdin.readline().rstrip(':\n').split(' ')
	pygame.display.update()
	pygame.time.delay(int(set_delay))
