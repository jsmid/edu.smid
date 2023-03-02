from Queue import LifoQueue
from Queue import PriorityQueue
import math
import random

import pygame


WIDTH   = 800
WIN     = pygame.display.set_mode(size=(WIDTH, WIDTH))
pygame.display.set_caption("A* Path Finding Algorithm")

class Node (object):

    CLOSED_RGB  = (220, 32, 32)
    OPENED_RGB  = (64, 200, 64)
    RESET_RGB   = (255, 255, 255)
    WALL_RGB    = (0, 0, 0)
    START_RGB   = (224, 128, 32)
    END_RGB     = (64, 160, 160)
    PATH_RGB    = (160, 255, 255)
    LINE_RGB    = (192, 192, 192)

    def __init__ (self, row, col, width, total_rows, status = RESET_RGB):
        self.row        = row
        self.col        = col
        self.x          = row*width
        self.y          = col*width
        self.color      = status
        self.neighbors  = []
        self.width      = width
        self.total_rows = total_rows
        self.total_cols = total_rows

    @classmethod
    def h(cls, p1, p2):
        ''' Our predicted distance from p1 to p2

        @param p1: current node
        @param p2: end node
        '''
        x1, y1 = p1
        x2, y2 = p2

        return math.sqrt((x1-x2)**2 + (y1-y2)**2)
    #end def h

    @classmethod
    def reconstruct_path(cls, came_from, current, draw) :
        while current in came_from : # start is not in came_from
            current = came_from[current]
            current.make_path()
            draw()
    #end def reconstruct_path

    @classmethod
    def run(cls, draw, grid, start, end):
        count       = 0
        open_set    = PriorityQueue()
        # Items are sorted lowest score (first item in the tuple) first
        # In case we have two items with the same score in the queue,
        # count will help us out.
        open_set.put((0, count, start))
        came_from = {}
        # Initialize g_score and f_score
        g_score = {node: float("inf") for row in grid for node in row}
        g_score[start] = 0
        f_score = {node: float("inf") for row in grid for node in row}
        f_score[start] = Node.h(start.get_position(), end.get_position())

        # Keeps track about everything that's in the open_set
        open_set_hash = {start}

        # When open set is empty there's no solution
        while not open_set.empty() :
            for event in pygame.event.get():
                if event.type == pygame.QUIT :
                    pygame.quit()

            current = open_set.get()[2] # Gets the lowest score item
            open_set_hash.remove(current)

            if current == end :
                # We've found the shortest path!
                Node.reconstruct_path(came_from, end, draw)
                end.make_end()
                start.make_start()
                return True

            for neighbor in current.neighbors :
                neighbor_pos = neighbor.get_position()
                current_pos  = current.get_position()
                temp_g_score = g_score[current]+math.sqrt((neighbor_pos[0]-current_pos[0])**2 + (neighbor_pos[1]-current_pos[1])**2)
                if temp_g_score < g_score[neighbor] :
                    # this neighbor is better
                    came_from[neighbor] = current
                    g_score[neighbor] = temp_g_score
                    f_score[neighbor] = temp_g_score + Node.h(neighbor_pos, end.get_position())
                    if neighbor not in open_set_hash :
                        count += 1
                        open_set.put((f_score[neighbor], count, neighbor))
                        open_set_hash.add(neighbor)
                        neighbor.make_open()
            draw()

            if current != start :
                current.make_closed()

        return False
    #end def run

    @classmethod
    def make_grid(cls, rows, width, random_walls = 0.):
        grid = []
        gap  = width // rows
        for i in range(rows) :
            grid.append([])
            for j in range(rows) :
                status = Node.RESET_RGB
                if random.uniform(0, 1) < random_walls :
                    status = Node.WALL_RGB

                node = cls(i, j, gap, rows, status)
                grid[i].append(node)

        return grid
    #end def make_grid

    @classmethod
    def reset_grid(cls, grid):
        rows = len(grid)
        for i in range(rows) :
            for j in range(rows) :
                if not grid[i][j].is_wall :
                    grid[i][j].reset()

        return grid
    #end def reset_grid

    @classmethod
    def make_maze(cls, rows, width):
        ''' The method employs Jarnik's algorithm (1930), later appropriated by Prim (1957)
        and Dijkstra (1959).

        1. Start with a grid full of walls.
        2. Pick a cell, mark it as part of the maze. Add the walls of the cell to the wall list.
        3. While there are walls in the list:
            a. Pick a random wall from the list. If only one of the cells that the wall divides is visited, then:
                i.  Make the wall a passage and mark the unvisited cell as part of the maze.
                ii. Add the neighboring walls of the cell to the wall list.
            b. Remove the wall from the list.
        '''
        grid            = Node.make_grid(rows, width, 1.)
        row             = int(random.uniform(0, rows-1))
        col             = int(random.uniform(0, rows-1))

        start   = grid[row][col]
        start.reset()
        visited_hash = {(start.row, start.col)}
        walls   = PriorityQueue();
        inits   = start.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])
        for dir, node in inits.items() :
            walls.put((random.uniform(0, 1), node))

        while not walls.empty() :
            current     = walls.get()[1]
            neighbors_d = current.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])
            if len(neighbors_d.items()) > 0 :
                visited = [x for x in neighbors_d.items() if (x[1].row, x[1].col) in visited_hash]
                if len(visited) == 1 :
                    current.reset() # tear down the wall
                    cell = visited[0][1] # the cell that's on the opposite side of the wall
                    cell_dir = visited[0][0]
                    other    = None
                    if cell_dir == "UP" and "DOWN" in neighbors_d.keys() :
                        other = neighbors_d["DOWN"]
                    elif cell_dir == "DOWN" and "UP" in neighbors_d.keys() :
                        other = neighbors_d["UP"]
                    elif cell_dir == "LEFT" and "RIGHT" in neighbors_d.keys() :
                        other = neighbors_d["RIGHT"]
                    elif cell_dir == "RIGHT" and "LEFT" in neighbors_d.keys() :
                        other = neighbors_d["LEFT"]

                    if not other is None :
                        other.reset()
                        other_walls = other.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])

                        visited_hash.add((current.row, current.col))
                        visited_hash.add((other.row, other.col))

                        for dir, node in other_walls.items() :
                            if not (node.row, node.col) in visited_hash:
                                walls.put((random.uniform(0, 1), node))

        return grid
    #end def make_maze

    @classmethod
    def _draw_grid (cls, win, rows, width):
        gap = width // rows
        for i in range(rows):
            pygame.draw.line(win, Node.LINE_RGB, (0, i*gap), (width, i*gap))
            for j in range(rows):
                pygame.draw.line(win, Node.LINE_RGB, (j*gap, 0), (j*gap, width))
    #end def _draw_grid

    @classmethod
    def draw_nodes (cls, win, rows, grid, width):
        win.fill(Node.RESET_RGB)

        for row in grid :
            for node in row :
                node.draw(win)

        cls._draw_grid(win, rows, width)
        pygame.display.update()
    #end def draw_nodes

    def get_position (self):
        return self.row, self.col

    def draw (self, win):
        pygame.draw.rect(win, self.color, (self.x, self.y, self.width, self.width))
    #end def draw

    def get_neighbors(self, grid, dirs=["DOWN", "UP", "RIGHT", "LEFT", "DOWN_RIGHT", "DOWN_LEFT", "UP_RIGHT", "UP_LEFT"], visited = {}, dist=1):
        ret = {}
        if self.row < self.total_rows-dist \
            and "DOWN" in dirs \
            and not grid[self.row+dist][self.col] in visited: # DOWN
            ret["DOWN"] = grid[self.row+1][self.col]
        if self.row > dist-1 \
            and "UP" in dirs \
            and not grid[self.row-dist][self.col] in visited : # UP
            ret["UP"] = grid[self.row-dist][self.col]
        if self.col < self.total_cols-dist \
            and "RIGHT" in dirs \
            and not grid[self.row][self.col+dist] in visited : # RIGHT
            ret["RIGHT"] = grid[self.row][self.col+dist]
        if self.col > dist-1 \
            and "LEFT" in dirs \
            and not grid[self.row][self.col-dist] in visited : # LEFT
            ret["LEFT"] = grid[self.row][self.col-dist]
        if dist == 1 :
            if self.row < self.total_rows-1 and self.col < self.total_cols-1 \
                and "DOWN_RIGHT" in dirs \
                and not grid[self.row+1][self.col+1] in visited : # DOWN + RIGHT
                ret["DOWN_RIGHT"] = grid[self.row+1][self.col+1]
            if self.row < self.total_rows-1 and self.col > 0 \
                and "DOWN_LEFT" in dirs \
                and not grid[self.row+1][self.col-1] in visited : # DOWN + LEFT
                ret["DOWN_LEFT"] = grid[self.row+1][self.col-1]
            if self.row > 0 and self.col < self.total_cols-1 \
                and "UP_RIGHT" in dirs \
                and not grid[self.row-1][self.col+1] in visited : # UP + RIGHT
                ret["UP_RIGHT"] = grid[self.row-1][self.col+1]
            if self.row > 0 and self.col > 0 \
                and "UP_LEFT" in dirs \
                and not grid[self.row-1][self.col-1] in visited : # UP + LEFT
                ret["UP_LEFT"] = grid[self.row-1][self.col-1]

        return ret
    #end def get_neighbors

    def update_neighbors(self, grid, dirs=["DOWN", "UP", "RIGHT", "LEFT", "DOWN_RIGHT", "DOWN_LEFT", "UP_RIGHT", "UP_LEFT"]):
        self.neighbors = []
        if self.row < self.total_rows-1 \
            and "DOWN" in dirs \
            and not grid[self.row+1][self.col].is_wall : # DOWN
            self.neighbors.append(grid[self.row+1][self.col])
        if self.row > 0 \
            and "UP" in dirs \
            and not grid[self.row-1][self.col].is_wall : # UP
            self.neighbors.append(grid[self.row-1][self.col])
        if self.col < self.total_cols-1 \
            and "RIGHT" in dirs \
            and not grid[self.row][self.col+1].is_wall : # RIGHT
            self.neighbors.append(grid[self.row][self.col+1])
        if self.col > 0 \
            and "LEFT" in dirs \
            and not grid[self.row][self.col-1].is_wall : # LEFT
            self.neighbors.append(grid[self.row][self.col-1])
        if self.row < self.total_rows-1 and self.col < self.total_cols-1 \
            and "DOWN_RIGHT" in dirs \
            and not grid[self.row+1][self.col+1].is_wall : # DOWN + RIGHT
            self.neighbors.append(grid[self.row+1][self.col+1])
        if self.row < self.total_rows-1 and self.col > 0 \
            and "DOWN_LEFT" in dirs \
            and not grid[self.row+1][self.col-1].is_wall : # DOWN + LEFT
            self.neighbors.append(grid[self.row+1][self.col-1])
        if self.row > 0 and self.col < self.total_cols-1 \
            and "UP_RIGHT" in dirs \
            and not grid[self.row-1][self.col+1].is_wall : # UP + RIGHT
            self.neighbors.append(grid[self.row-1][self.col+1])
        if self.row > 0 and self.col > 0 \
            and "UP_LEFT" in dirs \
            and not grid[self.row-1][self.col-1].is_wall : # UP + LEFT
            self.neighbors.append(grid[self.row-1][self.col-1])
    #end def update_neighbors

    def __lt__ (self, other):
        return False

    @property
    def is_closed (self):
        return self.color == Node.CLOSED_RGB

    @property
    def is_open (self):
        return self.color == Node.OPENED_RGB

    @property
    def is_wall (self):
        return self.color == Node.WALL_RGB

    @property
    def is_start (self):
        return self.color == Node.START_RGB

    @property
    def is_end (self):
        return self.color == Node.END_RGB

    @property
    def is_reset (self):
        return self.color == Node.RESET_RGB

    def reset (self):
        self.color = Node.RESET_RGB

    def make_start (self):
        self.color = Node.START_RGB

    def make_closed (self):
        self.color = Node.CLOSED_RGB

    def make_open (self):
        self.color = Node.OPENED_RGB

    def make_wall (self):
        self.color = Node.WALL_RGB

    def make_end (self):
        self.color = Node.END_RGB

    def make_path (self):
        self.color = Node.PATH_RGB

