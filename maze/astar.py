from queue import PriorityQueue
import math
import random

import pygame
pygame.font.init()


WIDTH           = 960 # Width of the window in pixels
NODE_WIDTH      = 6 # Width of a single node in pixels
WIN             = pygame.display.set_mode(size=(WIDTH, WIDTH))
FPS             = 40
SPEED_MS        = 5
pygame.display.set_caption("A* Path Finding Algorithm")
clock = pygame.time.Clock()

class Node(pygame.sprite.Sprite):
    CLOSED_RGB  = (220, 32, 32, 255)
    OPENED_RGB  = (64, 200, 64, 255)
    RESET_RGB   = (255, 255, 255, 255)
    WALL_RGB    = (0, 0, 0, 255)
    START_RGB   = (224, 128, 32, 255)
    END_RGB     = (64, 160, 160, 255)
    PATH_RGB    = (160, 255, 255, 255)
    LINE_RGB    = (192, 192, 192, 255)

    def __init__(self, row, col, width, total_rows, status=RESET_RGB):
        super().__init__()
        self.row        = row
        self.col        = col
        self.x          = row * width
        self.y          = col * width
        self.color      = status
        self.neighbors  = []
        self.width      = width-1 # Subtract 1 to avoid drawing issues at the edges
        self.total_rows = total_rows
        self.total_cols = total_rows
        self.image      = pygame.Surface((self.width, self.width), pygame.SRCALPHA)
        self.image.fill(self.color)
        self.rect       = self.image.get_rect(topleft=(self.x, self.y))

    def update_sprite(self):
        self.image.fill(self.color)

    @classmethod
    def euclidean_distance(cls, p1, p2):
        """
        Calculates the Euclidean distance (straight-line distance) between two points.

        Args:
            p1 (tuple): The first point as a tuple of (x, y) coordinates.
            p2 (tuple): The second point as a tuple of (x, y) coordinates.

        Returns:
            float: The Euclidean distance between p1 and p2.

        # This method is typically used as a heuristic function in pathfinding algorithms like A*.
        # It estimates the cost to reach from one point to another by computing the square root of the sum of squared differences in their coordinates.
        """
        x1, y1 = p1
        x2, y2 = p2
        return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

    @classmethod
    def manhattan_distance(cls, p1, p2):
        """
        Calculates the Manhattan distance between two points.

        This heuristic function is commonly used in grid-based pathfinding algorithms
        such as A* to estimate the cost from the current position to the goal. The Manhattan
        distance is the sum of the absolute differences of the x and y coordinates of the two points,
        which represents the minimum number of moves required to reach the target if only horizontal
        and vertical movements are allowed.

        Args:
            p1 (tuple): The (x, y) coordinates of the first point.
            p2 (tuple): The (x, y) coordinates of the second point.

        Returns:
            int: The Manhattan distance between p1 and p2.
        """
        x1, y1 = p1
        x2, y2 = p2
        return abs(x1 - x2) + abs(y1 - y2)

    @classmethod
    def reconstruct_path(cls, came_from, current, rows, width):
        while current in came_from:
            current = came_from[current]
            current.make_path()
            cls.redraw_nodes([current])

    @classmethod
    def run(cls, grid, start, end, rows, width, heuristic):
        count = 0
        open_set = PriorityQueue()
        open_set.put((0, count, start))
        came_from = {}
        g_score = {node: float("inf") for row in grid for node in row}
        g_score[start] = 0
        f_score = {node: float("inf") for row in grid for node in row}
        f_score[start] = heuristic(start.get_position(), end.get_position())
        open_set_hash = {start}

        while not open_set.empty():
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()

            current = open_set.get()[2]
            open_set_hash.remove(current)

            if current == end:
                Node.reconstruct_path(came_from, end, rows, width)
                end.make_end()
                start.make_start()
                return True

            for neighbor in current.neighbors:
                neighbor_pos = neighbor.get_position()
                current_pos = current.get_position()
                temp_g_score = g_score[current] + heuristic(neighbor_pos, current_pos)
                if temp_g_score < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = temp_g_score
                    f_score[neighbor] = temp_g_score + heuristic(neighbor_pos, end.get_position())
                    if neighbor not in open_set_hash:
                        count += 1
                        open_set.put((f_score[neighbor], count, neighbor))
                        open_set_hash.add(neighbor)
                        neighbor.make_open()
                        cls.redraw_nodes([neighbor])

            if current != start:
                current.make_closed()
                cls.redraw_nodes([current])

        return False

    @classmethod
    def redraw_nodes(cls, nodes):
        for node in nodes:
            node.update_sprite()
            WIN.blit(node.image, node.rect)

    @classmethod
    def make_grid(cls, rows, width, random_walls=0.):
        grid = []
        gap = width // rows
        for i in range(rows):
            grid.append([])
            for j in range(rows):
                status = Node.RESET_RGB
                if random.uniform(0, 1) < random_walls:
                    status = Node.WALL_RGB
                node = cls(i, j, gap, rows, status)
                grid[i].append(node)
        return grid

    @classmethod
    def reset_grid(cls, grid, keep_start_end=False):
        rows = len(grid)
        for i in range(rows):
            for j in range(rows):
                if not grid[i][j].is_wall:
                    if keep_start_end and (grid[i][j].is_start or grid[i][j].is_end):
                        continue
                    else:
                        grid[i][j].reset()
                        cls.redraw_nodes([grid[i][j]])
        return grid

    @classmethod
    def count_steps(cls, grid):
        rows = len(grid)
        steps = 0
        for i in range(rows):
            for j in range(rows):
                if grid[i][j].is_closed or grid[i][j].is_open or grid[i][j].is_path:
                    steps += 1
        return steps

    @classmethod
    def make_maze(cls, rows, width):
        grid = Node.make_grid(rows, width, 1.)
        row = int(random.uniform(0, rows - 1))
        col = int(random.uniform(0, rows - 1))
        start = grid[row][col]
        start.reset()
        visited_hash = {(start.row, start.col)}
        walls = PriorityQueue()
        inits = start.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])
        for _, node in inits.items():
            walls.put((random.uniform(0, 1), node))

        while not walls.empty():
            current = walls.get()[1]
            neighbors_d = current.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])
            if len(neighbors_d.items()) > 0:
                visited = [x for x in neighbors_d.items() if (x[1].row, x[1].col) in visited_hash]
                if len(visited) == 1:
                    current.reset()
                    cell_dir = visited[0][0]
                    other = None
                    if cell_dir == "UP" and "DOWN" in neighbors_d.keys():
                        other = neighbors_d["DOWN"]
                    elif cell_dir == "DOWN" and "UP" in neighbors_d.keys():
                        other = neighbors_d["UP"]
                    elif cell_dir == "LEFT" and "RIGHT" in neighbors_d.keys():
                        other = neighbors_d["RIGHT"]
                    elif cell_dir == "RIGHT" and "LEFT" in neighbors_d.keys():
                        other = neighbors_d["LEFT"]

                    if not other is None:
                        other.reset()
                        other_walls = other.get_neighbors(grid, ["UP", "DOWN", "LEFT", "RIGHT"])
                        visited_hash.add((current.row, current.col))
                        visited_hash.add((other.row, other.col))
                        for _, node in other_walls.items():
                            if not (node.row, node.col) in visited_hash:
                                walls.put((random.uniform(0, 1), node))
        return grid

    @classmethod
    def _draw_grid(cls, win, rows, width):
        gap = width // rows
        for i in range(rows):
            pygame.draw.line(win, Node.LINE_RGB, (0, i * gap), (width, i * gap))
            for j in range(rows):
                pygame.draw.line(win, Node.LINE_RGB, (j * gap, 0), (j * gap, width))

    @classmethod
    def draw_nodes(cls, win, rows, grid, width):
        win.fill(Node.RESET_RGB)
        for row in grid:
            for node in row:
                node.update_sprite()
                win.blit(node.image, node.rect)
        cls._draw_grid(win, rows, width)
        pygame.display.update()

    def get_position(self):
        return self.row, self.col

    def draw(self, win):
        self.update_sprite()
        win.blit(self.image, self.rect)

    def get_neighbors(self, grid, dirs=["DOWN", "UP", "RIGHT", "LEFT", "DOWN_RIGHT", "DOWN_LEFT", "UP_RIGHT", "UP_LEFT"], visited={}, dist=1):
        ret = {}
        if self.row < self.total_rows - dist and "DOWN" in dirs and not grid[self.row + dist][self.col] in visited:
            ret["DOWN"] = grid[self.row + 1][self.col]
        if self.row > dist - 1 and "UP" in dirs and not grid[self.row - dist][self.col] in visited:
            ret["UP"] = grid[self.row - dist][self.col]
        if self.col < self.total_cols - dist and "RIGHT" in dirs and not grid[self.row][self.col + dist] in visited:
            ret["RIGHT"] = grid[self.row][self.col + dist]
        if self.col > dist - 1 and "LEFT" in dirs and not grid[self.row][self.col - dist] in visited:
            ret["LEFT"] = grid[self.row][self.col - dist]
        if dist == 1:
            if self.row < self.total_rows - 1 and self.col < self.total_cols - 1 and "DOWN_RIGHT" in dirs and not grid[self.row + 1][self.col + 1] in visited:
                ret["DOWN_RIGHT"] = grid[self.row + 1][self.col + 1]
            if self.row < self.total_rows - 1 and self.col > 0 and "DOWN_LEFT" in dirs and not grid[self.row + 1][self.col - 1] in visited:
                ret["DOWN_LEFT"] = grid[self.row + 1][self.col - 1]
            if self.row > 0 and self.col < self.total_cols - 1 and "UP_RIGHT" in dirs and not grid[self.row - 1][self.col + 1] in visited:
                ret["UP_RIGHT"] = grid[self.row - 1][self.col + 1]
            if self.row > 0 and self.col > 0 and "UP_LEFT" in dirs and not grid[self.row - 1][self.col - 1] in visited:
                ret["UP_LEFT"] = grid[self.row - 1][self.col - 1]
        return ret

    def update_neighbors(self, grid, dirs=["DOWN", "UP", "RIGHT", "LEFT", "DOWN_RIGHT", "DOWN_LEFT", "UP_RIGHT", "UP_LEFT"]):
        self.neighbors = []
        if self.row < self.total_rows - 1 and "DOWN" in dirs and not grid[self.row + 1][self.col].is_wall:
            self.neighbors.append(grid[self.row + 1][self.col])
        if self.row > 0 and "UP" in dirs and not grid[self.row - 1][self.col].is_wall:
            self.neighbors.append(grid[self.row - 1][self.col])
        if self.col < self.total_cols - 1 and "RIGHT" in dirs and not grid[self.row][self.col + 1].is_wall:
            self.neighbors.append(grid[self.row][self.col + 1])
        if self.col > 0 and "LEFT" in dirs and not grid[self.row][self.col - 1].is_wall:
            self.neighbors.append(grid[self.row][self.col - 1])
        if self.row < self.total_rows - 1 and self.col < self.total_cols - 1 and "DOWN_RIGHT" in dirs and not grid[self.row + 1][self.col + 1].is_wall:
            self.neighbors.append(grid[self.row + 1][self.col + 1])
        if self.row < self.total_rows - 1 and self.col > 0 and "DOWN_LEFT" in dirs and not grid[self.row + 1][self.col - 1].is_wall:
            self.neighbors.append(grid[self.row + 1][self.col - 1])
        if self.row > 0 and self.col < self.total_cols - 1 and "UP_RIGHT" in dirs and not grid[self.row - 1][self.col + 1].is_wall:
            self.neighbors.append(grid[self.row - 1][self.col + 1])
        if self.row > 0 and self.col > 0 and "UP_LEFT" in dirs and not grid[self.row - 1][self.col - 1].is_wall:
            self.neighbors.append(grid[self.row - 1][self.col - 1])

    @property
    def is_closed(self):
        return self.color == Node.CLOSED_RGB

    @property
    def is_open(self):
        return self.color == Node.OPENED_RGB

    @property
    def is_path(self):
        return self.color == Node.PATH_RGB

    @property
    def is_wall(self):
        return self.color == Node.WALL_RGB

    @property
    def is_start(self):
        return self.color == Node.START_RGB

    @property
    def is_end(self):
        return self.color == Node.END_RGB

    @property
    def is_reset(self):
        return self.color == Node.RESET_RGB

    def reset(self):
        self.color = Node.RESET_RGB
        self.update_sprite()

    def make_start(self):
        self.color = Node.START_RGB
        self.update_sprite()

    def make_closed(self):
        self.color = Node.CLOSED_RGB
        self.update_sprite()

    def make_open(self):
        self.color = Node.OPENED_RGB
        self.update_sprite()

    def make_wall(self):
        self.color = Node.WALL_RGB
        self.update_sprite()

    def make_end(self):
        self.color = Node.END_RGB
        self.update_sprite()

    def make_path(self):
        self.color = Node.PATH_RGB
        self.update_sprite()

