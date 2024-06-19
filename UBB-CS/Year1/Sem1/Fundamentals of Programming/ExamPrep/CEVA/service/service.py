from texttable import Texttable
from random import randint

class Service:

    def __init__(self, repository, validator):
        self.__repository = repository
        self.__validator = validator

    def show(self):
        table = Texttable()
        t = self.__repository.get_list()
        for row in t:
            table.add_row(row)
        return table.draw()

    def add(self, data):
        self.__validator.validate_coordonate(data)
        if data[4] in 'xX':
            simbol = 'x'
        else:
            simbol = 'o'
        coord = (int(data[0]) - 1, int(data[2]) - 1, simbol)
        p = self.__repository.add(coord)
        if p == 0:
            raise ValueError

    def ai_move(self):
        simbol = self.__repository.get_simbol()
        adiacenta = [[0 for x in range(6)] for y in range(6)]
        max = 0
        posibilities = []
        for i in range(6):
            for j in range(6):
                adiacenta[i][j] = self.__repository.check_adiacenta((i,j, simbol))
                if max == adiacenta[i][j]:
                    posibilities.append((i, j))
                if max < adiacenta[i][j]:
                    posibilities.clear()
                    posibilities.append((i, j))
                    max = adiacenta[i][j]
        if len(posibilities) == 1:
            index = 0
        else:
            print('sex', len(posibilities))
            index = randint(1, len(posibilities))
            index -= 1
        coord = (posibilities[index][0], posibilities[index][1], simbol)
        print(coord)
        print (self.__repository.add(coord))

    def check_win(self):
        for i in range(6):
            for j in range(6):
                if self.__repository.check_lose((i, j)):
                    return -1
        if self.__repository.check_win():
            return 1
        return 0