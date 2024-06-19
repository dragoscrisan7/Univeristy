import pygame
from random import randint


class Board_Services:
    def __init__(self, board_repo):
        self.__board = board_repo

    def check_full_column(self, column):
        return self.__board.get_next_valid_poz(column) == -1

    def set_on_valid_poz(self, row, column, player):
        if self.__board.is_valid_poz(row, column):
            self.__board.set_poz(row, column, player)
        else:
            valid_poz = self.__board.get_next_valid_poz(column)
            if valid_poz != -1:
                self.__board.set_poz(valid_poz, column, player)

    def check_winning_move(self, player):
        for c in range(7 - 3):
            for r in range(6):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r, c+1) == player and \
                        self.__board.get_poz(r, c+2) == player and self.__board.get_poz(r, c+3) == player:
                    return True

        for c in range(7):
            for r in range(6-3):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r+1, c) == player and \
                        self.__board.get_poz(r+2, c) == player and self.__board.get_poz(r+3, c) == player:
                    return True

        for c in range(7 - 3):
            for r in range(6-3):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r+1, c+1) == player and \
                        self.__board.get_poz(r+2, c+2) == player and self.__board.get_poz(r+3, c+3) == player:
                    return True

        for c in range(7 - 3):
            for r in range(3, 6):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r-1, c+1) == player and \
                        self.__board.get_poz(r-2, c+2) == player and self.__board.get_poz(r-3, c+3) == player:
                    return True

    def almost_winning_move(self, player):
        for c in range(7 - 3):
            for r in range(6):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r, c+1) == player and \
                        self.__board.get_poz(r, c+2) == player and self.__board.is_valid_poz(r, c+3):
                    poz = [r, c+3]
                    return poz

        for c in range(7):
            for r in range(6-3):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r+1, c) == player and \
                        self.__board.get_poz(r+2, c) == player and self.__board.is_valid_poz(r+3, c):
                    poz = [r, c]
                    return poz

        for c in range(7 - 3):
            for r in range(6-3):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r+1, c+1) == player and \
                        self.__board.get_poz(r+2, c+2) == player and self.__board.is_valid_poz(r+3, c+3):
                    poz = [r, c+3]
                    return poz

        for c in range(7 - 3):
            for r in range(3, 6):
                if self.__board.get_poz(r, c) == player and self.__board.get_poz(r-1, c+1) == player and \
                        self.__board.get_poz(r-2, c+2) == player and self.__board.is_valid_poz(r-3, c+3):
                    poz = [r, c+3]
                    return poz

        poz = [-1, -1]
        return poz

    def draw_board(self):
        blue = (127, 127, 127)
        black = (0, 0, 0)
        red = (255, 0, 0)
        yellow = (255, 255, 0)
        square_size = 75
        width = 7 * square_size
        height = (6 + 1) * square_size
        size = (width, height)
        radius = int(square_size / 2 - 5)
        screen = pygame.display.set_mode(size)

        for c in range(7):
            for r in range(6):
                pygame.draw.rect(screen, blue, (c * square_size, r * square_size + square_size, square_size,
                                                square_size))
                pygame.draw.circle(screen, black, (
                    int(c * square_size + square_size / 2), int(r * square_size + square_size +
                                                                square_size / 2)), radius)

        for c in range(7):
            for r in range(6):
                if self.__board.get_poz(r, c) == 1:
                    pygame.draw.circle(screen, red, (
                        int(c * square_size + square_size / 2), height - int(r * square_size +
                                                                             square_size / 2)), radius)
                elif self.__board.get_poz(r, c) == 2:
                    pygame.draw.circle(screen, yellow, (
                        int(c * square_size + square_size / 2), height - int(r * square_size +
                                                                             square_size / 2)), radius)
        pygame.display.update()

    def check_full(self):
        for c in range(7):
            for r in range(6):
                if self.__board.get_poz(r, c) == 0:
                    return False
        return True

    def ai(self):
        poz = self.almost_winning_move(2)
        if poz[0] != -1 and poz[1] != -1:
            return poz[1]
        else:
            for c in range(7):
                for r in range(5):
                    if c == 0 and self.__board.get_poz(r, c) == 2:
                        if self.__board.is_valid_poz(r+1, c):
                            return c
                        elif self.__board.is_valid_poz(r+1, c+1) or self.__board.is_valid_poz(r, c+1):
                            return c + 1
                    elif c == 6 and self.__board.get_poz(r, c) == 2:
                        if self.__board.is_valid_poz(r+1, c):
                            return c
                        elif self.__board.is_valid_poz(r, c-1) or self.__board.is_valid_poz(r+1, c-1):
                            return c - 1
                    elif self.__board.get_poz(r, c) == 2:
                        if self.__board.is_valid_poz(r+1, c):
                            return c
                        elif self.__board.is_valid_poz(r+1, c+1) or self.__board.is_valid_poz(r, c+1):
                            return c + 1
                        elif self.__board.is_valid_poz(r, c-1) or self.__board.is_valid_poz(r+1, c-1):
                            return c - 1
            c = randint(0, 6)
            return c

    def print_board(self):
        self.__board.print_board()
