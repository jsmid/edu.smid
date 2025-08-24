from queue import PriorityQueue
import math
import random
import pygame
import sys

pygame.init()  # Ensure pygame is initialized before using any pygame functions

WIDTH           = 960 # Width of the window in pixels
NODE_WIDTH      = 6 # Width of a single node in pixels
WIN             = pygame.display.set_mode(size=(WIDTH, WIDTH))
FPS             = 40
SPEED_MS        = 5
TEXT_SIZE       = 16
# Window transparency for the result message box (0=fully transparent, 255=opaque)
WND_TRANSPARENCY = 220

# You can list available system fonts using pygame.font.get_fonts()
    # Example: print(pygame.font.get_fonts())
    # To use a specific font, pass its name as the first argument to SysFont, e.g.:
    # font = pygame.font.SysFont("arial", TEXT_SIZE)
    #
    # ['arial', 'arialblack', 'bahnschrift', 'calibri', 'cambria', 'cambriamath', 'candara', 'comicsansms', 
    # 'consolas', 'constantia', 'corbel', 'couriernew', 'ebrima', 'franklingothicmedium', 'gabriola', 'gadugi', 
    # 'georgia', 'impact', 'inkfree', 'javanesetext', 'leelawadeeui', 'leelawadeeuisemilight', 'lucidaconsole', 
    # 'lucidasans', 'malgungothic', 'malgungothicsemilight', 'microsofthimalaya', 'microsoftjhenghei', 
    # 'microsoftjhengheiui', 'microsoftnewtailue', 'microsoftphagspa', 'microsoftsansserif', 'microsofttaile', 
    # 'microsoftyahei', 'microsoftyaheiui', 'microsoftyibaiti', 'mingliuextb', 'pmingliuextb', 'mingliuhkscsextb', 
    # 'mongolianbaiti', 'msgothic', 'msuigothic', 'mspgothic', 'mvboli', 'myanmartext', 'nirmalaui', 'nirmalauisemilight', 
    # 'nirmalatext', 'nirmalatextsemilight', 'palatinolinotype', 'sansserifcollection', 'segoefluenticons', 'segoemdl2assets', 
    # 'segoeprint', 'segoescript', 'segoeui', 'segoeuiblack', 'segoeuiemoji', 'segoeuihistoric', 'segoeuisemibold', 
    # 'segoeuisemilight', 'segoeuisymbol', 'segoeuivariable', 'simsun', 'nsimsun', 'simsunextb', 'sitkatext', 'sylfaen', 
    # 'symbol', 'tahoma', 'timesnewroman', 'trebuchetms', 'verdana', 'webdings', 'wingdings', 'yugothic', 'yugothicuisemibold', 
    # 'yugothicui', 'yugothicmedium', 'yugothicuiregular', 'yugothicregular', 'yugothicuisemilight', 'simsunextg', 'agencyfbtučné', 
    # 'agencyfb', 'algerian', 'bookantiquatučné', 'bookantiquatučnékurzíva', 'bookantiquakurzíva', 'arialtučné', 'arialtučnékurzíva', 
    # 'arialkurzíva', 'arialrounded', 'baskervilleoldface', 'bauhaus93', 'bell', 'belltučné', 'bellkurzíva', 'bernardcondensed', 
    # 'bookantiqua', 'bodonitučné', 'bodonitučnékurzíva', 'bodoniblackkurzíva', 'bodoniblack', 'bodonicondensedtučné', 
    # 'bodonicondensedtučnékurzíva', 'bodonicondensedkurzíva', 'bodonicondensed', 'bodonikurzíva', 'bodonipostercompressed', 
    # 'bodoni', 'bookmanoldstyle', 'bookmanoldstyletučné', 'bookmanoldstyletučnékurzíva', 'bookmanoldstylekurzíva', 
    # 'bradleyhanditc', 'britannic', 'berlinsansfbtučné', 'berlinsansfbdemitučné', 'berlinsansfb', 'broadway', 'brushscriptkurzíva', 
    # 'bookshelfsymbol7', 'californianfbtučné', 'californianfbkurzíva', 'californianfb', 'calisto', 'calistotučné', 
    # 'calistotučnékurzíva', 'calistokurzíva', 'castellar', 'centuryschoolbook', 'centaur', 'century', 'chiller', 
    # 'colonna', 'cooperblack', 'copperplategothic', 'curlz', 'dubai', 'dubaimedium', 'dubairegular', 'elephant', 
    # 'elephantkurzíva', 'engravers', 'erasitc', 'erasdemiitc', 'erasmediumitc', 'felixtitling', 'forte', 'franklingothicbook', 
    # 'franklingothicbookkurzíva', 'franklingothicdemi', 'franklingothicdemicond', 'franklingothicdemikurzíva', 
    # 'franklingothicheavy', 'franklingothicheavykurzíva', 'franklingothicmediumcond', 'freestylescript', 'frenchscript', 
    # 'footlight', 'garamond', 'garamondtučné', 'garamondkurzíva', 'gigi', 'gillsanstučnékurzíva', 'gillsanstučné', 
    # 'gillsanscondensed', 'gillsanskurzíva', 'gillsansultracondensed', 'gillsansultra', 'gillsans', 'gloucesterextracondensed', 
    # 'gillsansextcondensed', 'centurygothic', 'centurygothictučné', 'centurygothictučnékurzíva', 'centurygothickurzíva', 
    # 'goudyoldstyle', 'goudyoldstyletučné', 'goudyoldstylekurzíva', 'goudystout', 'harlowsolid', 'harrington', 'haettenschweiler', 
    # 'hightowertext', 'hightowertextkurzíva', 'imprintshadow', 'informalroman', 'blackadderitc', 'edwardianscriptitc', 'kristenitc', 
    # 'jokerman', 'juiceitc', 'kunstlerscript', 'widelatin', 'lucidabright', 'lucidacalligraphy', 'leelawadee', 'leelawadeetučné', 
    # 'lucidafaxregular', 'lucidafax', 'lucidahandwriting', 'lucidasansregular', 'lucidasansroman', 'lucidasanstypewriterregular', 
    # 'lucidasanstypewriter', 'lucidasanstypewriteroblique', 'magnetotučné', 'maiandragd', 'maturascriptcapitals', 'mistral', 
    # 'modernno20', 'microsoftuighurtučné', 'microsoftuighur', 'monotypecorsiva', 'extra', 'niagaraengraved', 'niagarasolid', 
    # 'ocraextended', 'oldenglishtext', 'onyx', 'msoutlook', 'palacescript', 'papyrus', 'parchment', 'perpetuatučnékurzíva', 
    # 'perpetuatučné', 'perpetuakurzíva', 'perpetuatitlingtučné', 'perpetuatitling', 'perpetua', 'playbill', 'poorrichard', 
    # 'pristina', 'rage', 'ravie', 'msreferencesansserif', 'msreferencespecialty', 'rockwellcondensedtučné', 'rockwellcondensed', 
    # 'rockwell', 'rockwelltučné', 'rockwelltučnékurzíva', 'rockwellextra', 'rockwellkurzíva', 'centuryschoolbooktučné', 
    # 'centuryschoolbooktučnékurzíva', 'centuryschoolbookkurzíva', 'script', 'showcardgothic', 'snapitc', 'stencil', 
    # 'twcentučnékurzíva', 'twcentučné', 'twcencondensedtučné', 'twcencondensedextra', 'twcencondensed', 'twcenkurzíva', 
    # 'twcen', 'tempussansitc', 'vinerhanditc', 'vivaldikurzíva', 'vladimirscript', 'wingdings2', 'wingdings3']
