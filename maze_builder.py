import pygame as pg
import sys
import math
import os
from enum import Enum
pg.init()


class Mode(Enum):
    EMPTY = 0
    WALL = 1
    POWER = 2
    NO_COIN = 3
modes = ["EMPTY", "Wall", "POWER", "NO_COIN"]
# Constants based on the pacman game
MAP_WIDTH = 28
MAP_HEIGHT = 27

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 220)
YELLOW = (255, 255, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

# Global
WIDTH, HEIGHT = 800, 600
PANEL_WIDTH = 130
PANEL_HEIGHT = 30
OPTIONS_WIDTH = 80 
FILE_LIST_HEIGHT = 30
DELETE_WIDTH = 15


# Set up the game window
screen = pg.display.set_mode((WIDTH, HEIGHT))
file_font = pg.font.Font("assets/Emulogic.ttf", 10)
pg.display.set_caption('Map editor')

# Set up the game clock
clock = pg.time.Clock()
running = True
isDifferent = False
mode = Mode.WALL

x_ratio = int(math.ceil(WIDTH - PANEL_WIDTH)/(MAP_WIDTH)) + 1
y_ratio = int(math.ceil(HEIGHT - PANEL_HEIGHT)/(MAP_HEIGHT)) 

pacman_matrix = [[0]*(MAP_WIDTH+1) for _ in range(MAP_HEIGHT+1)]
current_file = ""

def upload_map(fileName):
    file = open(fileName, 'r')
    content = file.read().split("\n")
    for i in range(MAP_HEIGHT):
        for j in range(MAP_WIDTH):
            pacman_matrix[j][i] = int(content[i][j])
    file.close()
def get_column(matrix, i):
    return [row[i] for row in matrix]
def pacmanMatrixToString():
    return [''.join(map(str, get_column(pacman_matrix, i)))+"\n" for i in range(MAP_HEIGHT)]
def save_map(fileName):
    with open(fileName, 'w') as file:
        file.writelines(pacmanMatrixToString())
def list_mazes(mazeListFile):
    file = open(mazeListFile, 'r')
    content = file.read().split("\n")
    content.pop()
    file.close()
    return content
def deleteFile(filePath, mazesList):
    mazesList.remove(filePath)
    with open("mazes/mazeList.txt", 'w') as file:
        file.writelines([el + "\n" for el in mazesList])
    try:
        os.remove("mazes/" + filePath)
    except FileNotFoundError : print(f"file {filePath} not found.")

list_files = list_mazes("mazes/mazeList.txt")
if (len(list_files) > 0):
    current_file = list_files[0]
    upload_map(fileName="mazes/" + list_files[0])
## Sorry for the cumsiness


isMouseDown = False
while running:
    # Handle events
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
        if event.type == pg.MOUSEBUTTONDOWN:
            isMouseDown = True
            pos = pg.mouse.get_pos();
            if (pos[1] < PANEL_HEIGHT):
                for i in range(len(modes)):
                    if (pos[0] < OPTIONS_WIDTH*(i+1)):
                        mode = Mode(i)
                        break;
                if (pos[0] > WIDTH-OPTIONS_WIDTH):
                    save_map(current_file)
            elif (pos[1] > PANEL_HEIGHT and pos[0] < PANEL_WIDTH):
                # file handling stuff
                for i in range(len(list_files)):
                    if (pos[1] < PANEL_HEIGHT + FILE_LIST_HEIGHT*(i+1)):
                        current_file = "mazes/" + list_files[i]
                        if (current_file == "mazes/"):
                            break
                        if (pos[0] > PANEL_WIDTH-DELETE_WIDTH):
                            deleteFile(list_files[i], list_files)
                        else:
                            upload_map(fileName=current_file)
                        isDifferent = True
                        break
                if (not isDifferent and pos[1] < PANEL_HEIGHT+10+((len(list_files)+1)*FILE_LIST_HEIGHT)):
                    list_files.append("maze" + str(len(list_files)+1) + ".map")
                    with open("mazes/mazeList.txt", 'a') as file:
                        file.write(list_files[-1] + "\n")
                    with open("mazes/" + list_files[-1],'w') as file:
                        file.writelines(pacmanMatrixToString())
        if event.type == pg.MOUSEBUTTONUP:
            isMouseDown = False
    pos = pg.mouse.get_pos()
    if isMouseDown and pos[1] > PANEL_HEIGHT and pos[0] > PANEL_WIDTH:
        pos = (pos[0]-PANEL_WIDTH, pos[1]-PANEL_HEIGHT)
        maze_pos = (int(pos[0]/x_ratio), int(pos[1]/y_ratio))
        pacman_matrix[maze_pos[0]][maze_pos[1]] = mode.value

    screen.fill(BLACK)
    for i in range(len(modes)):
        screen.blit(file_font.render(modes[i], 1, WHITE), (i*OPTIONS_WIDTH, 0))
        pg.draw.line(screen, WHITE, [(i+1)*OPTIONS_WIDTH-1, 0], [(i+1)*OPTIONS_WIDTH-1, PANEL_HEIGHT])
    screen.blit(file_font.render("Save", 1, RED), (WIDTH-OPTIONS_WIDTH, 0))
    pg.draw.line(screen, WHITE, [WIDTH-OPTIONS_WIDTH-1, 0],
                     [WIDTH-OPTIONS_WIDTH-1, PANEL_HEIGHT])
    screen.blit(file_font.render(current_file[6:], 1, GREEN), (WIDTH-(OPTIONS_WIDTH+10)*2, 0))
    pg.draw.line(screen, WHITE, [WIDTH-(OPTIONS_WIDTH+10)*2-1, 0],
                     [WIDTH-(OPTIONS_WIDTH+10)*2-1, PANEL_HEIGHT])

    y = 0
    for file_name in list_files:
        screen.blit(file_font.render(file_name, 1, YELLOW), (0, PANEL_HEIGHT+10+y*FILE_LIST_HEIGHT))
        screen.blit(file_font.render("X", 1, RED), (PANEL_WIDTH-DELETE_WIDTH, PANEL_HEIGHT+10+y*FILE_LIST_HEIGHT))
        y+=1
    screen.blit(file_font.render("New maze", 1, RED), (0, PANEL_HEIGHT+10+(len(list_files)*FILE_LIST_HEIGHT)))


    # Grid
    for i in range(PANEL_WIDTH, WIDTH, x_ratio):
        pg.draw.line(screen, WHITE, [i, PANEL_HEIGHT], [i, HEIGHT])
    for i in range(PANEL_HEIGHT, HEIGHT, y_ratio):
        pg.draw.line(screen, WHITE, [PANEL_WIDTH, i], [WIDTH, i])

    for i in range(MAP_HEIGHT+1):
        for j in range(MAP_WIDTH+1):
            if (pacman_matrix[i][j] == 0):
                pg.draw.circle(screen, YELLOW, [PANEL_WIDTH + (i+0.5)*x_ratio, PANEL_HEIGHT+(j+0.5)*y_ratio], x_ratio/10)
            if (pacman_matrix[i][j] == 1):
                pg.draw.rect(screen, BLUE, [PANEL_WIDTH + i*x_ratio, PANEL_HEIGHT+j*y_ratio+1, x_ratio, y_ratio])
            if (pacman_matrix[i][j] == 2):
                pg.draw.circle(screen, YELLOW, [PANEL_WIDTH + (i+0.5)*x_ratio, PANEL_HEIGHT+(j+0.5)*y_ratio], x_ratio/4)

    pg.draw.line(screen, WHITE, [0, PANEL_HEIGHT], [WIDTH, PANEL_HEIGHT])
    pg.draw.line(screen, WHITE, [PANEL_WIDTH, PANEL_HEIGHT], [PANEL_WIDTH, HEIGHT])

    pg.display.flip()

    clock.tick(60)

# Quit the game
pg.quit()
sys.exit()
