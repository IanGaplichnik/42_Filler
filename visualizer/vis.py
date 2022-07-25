from curses.ascii import isalpha, isdigit
import pygame
import sys
import subprocess
import time

#initialization
pygame.init()

#create screen
screen = pygame.display.set_mode((1920 / 2, 1280 / 2))
#set header of the screen
pygame.display.set_caption("42_Filler")

clock = pygame.time.Clock()




def parse_player_num():
	text_out = pygame.font.Font("press-start/prstart.ttf", 8)
	game_out = pygame.font.Font("press-start/prstart.ttf", 30)

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

	text_surface = game_out.render("FIL", True, 'cyan2')
	screen.blit(text_surface, (50, 25))
	text_surface = game_out.render("LER", True, 'coral')
	screen.blit(text_surface, (140, 25))

	text_surface = text_out.render("Player 1:", True, 'white')
	screen.blit(text_surface, (1200 / 2, 200 / 2))

	text_surface = text_out.render(p1, True, 'cyan2')
	screen.blit(text_surface, (1200 / 2, 230 / 2))

	text_surface = text_out.render("Last received piece:", True, 'white')
	screen.blit(text_surface, (1200 / 2, 300 / 2))

	text_surface = text_out.render("Player 2:", True, 'white')
	screen.blit(text_surface, (1200 / 2, 600 / 2))

	text_surface = text_out.render(p2, True, 'coral')
	screen.blit(text_surface, (1200 / 2, 630 / 2))

	text_surface = text_out.render("Last received piece:", True, 'white')
	screen.blit(text_surface, (1200 / 2, 700 / 2))
	return (p1, p2)

def parse_map(rows, columns):
	x = 0;
	y = 0;
	p1 = 0;
	p2 = 0;
	x_coord = 50;
	y_coord = 100;
	if (rows < columns):
		divider = int(columns)
	else:
		divider = int(rows)


	p1_old = pygame.Surface(((450 / divider) - 2, (450 / divider) - 2))
	p1_old.fill('cyan4')
	p1_new = pygame.Surface(((450 / divider) - 2, (450 / divider) - 2))
	p1_new.fill('cyan2')
	p2_old = pygame.Surface(((450 / divider) - 2, (450 / divider) - 2))
	p2_old.fill('coral4')
	p2_new = pygame.Surface(((450 / divider) - 2, (450 / divider) - 2))
	p2_new.fill('coral')
	empty = pygame.Surface(((450 / divider) - 2, (450 / divider) - 2))
	empty.fill('gray19')
	text_out = pygame.font.Font("press-start/prstart.ttf", 8)

	clear = pygame.Surface((450, 50))
	clear.fill('black')
	screen.blit(clear, (50,65))
	str = sys.stdin.readline()
	# print(str)
	while (y < int(rows)):
		str = sys.stdin.readline()
		# print(str)
		while (isdigit(str[x]) or str[x] == ' '):
			x += 1
		while (x < (int(columns) + 4)):
			if str[x] == '.':
				screen.blit(empty, (x_coord, y_coord))
			if str[x] == 'O':
				screen.blit(p1_old, (x_coord, y_coord))
				p1 += 1
			if str[x] == 'o':
				screen.blit(p1_new, (x_coord, y_coord))
				p1 += 1
			if str[x] == 'x':
				screen.blit(p2_new, (x_coord, y_coord))
				p2 += 1
			if str[x] == 'X':
				screen.blit(p2_old, (x_coord, y_coord))
				p2 += 1
			x += 1
			x_coord += (450 / divider)
		x = 0
		x_coord = 50
		y += 1
		y_coord += (450 / divider)
	p1s = f'{p1}'
	p2s = f'{p2}'
	text_surface = text_out.render(p1s, True, 'cyan2')
	screen.blit(text_surface, (50, 75))
	text_surface = text_out.render(p2s , True, 'coral')
	screen.blit(text_surface, (145, 75))


def parse_piece(p_rows, p_columns, first_player):
	x = 0;
	y = 0;

	if (p_rows < p_columns):
		divider = int(p_columns)
	else:
		divider = int(p_rows)
	side = 100 / divider
	x_coord = 600
	p1_new = pygame.Surface((side - 2, side - 2))
	p1_new.fill('cyan2')
	p2_new = pygame.Surface((side - 2, side - 2))
	p2_new.fill('coral')
	empty = pygame.Surface((side - 2, side - 2))
	empty.fill('gray19')
	clear_p1 = pygame.Surface((360, 100))
	clear_p1.fill('black')
	if (first_player % 2 == 1):
		piece = p1_new
		y_coord = 175
	else:
		piece = p2_new
		y_coord = 375

	screen.blit(clear_p1, (x_coord, y_coord))
	while (y < int(p_rows)):
		str = sys.stdin.readline()
		# print(str)
		while (x < int(p_columns)):
			if (str[x] == '*'):
				screen.blit(piece, (x_coord, y_coord))
			if (str[x] == '.'):
				screen.blit(empty, (x_coord, y_coord))
			x += 1
			x_coord += side
		x_coord = 600
		x = 0
		y_coord += side
		y += 1

def pause():
	text_out = pygame.font.Font("press-start/prstart.ttf", 15)
	text_surface = text_out.render("PAUSE", True, 'white')
	empty = pygame.Surface((200, 200))
	empty.fill('black')

	screen.blit(text_surface, (240, 300))
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
					screen.blit(empty, (200, 200))
			if event.type == pygame.QUIT:
				pygame.quit()
				exit()

def pause_finish(o_score, x_score, p1, p2):
	paused = True
	text_out = pygame.font.Font("press-start/prstart.ttf", 13)
	if o_score > x_score:
		text_surface = text_out.render(p1 + " wins", True, 'white')
	if x_score > o_score:
		text_surface = text_out.render(p2 + " wins", True, 'white')
	if x_score == o_score:
		text_surface = text_out.render("Draw", True, 'white')
	screen.blit(text_surface, (150, 300))
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
str = sys.stdin.readline().rstrip(':\n').split(' ')
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
	if 'fin' in str[2]:
		o_score = int(str[3])
		str = sys.stdin.readline().rstrip(':\n').split(' ')
		x_score = int(str[3])
		pause_finish(o_score, x_score, p1, p2)
	rows = int(str[1])
	columns = int(str[2])
	parse_map(rows, columns)
	str = sys.stdin.readline().rstrip(':\n').split(' ')
	while 'Piece' in str[0]:
		p_rows = int(str[1])
		p_columns = int(str[2])
		parse_piece(p_rows, p_columns, first_player)
		str = sys.stdin.readline().rstrip(':\n').split(' ')
		if str[1] != old_symb:
			first_player += 1
			old_symb = str[1]
		else:
			if 'X' in old_symb:
				first_player = 0
			if 'O' in old_symb:
				first_player = 1
		str = sys.stdin.readline().rstrip(':\n').split(' ')
	pygame.display.update()
	pygame.time.delay(int(set_delay))