APP_FONT_NAME   = 'georgia' # Use default font
pygame.font.init()
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
                    sys.exit()

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

class TextSprite(pygame.sprite.Sprite):
    def __init__(self, text, font, color, bg_color, alpha):
        """ Initializes a TextSprite object that displays a text label with a customizable font, 
        text color, background color, and alpha transparency, and includes a close button 
        rendered as an 'X' with a transparent background. The method creates a Pygame surface 
        sized to fit the text, padding, and the close button, fills it with the specified 
        background color and alpha, draws the text at the appropriate position, and adds the close button. 
        The resulting surface is assigned to the sprite's image attribute, 
        and its rect attribute is set accordingly.

        Args:
            text (str): The text to display in the sprite.
            font (pygame.font.Font): The font to use for rendering the text.
            color (tuple): The color of the text as an RGB tuple.
            bg_color (tuple): The background color of the sprite as an RGB tuple.
            alpha (int): The alpha transparency value for the sprite (0-255).
        """
        super().__init__()
        text_surface = font.render(text, True, color)
        padding = 10
        button_size = 16
        # Calculate size for text + padding + button
        width = text_surface.get_width() + padding * 2 + button_size
        height = max(text_surface.get_height() + padding * 2, button_size + padding)
        self.image = pygame.Surface((width, height), pygame.SRCALPHA)
        self.image.fill(bg_color)
        self.image.set_alpha(alpha)
        # Draw text
        self.image.blit(text_surface, (padding, padding))
        # Draw close button (only 'X', transparent background)
        self.draw_close_button(padding, button_size, width)
        self.rect = self.image.get_rect()

    def draw_close_button(self, padding, button_size, width):
        """
        Draws a close ('X') button on the surface image of the object.

        This method creates a rectangular area in the top-right corner of the surface, 
        sized according to `button_size` and offset by `padding`. The rectangle itself 
        is not filled or outlined; instead, two diagonal red lines are drawn within 
        the rectangle to form an 'X', visually representing a close button. The 
        position and size of the button are dynamically calculated based on the 
        provided `width`, `button_size`, and `padding` parameters. The rectangle's 
        coordinates are stored in `self.close_rect` for later use, such as detecting 
        mouse clicks.

        Args:
            padding (int): The space in pixels between the button and the edges of the surface.
            button_size (int): The width and height of the square close button in pixels.
            width (int): The total width of the surface on which the button is drawn.

        Side Effects:
            - Updates `self.close_rect` with the position and size of the close button.
            - Draws two red diagonal lines on `self.image` to form the 'X' symbol.
        """
        self.close_rect = pygame.Rect(width - button_size - padding // 2, padding // 2, button_size, button_size)
        # No rectangle fill, just draw 'X'
        x_margin = 6
        pygame.draw.line(
            self.image, (200, 0, 0),
            (self.close_rect.left + x_margin, self.close_rect.top + x_margin),
            (self.close_rect.right - x_margin, self.close_rect.bottom - x_margin), 2
        )
        pygame.draw.line(
            self.image, (200, 0, 0),
            (self.close_rect.left + x_margin, self.close_rect.bottom - x_margin),
            (self.close_rect.right - x_margin, self.close_rect.top + x_margin), 2
        )

    def is_close_clicked(self, mouse_pos):
        """
        Determines whether the close button of the sprite was clicked based on the mouse position.

        This method checks if a mouse click occurred within the bounds of the close button (represented by `self.close_rect`)
        of the sprite. The `mouse_pos` parameter is expected to be a tuple containing the x and y coordinates of the mouse
        relative to the entire window or screen. The method first converts these coordinates to be relative to the top-left
        corner of the sprite by subtracting the sprite's position (`self.rect.x` and `self.rect.y`). It then checks if the
        resulting relative coordinates fall within the area defined by `self.close_rect`, which represents the clickable
        region for closing the sprite (such as a close or "X" button).

        Args:
            mouse_pos (tuple): The (x, y) position of the mouse click, relative to the window or screen.

        Returns:
            bool: True if the close button was clicked, False otherwise.
        """
        # mouse_pos is relative to the sprite's top-left
        rel_x = mouse_pos[0] - self.rect.x
        rel_y = mouse_pos[1] - self.rect.y
        return self.close_rect.collidepoint(rel_x, rel_y)

    def show(self, win, grid):
        """
        Displays the current node's image in a draggable window and handles user interaction.
        This method creates an interactive window using Pygame, where the node's image is displayed
        on top of the provided grid. The window supports the following interactions:
          - The user can drag the node's image around the window by clicking and holding the mouse button
            on the image, then moving the mouse.
          - The user can close the window by clicking a designated "close" area on the image (as determined
            by `self.is_close_clicked`), or by pressing the SPACE key.
          - The window will also close if the user closes the Pygame window.
        The method continuously redraws the grid and the node's image until the user performs an action
        to exit. It updates the display only within the area occupied by the node's image for efficiency.
        Args:
            win (pygame.Surface): The Pygame surface (window) where the grid and node image are drawn.
            grid (list): The grid data structure representing the maze or environment.
        Side Effects:
            - Updates the Pygame window with the node's image and grid.
            - Handles user input events for dragging and closing the window.
            - May terminate the Pygame application if the window is closed.
        """
        dragging = False
        offset_x, offset_y = 0, 0
        waiting = True
        # Draw the grid once and keep as background to avoid flicker
        background = pygame.Surface(win.get_size())
        Node.draw_nodes(background, len(grid), grid, win.get_width())
        prev_rect = self.rect.copy()
        while waiting:
            # Restore background only under the previous sprite rect to erase old position
            win.blit(background, prev_rect, prev_rect)
            # Draw the sprite at the new position
            win.blit(self.image, self.rect)
            pygame.display.update([prev_rect, self.rect])
            prev_rect = self.rect.copy()

            for e in pygame.event.get():
                if e.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if e.type == pygame.KEYDOWN and e.key == pygame.K_SPACE:
                    waiting = False
                if e.type == pygame.MOUSEBUTTONDOWN:
                    mx, my = pygame.mouse.get_pos()
                    if self.rect.collidepoint(mx, my):
                        if self.is_close_clicked((mx, my)):
                            waiting = False
                        else:
                            dragging = True
                            offset_x = mx - self.rect.x
                            offset_y = my - self.rect.y
                if e.type == pygame.MOUSEBUTTONUP:
                    dragging = False
                if e.type == pygame.MOUSEMOTION and dragging:
                    mx, my = pygame.mouse.get_pos()
                    self.rect.x = mx - offset_x
                    self.rect.y = my - offset_y

class MultiTextSprite(TextSprite):
    def __init__(self, texts, font, color, bg_color, alpha):
        super().__init__("", font, color, bg_color, alpha)
        padding = 10
        button_size = 16
        text_surfaces = [font.render(text, True, color) for text in texts]
        width = max(ts.get_width() for ts in text_surfaces) + padding * 2 + button_size
        height = sum(ts.get_height() for ts in text_surfaces) + padding * (len(text_surfaces) + 1)
        height = max(height, button_size + padding)
        self.image = pygame.Surface((width, height), pygame.SRCALPHA)
        self.image.fill(bg_color)
        self.image.set_alpha(alpha)
        y_offset = padding
        for ts in text_surfaces:
            self.image.blit(ts, (padding, y_offset))
            y_offset += ts.get_height() + padding
        self.draw_close_button(padding, button_size, width)
        self.rect = self.image.get_rect()

def report_result(grid, heuristics, h_idx):
    """
    This function creates a message summarizing the pathfinding result, including
    the heuristic used and the number of steps taken. It then displays this message
    in a custom message box (TextSprite) centered on the window. The message box
    can be dragged with the mouse and closed either by clicking its close button
    or pressing the spacebar.

    The function enters a loop where it:
      - Redraws the grid and message box each frame.
      - Handles user events:
        - QUIT: exits the application.
        - KEYDOWN (space): closes the message box.
        - MOUSEBUTTONDOWN: starts dragging if the message box is clicked, or closes if the close button is clicked.
        - MOUSEBUTTONUP: stops dragging.
        - MOUSEMOTION: moves the message box if dragging.

    Args:
        grid (list): The grid of nodes.
        heuristics (list): List of heuristic functions used.
        h_idx (int): Index of the heuristic used.
    """    
    font = pygame.font.SysFont(APP_FONT_NAME, TEXT_SIZE)
    text_color = (0, 114, 187)  # RGB
    bg_color = (255, 255, 255, WND_TRANSPARENCY)  # RGBA
    msg = "Path found using heuristic '{}' (index {}) in {} steps.".format(
        heuristics[h_idx % len(heuristics)].__name__, h_idx % len(heuristics), Node.count_steps(grid))
    text_sprite = TextSprite(msg, font, text_color, bg_color[:3], bg_color[3])

    # Initial position: center
    x = (WIN.get_width() - text_sprite.image.get_width()) // 2
    y = (WIN.get_height() - text_sprite.image.get_height()) // 2
    text_sprite.rect.topleft = (x, y)
    text_sprite.show(WIN, grid)

def main (win, width):
    """
    Runs the interactive visualization for the A* pathfinding algorithm.
    This function initializes the grid and handles user interactions to set up the start and end nodes,
    draw walls, generate random grids or mazes, and run the A* algorithm with selectable heuristics.
    The visualization is rendered in a Pygame window, and users can interact using mouse clicks and keyboard shortcuts.
    Parameters:
        win (pygame.Surface): The Pygame window surface where the visualization is drawn.
        width (int): The width of the window/grid in pixels.
    Functionality:
        - Left mouse click: Set the start node, end node, or draw walls.
        - Right mouse click: Remove nodes (reset to empty).
        - SPACE key: Run the A* algorithm using the current heuristic, cycling through available heuristics.
        - C key: Clear the grid.
        - 1-5 keys: Generate random grids with increasing wall density (10% to 50%).
        - M key: Generate a random maze.
        - R key: Reset the grid to its initial state.
        - The result of the pathfinding is displayed in the application window.
    The function runs in a loop until the user closes the window, handling all events and updating the visualization accordingly.
    """
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
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if started:
                continue

            if pygame.mouse.get_pressed()[0]:  # LEFT CLICK
                pos = pygame.mouse.get_pos()
                row, col = get_clicked_position(pos, ROWS, width)
                node = grid[row][col]
                if not start and node != end:
                    start = node
                    start.make_start()
                elif not end and node != start:
                    end = node
                    end.make_end()
                elif node != end and node != start:
                    node.make_wall()

            elif pygame.mouse.get_pressed()[2]:  # RIGHT CLICK
                pos = pygame.mouse.get_pos()
                row, col = get_clicked_position(pos, ROWS, width)
                node = grid[row][col]
                node.reset()
                if node == start:
                    start = None
                elif node == end:
                    end = None

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE and start and end:
                    if h_idx != 0:
                        grid = Node.reset_grid(grid, True)
                    for row in grid:
                        for node in row:
                            node.update_neighbors(grid, ["RIGHT", "LEFT", "UP", "DOWN"]) if is_maze else node.update_neighbors(grid)
                    Node.run(grid, start, end, ROWS, width, heuristics[h_idx % len(heuristics)])
                    # Display result as a message in the application window
                    report_result(grid, heuristics, h_idx)
                    h_idx += 1

                if event.key == pygame.K_c:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_1:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width, .1)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_2:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width, .2)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_3:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width, .3)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_4:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width, .4)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_5:
                    start = None
                    end = None
                    grid = Node.make_grid(ROWS, width, .5)
                    h_idx = 0
                    is_maze = False

                if event.key == pygame.K_m:
                    start = None
                    end = None
                    grid = Node.make_maze(ROWS, width)
                    h_idx = 0
                    is_maze = True

                if event.key == pygame.K_r:
                    start = None
                    end = None
                    grid = Node.reset_grid(grid)
                    h_idx = 0

                if event.key == pygame.K_h:
                    help_lines = [
                        "A* Pathfinding Help:",
                        "Left Click: Set start, end, or draw walls",
                        "Right Click: Remove node/reset",
                        "SPACE: Run A* (cycles heuristics)",
                        "C: Clear grid",
                        "1-5: Random grid (10%-50% walls)",
                        "M: Generate maze",
                        "R: Reset grid",
                        "H: Show this help",
                        "Close window: Quit"
                    ]
                    font = pygame.font.SysFont(APP_FONT_NAME, TEXT_SIZE//4*3)
                    text_color = (0, 0, 0)
                    bg_color = (255, 255, 255, WND_TRANSPARENCY)
                    multi_text_sprite = MultiTextSprite(help_lines, font, text_color, bg_color[:3], bg_color[3])
                    x = (WIN.get_width() - multi_text_sprite.image.get_width()) // 2
                    y = (WIN.get_height() - multi_text_sprite.image.get_height()) // 2
                    multi_text_sprite.rect.topleft = (x, y)
                    multi_text_sprite.show(WIN, grid)

    pygame.quit()
    sys.exit()
#end main

main(WIN, WIDTH)
#TODO: add help