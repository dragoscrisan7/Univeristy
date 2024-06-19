import numpy as np


class Board:
    def __init__(self):
        self.__board = np.zeros((6, 7))

    def get_poz(self, row, column):
        if row < 0 or row > 5 or column < 0 or column > 6:
            raise ValueError("Position outside board")
        return self.__board[row][column]

    def set_poz(self, row, column, player):
        if row < 0 or row > 5 or column < 0 or column > 6:
            raise ValueError("Position outside board")
        self.__board[row][column] = player

    def return_board(self):
        return self.__board

    def print_board(self):
        print(np.flip(self.__board, 0))
