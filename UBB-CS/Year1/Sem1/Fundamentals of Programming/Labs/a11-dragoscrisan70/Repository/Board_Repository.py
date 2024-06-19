from Domain.Board import Board


class Board_Repo:
    def __init__(self):
        self.__board = Board()

    def is_valid_poz(self, row, column):
        if column < 0 or column > 6:
            raise ValueError("Position outside board")
        return self.__board.get_poz(row, column) == 0

    def get_next_valid_poz(self, column):
        if column < 0 or column > 6:
            raise ValueError("Position outside board")
        for r in range(6):
            if self.__board.get_poz(r, column) == 0:
                return r

        return -1

    def print_board(self):
        self.__board.print_board()

    def get_poz(self, row, column):
        return self.__board.get_poz(row, column)

    def set_poz(self, row, column, player):
        self.__board.set_poz(row, column, player)
