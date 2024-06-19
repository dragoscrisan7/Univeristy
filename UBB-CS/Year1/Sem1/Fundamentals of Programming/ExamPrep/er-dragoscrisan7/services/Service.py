from texttable import Texttable
from random import randint


class service:
    def __init__(self, repo, vali):
        self.__repo = repo
        self.__vali = vali

    def show(self):
        """
        function for printing the texttable
        :return: the texttable so that it can be printed in ui
        """
        table = Texttable()
        t = self.__repo.get_list()
        for row in t:
            table.add_row(row)
        return table.draw()

    def add(self, cmd):
        """
        function for adding the player's mve
        :param cmd: the command used by the player, which must have the format figure + , + figure + , + symbol
        """
        self.__vali.vali_coord(cmd)
        if cmd[4] == 'x' or cmd[4] == 'X':
            symbol = 'x'
        else:
            symbol = 'o'
        coord = (int(cmd[0]) - 1, int(cmd[2]) - 1, symbol)
        p = self.__repo.add(coord)
        if p == 0:
            raise ValueError

    def ai_move(self):
        """
        code for the move that the computer makes, it first gets the most used symbol and then searches for a place
        with many adjacent symbols just like his and places it on one of those positions
        :return: the coordinates
        """
        symbol = self.__repo.get_symbol()
        adjacent = [[0 for _ in range(6)] for _ in range(6)]
        maximum = 0
        possibilities = []
        for i in range(6):
            for j in range(6):
                adjacent[i][j] = self.__repo.check_adjacent((i, j, symbol))
                if maximum == adjacent[i][j]:
                    possibilities.append((i, j))
                if maximum < adjacent[i][j]:
                    possibilities.clear()
                    possibilities.append((i, j))
                    maximum = adjacent[i][j]
        if len(possibilities) == 1:
            index = 0
        else:
            index = randint(1, len(possibilities))
            index -= 1
        coord = (possibilities[index][0], possibilities[index][1], symbol)
        self.__repo.add(coord)

    def check_win(self):
        """
        checks if the game is over and the player or the computer won
        :return: 0 if the player lost and 1 if he won
        """
        for i in range(6):
            for j in range(6):
                if self.__repo.check_lose((i, j)):
                    return -1
        if self.__repo.check_win():
            return 1
        return 0