def get_clicked_position (pos, rows, width):
    gap     = width // rows
    y, x    = pos
    row     = y // gap
    col     = x // gap

    return row, col
#def get_clicked_position

def report_result(grid, heuristics, h_idx):
    font = pygame.font.SysFont(None, 32)
    text_color = (0, 114, 187, 255)  # French blue RGBA
    msg = "Path found using heuristic '{}' (index {}) in {} steps.".format(
        heuristics[h_idx % len(heuristics)].__name__, h_idx % len(heuristics), Node.count_steps(grid))
    text_surface = font.render(msg, True, text_color[:3])
    text_bg = pygame.Surface(text_surface.get_size(), pygame.SRCALPHA)
    text_bg.fill((255, 255, 255, 200))  # partially transparent background
    text_bg.blit(text_surface, (0, 0))
    text_bg.set_alpha(text_color[3])

    # Initial position: center
    x = (WIN.get_width() - text_bg.get_width()) // 2
    y = (WIN.get_height() - text_bg.get_height()) // 2

    dragging = False
    offset_x, offset_y = 0, 0
    waiting = True

    while waiting:
        WIN.fill(Node.RESET_RGB)
        Node.draw_nodes(WIN, len(grid), grid, WIN.get_width())
        WIN.blit(text_bg, (x, y))
        pygame.display.update()

        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                pygame.quit()
                return
            if e.type == pygame.KEYDOWN:
                if e.key == pygame.K_SPACE or e.key == pygame.K_ESCAPE:
                    waiting = False
            if e.type == pygame.MOUSEBUTTONDOWN:
                mx, my = pygame.mouse.get_pos()
                if x <= mx <= x + text_bg.get_width() and y <= my <= y + text_bg.get_height():
                    dragging = True
                    offset_x = mx - x
                    offset_y = my - y
            if e.type == pygame.MOUSEBUTTONUP:
                dragging = False
            if e.type == pygame.MOUSEMOTION and dragging:
                mx, my = pygame.mouse.get_pos()
                x = mx - offset_x
                y = my - offset_y
