from texttable import Texttable
from random import randint

class Service:

    def __init__(self, repository, validator):
        self.__repository = repository
        self.__validator = validator

    def table_print(self):
        table = Texttable()
        table.header([X for X in range(0, 8)])
        t = self.__repository.get_table()
        letter = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
        index = 0
        for row in t:
            table.add_row([letter[index]] + row)
            index += 1
        return table.draw()

    def cheat(self):
        table = Texttable()
        table.header([X for X in range(0, 8)])
        t = self.__repository.get_table()
        letter = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
        x_pos = self.__repository.get_X_positions()
        for el in x_pos:
            t[el[0]][el[1]] = 'X'
        index = 0
        for row in t:
            table.add_row([letter[index]] + row)
            index += 1
        return table.draw()

    def fire(self, coord):
        self.__validator.validate_coord(coord)
        letter = 65
        coord = [ord(coord[0]) - letter, int(coord[1]) - 1]
        p = self.__repository.fire(coord)
        return p

    def check_win(self):
        x = self.__repository.get_X_positions()
        if len(x) == 0:
            return 1
        for el in x:
            if el[0] in range(2,5) and el[1] in range(2, 5):
                return -1
        return 0

    def ai_move(self):
        x = self.__repository.get_X_positions()
        for h in range(len(x)):
            if randint(0, 1):
                self.__repository.move_same(h, x[h][2])
            else:
                self.__repository.move_same(h, x[h][2] - 1)