def get_clicked_position (pos, rows, width):
    gap     = width // rows
    y, x    = pos
    row     = y // gap
    col     = x // gap

    return row, col
#def get_clicked_position

def main (win, width):
    ROWS    = 80
    grid    = Node.make_grid(ROWS, width)
    start   = None
    end     = None
    run     = True
    started = False
    is_maze = False

    while run :
        Node.draw_nodes(win, ROWS, grid, width)
        for event in pygame.event.get():
            if event.type == pygame.QUIT :
                run = False

            if started :
                continue

            if pygame.mouse.get_pressed()[0] : # LEFT CLICK
                pos         = pygame.mouse.get_pos()
                row, col    = get_clicked_position(pos, ROWS, width)
                node        = grid[row][col]
                if not start and node != end :
                    start = node
                    start.make_start()

                elif not end and node != start:
                    end = node
                    end.make_end()

                elif node != end and node != start :
                    node.make_wall()

            elif pygame.mouse.get_pressed()[2] : # RIGHT CLICK
                pos         = pygame.mouse.get_pos()
                row, col    = get_clicked_position(pos, ROWS, width)
                node        = grid[row][col]
                node.reset()
                if node == start :
                    start = None
                elif node == end :
                    end = None

            if event.type == pygame.KEYDOWN :
                if event.key == pygame.K_SPACE and start and end :
                    for row in grid :
                        for node in row :
                            node.update_neighbors(grid, ["RIGHT", "LEFT", "UP", "DOWN"]) if is_maze else node.update_neighbors(grid)

                    Node.run(lambda: Node.draw_nodes(win, ROWS, grid, width), grid, start, end)

                if event.key == pygame.K_c :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width)
                    is_maze = False

                if event.key == pygame.K_1 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .1)
                    is_maze = False

                if event.key == pygame.K_2 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .2)
                    is_maze = False

                if event.key == pygame.K_3 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .3)
                    is_maze = False

                if event.key == pygame.K_4 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .4)
                    is_maze = False

                if event.key == pygame.K_5 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .5)
                    is_maze = False

                if event.key == pygame.K_m :
                    start   = None
                    end     = None
                    grid    = Node.make_maze(ROWS, width)
                    is_maze = True

                if event.key == pygame.K_r :
                    start   = None
                    end     = None
                    grid    = Node.reset_grid(grid)

    pygame.quit()
#end main

main(WIN, WIDTH)