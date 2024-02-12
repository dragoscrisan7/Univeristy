from random import randint
from copy import deepcopy

class Repository:

    def __init__(self):
        self.__list = [[' ' for x in range(7)] for y in range(7)]
        self.__list[3][3] = 'E'
        self.__X_positions = []
        self.__initialize()

    def get_table(self):
        return deepcopy(self.__list)

    def __check_star(self, coord):
        row = coord[0]
        column = coord[1]

        if self.__list[row][column] == '*' or self.__list[row][column] == 'E':
            return 0

        for p in range(-1, 2):
            for q in range(-1, 2):
                i = row + p
                j = column + q
                if i in range(0,7) and j in range(0,7):
                    if self.__list[i][j] == '*':
                        return 0
        return 1


    def __check_ship(self, coord):
        row = coord[0]
        column = coord[1]
        print(coord)

        if self.__list[row][column] != ' ':
            return 0
        for x in self.__X_positions:
            if x[0] == row and x[1] == column:
                return 0

        return 1


    def __initialize(self):

        for i in range(0, 7):
            posibilities = []
            for j in range(0, 7):
                if self.__check_star((i, j)):
                    posibilities.append((i, j))
            index = randint(0, len(posibilities) - 1)
            i = posibilities[index][0]
            j = posibilities[index][1]
            self.__list[i][j] = '*'

        posibilities = []
        for i in range(0,7):
            for j in range(0,7):
                if self.__check_star((i, j)):
                    posibilities.append((i,j))

        index = randint(0, len(posibilities)-1)
        i = posibilities[index][0]
        j = posibilities[index][1]
        self.__list[i][j] = '*'

        posibilities = []
        for i in range (0,7):
            if self.__check_ship((i, 0)):
                posibilities.append((i, 0, 3))
            if self.__check_ship((i, 6)):
                posibilities.append((i, 6, 3))

        for j in range (1,6):
            if self.__check_ship((0, j)):
                posibilities.append((0, j, 3))
            if self.__check_ship((6, j)):
                posibilities.append((6, j, 3))

        index = randint(0, len(posibilities)-1)
        coord = posibilities[index]
        posibilities.pop(index)
        self.__X_positions.append(coord)
        index = randint(0, len(posibilities) - 1)
        coord = posibilities[index]
        self.__X_positions.append(coord)


    def get_X_positions(self):
        return self.__X_positions

    def fire(self, coord):
        i = coord[0]
        j = coord[1]
        self.__list[i][j] = '-'
        for h in range(0, len(self.__X_positions)):
            el = self.__X_positions[h]
            if i == el[0] and j == el[1]:
                self.__X_positions.pop(h)
                return 1
        return 0

    def move_same(self, h, d):
        x = self.__X_positions[h]
        s = 4 - d - 1
        f = 4 + d - 1
        posibilities = []
        for i in range (s,f):
            if self.__check_ship((i, s)):
                posibilities.append((i, s, 3))
            if self.__check_ship((i, f)):
                posibilities.append((i, f, 3))

        for j in range (s+1,f-1):
            if self.__check_ship((s, j)):
                posibilities.append((s, j, 3))
            if self.__check_ship((f, j)):
                posibilities.append((f, j, 3))

        index = randint(0, len(posibilities)-1)
        self.__X_positions[h] = (posibilities[index][0], posibilities[index][1], d)





