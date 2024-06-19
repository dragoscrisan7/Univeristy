from copy import deepcopy

class Repository:

    def __init__(self):
        self.__list = [[' ' for x in range(6)] for y in range(6)]
        self.__x_number = 0
        self.__o_number = 0

    def get_list(self):
        return deepcopy(self.__list)

    def add(self, coord):
        if self.__list[coord[0]][coord[1]] != ' ':
            return 0
        self.__list[coord[0]][coord[1]] = coord[2]
        if coord[2] == 'x':
            self.__x_number += 1
        else:
            self.__o_number += 1
        return 1

    def get_simbol(self):
        if self.__x_number < self.__o_number:
            return 'o'
        else:
            return 'x'

    def check_adiacenta(self, coord):
        row = coord[0]
        column = coord[1]
        simbol = coord[2]
        if self.__list[row][column] != ' ':
            return -1
        out = 0
        for p in range(-1, 2):
            for q in range(-1, 2):
                i = row + p
                j = column + q
                if 0 <= i <= 5 and 0 <= j <= 5:
                    if self.__list[i][j] == simbol:
                        out += 1
        return out

    def check_win(self):
        if self.__x_number + self.__o_number == 36:
            return 1
        return 0

    def check_lose(self, coord):
        row = coord[0]
        column = coord[1]
        simbol = self.__list[row][column]
        if not simbol in 'xo':
            return 0
        moves = [(-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1)]
        for move in moves:
            c = 0
            i = row
            j = column
            while simbol == self.__list[i][j]:
                i += move[0]
                j += move[1]
                c += 1
                if c == 5:
                    return 1
                if not (i in range(6) and j in range(6)):
                    break
        return 0