# def report_result

def main (win, width):
    ROWS    = WIDTH // NODE_WIDTH
    grid    = Node.make_grid(ROWS, width)
    start   = None
    end     = None
    run     = True
    started = False
    is_maze = False
    heuristics = [Node.euclidean_distance, Node.manhattan_distance]  # List of heuristics to choose from
    h_idx = 0  # Index for the current heuristic

    while run :
        clock.tick(FPS)
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
                    if h_idx != 0 : 
                        grid = Node.reset_grid(grid, True)             
                    for row in grid :
                        for node in row :
                            node.update_neighbors(grid, ["RIGHT", "LEFT", "UP", "DOWN"]) if is_maze else node.update_neighbors(grid)
                    Node.run(grid, start, end, ROWS, width, heuristics[h_idx % len(heuristics)])
                    # Display result as a message in the application window
                    report_result(grid, heuristics, h_idx)
                    h_idx += 1

                if event.key == pygame.K_c :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_1 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .1)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_2 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .2)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_3 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .3)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_4 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .4)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_5 :
                    start   = None
                    end     = None
                    grid    = Node.make_grid(ROWS, width, .5)
                    h_idx   = 0
                    is_maze = False

                if event.key == pygame.K_m :
                    start   = None
                    end     = None
                    grid    = Node.make_maze(ROWS, width)
                    h_idx   = 0
                    is_maze = True

                if event.key == pygame.K_r :
                    start   = None
                    end     = None
                    grid    = Node.reset_grid(grid)
                    h_idx   = 0

    pygame.quit()


#end main

main(WIN, WIDTH)
#TODO: add help