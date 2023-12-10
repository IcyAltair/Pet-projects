from random import choice
import sys

GAME_SYMBOLS = ('X', 'O', '_')
GRID_MAP = {"1 1": "1", "1 2": "2", "1 3": "3",
            "2 1": "4", "2 2": "5", "2 3": "6",
            "3 1": "7", "3 2": "8", "3 3": "9"}
PARAMS = ('start', 'user', 'easy', 'medium', 'hard')
ENEMY = {'X': 'O', 'O': 'X'}


class Game:
    def __init__(self) -> None:
        self.grid = {"1": "", "2": "", "3": "",
                     "4": "", "5": "", "6": "",
                     "7": "", "8": "", "9": ""}
        self.state = 'Game not finished'
        self.x_count, self.o_count = 0, 0
        self.turn = ''
        self.a_level, self.b_level = '', ''
        self.turns = []
        self.correct_params = False
        self.first, self.second = '', ''
        self.victories = [["1", "2", "3"],
                     ["4", "5", "6"],
                     ["7", "8", "9"],
                     ["1", "4", "7"],
                     ["2", "5", "8"],
                     ["3", "6", "9"],
                     ["1", "5", "9"],
                     ["3", "5", "7"]]

    def get_grid(self) -> None:
        user_grid = '_' * 9
        user_grid = [s for s in user_grid]
        if self.check_user_grid(user_grid):
            for i, v in enumerate(user_grid):
                if v == '_':
                    v = ' '
                if v == 'X':
                    self.x_count += 1
                elif v == 'O':
                    self.o_count += 1
                self.grid[str(i + 1)] = v
        else:
            print('Wrong cells')

    def print_grid(self) -> None:
        print('---------')
        for i in range(1, 8, 3):
            print('|' + ' ' + self.grid[str(i)] + ' '
                  + self.grid[str(i + 1)] + ' '
                  + self.grid[str(i + 2)] + ' ' + '|')
        print('---------')

    def menu(self):
        while not self.correct_params:
            params = input("Input command:")
            if params == 'exit':
                sys.exit(0)
            if ' ' not in params:
                self.print_bad_params()
                continue
            try:
                params = params.split(' ')
            except TypeError:
                self.print_bad_params()
            if len(params) != 3:
                self.print_bad_params()
                continue
            elif not all(p in PARAMS for p in params):
                self.print_bad_params()
                continue
            self.correct_params = True
            if params[1] == 'user':
                self.first = 'user'
                self.second = params[2]
                self.b_level = params[2]
            elif params[2] == 'user':
                self.first = params[1]
                self.second = 'user'
                self.a_level = params[1]
            else:
                self.first = params[1]
                self.second = params[2]
                self.a_level = params[1]
                self.b_level = params[2]

    def play(self):
        self.print_grid()
        while self.state == 'Game not finished':
            if self.first == 'user':
                while True:
                    if self.take_turn_user(side='X'):
                        break
                self.print_grid()
                self.check_grid()
            elif self.first != 'user':
                print(f'Making move level "{self.a_level}"')
                self.take_turn_ai(side='X', level=self.a_level)
                self.print_grid()
                self.check_grid()
            if self.state != 'Game not finished':
                break
            if self.second == 'user':
                while True:
                    if self.take_turn_user(side='O'):
                        break
                self.print_grid()
                self.check_grid()
            elif self.second != 'user':
                print(f'Making move level "{self.b_level}"')
                self.take_turn_ai(side='O', level=self.b_level)
                self.print_grid()
                self.check_grid()
            if self.state == 'Game not finished':
                print(self.state)

    def take_turn_user(self, side: str) -> bool:
        user_cords = input("Enter the coordinates:").split()
        user_cords = self.convert_coordinates(user_cords)
        if not user_cords:
            return False
        else:
            self.turns.append(int(user_cords))
        if self.grid[user_cords] != ' ':
            print('This cell is occupied! Choose another one!')
            return False
        self.grid[user_cords] = side
        self.turn = side
        '''
        elif self.x_count <= self.o_count:
            self.grid[user_cords] = 'X'
            self.x_count += 1
            self.turn = 'X'
        else:
            self.grid[user_cords] = 'O'
            self.o_count += 1
            self.turn = 'O'
        '''
        return True

    def take_turn_ai(self, side: str, level: str) -> None:
        if level == 'easy':
            ai_turn = choice([i for i in range(1, 10) if i not in self.turns])
            self.turns.append(ai_turn)
            self.grid[str(ai_turn)] = side
            self.turn = side
            return
        elif level == 'medium':
            for i in range(1, 4):
                if (self.grid[str(i+3)] == side and self.grid[str(i+6)] == side) or \
                        (self.grid[str(i+3)] == ENEMY[side] and self.grid[str(i+6)] == ENEMY[side]):
                    self.grid[str(i)] = side
                    self.turn = side
                    return
            for i in range(7, 10):
                if (self.grid[str(i-3)] == side and self.grid[str(i-6)] == side) or \
                        (self.grid[str(i-3)] == ENEMY[side] and self.grid[str(i-6)] == ENEMY[side]):
                    self.grid[str(i)] = side
                    self.turn = side
                    return
            for i in range(1, 8, 3):
                if (self.grid[str(i+1)] == side and self.grid[str(i+2)] == side) or \
                        (self.grid[str(i+1)] == ENEMY[side] and self.grid[str(i+2)] == ENEMY[side]):
                    self.grid[str(i)] = side
                    self.turn = side
                    return
            for i in range(3, 10, 3):
                if (self.grid[str(i-1)] == side and self.grid[str(i-2)] == side) or \
                        (self.grid[str(i-1)] == ENEMY[side] and self.grid[str(i-2)] == ENEMY[side]):
                    self.grid[str(i)] = side
                    self.turn = side
                    return
            j = 1
            if (self.grid[str(j + 4)] == side and self.grid[str(j + 8)] == side) or \
                    (self.grid[str(j + 4)] == ENEMY[side] and self.grid[str(j + 8)] == ENEMY[side]):
                self.grid[str(j)] = side
                self.turn = side
                return
            j = 9
            if (self.grid[str(j - 4)] == side and self.grid[str(j - 8)] == side) or \
                    (self.grid[str(j - 4)] == ENEMY[side] and self.grid[str(j - 8)] == ENEMY[side]):
                self.grid[str(j)] = side
                self.turn = side
                return
            j = 3
            if (self.grid[str(j + 2)] == side and self.grid[str(j + 4)] == side) or \
                    (self.grid[str(j + 2)] == ENEMY[side] and self.grid[str(j + 4)] == ENEMY[side]):
                self.grid[str(j)] = side
                self.turn = side
                return
            j = 7
            if (self.grid[str(j - 2)] == side and self.grid[str(j - 4)] == side) or \
                    (self.grid[str(j - 2)] == ENEMY[side] and self.grid[str(j - 4)] == ENEMY[side]):
                self.grid[str(j)] = side
                self.turn = side
                return
            ai_turn = choice([i for i in range(1, 10) if i not in self.turns])
            self.turns.append(ai_turn)
            self.grid[str(ai_turn)] = side
            self.turn = side
            return
        elif level == 'hard':
            ai_turn = ""
            ai_turn = self.check_line(2, 0)
            if ai_turn == "":
                ai_turn = self.check_line(0, 2)
            if ai_turn == "":
                ai_turn = self.check_line(1, 0)
            if ai_turn == "":
                if self.grid["5"] != "X" and self.grid["5"] != "O":
                    ai_turn = "5"
            if ai_turn == "":
                if self.grid["1"] != "X" and self.grid["1"] != "O":
                    ai_turn = "1"
            if ai_turn == "":
                ai_turn = choice([i for i in range(1, 10) if i not in self.turns])
            self.turns.append(int(ai_turn))
            print(ai_turn)
            self.grid[str(ai_turn)] = side
            self.turn = side
            return

    def check_line(self, sum_o, sum_x):
        step = ""
        for line in self.victories:
            o = 0
            x = 0
            for j in range(0, 3):
                if self.grid[line[j]] == "O":
                    o = o + 1
                if self.grid[line[j]] == "X":
                    x = x + 1
            if o == sum_o and x == sum_x:
                for j in range(0, 3):
                    if self.grid[line[j]] != "O" and self.grid[line[j]] != "X":
                        step = line[j]
        return step

    def check_grid(self) -> None:
        for i in range(1, 8, 3):
            if self.grid[str(i)] == self.turn \
                    and self.grid[str(i + 1)] == self.turn \
                    and self.grid[str(i + 2)] == self.turn:
                self.state = self.turn + ' wins'
                print(self.state)
        for i in range(1, 4):
            if self.grid[str(i)] == self.turn \
                    and self.grid[str(i + 3)] == self.turn \
                    and self.grid[str(i + 6)] == self.turn:
                self.state = self.turn + ' wins'
                print(self.state)
        j = 1
        if self.grid[str(j)] == self.turn \
                and self.grid[str(j + 4)] == self.turn \
                and self.grid[str(j + 8)] == self.turn:
            self.state = self.turn + ' wins'
            print(self.state)
        j = 3
        if self.grid[str(j)] == self.turn \
                and self.grid[str(j + 2)] == self.turn \
                and self.grid[str(j + 4)] == self.turn:
            self.state = self.turn + ' wins'
            print(self.state)
        if ' ' not in list(self.grid.values()) and 'wins' not in self.state:
            self.state = 'Draw'
            print(self.state)

    @classmethod
    def convert_coordinates(cls, user_cords: list) -> str:
        if any(not c.isdigit() for c in user_cords):
            print('You should enter numbers!')
            return ''
        else:
            user_cords = list(map(int, user_cords))
        if any(c > 3 or c < 1 for c in user_cords):
            print('Coordinates should be from 1 to 3!')
            return ''
        return GRID_MAP[" ".join(str(c) for c in user_cords)]

    @classmethod
    def check_user_grid(cls, user_grid: list) -> bool:
        if any(s not in GAME_SYMBOLS for s in user_grid) or len(user_grid) != 9:
            return False
        return True

    @classmethod
    def print_bad_params(cls) -> None:
        print('Bad parameters!')


if __name__ == "__main__":
    game = Game()
    game.menu()
    game.get_grid()
    game.play()
