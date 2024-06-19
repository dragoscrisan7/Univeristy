from copy import deepcopy


class repository:
    def __init__(self):
        self.__list = [[' ' for _ in range(6)] for _ in range(6)]
        self.__x_count = 0
        self.__o_count = 0

    def get_list(self):
        """
        function for accessing the list storing the x,o and blank spaces
        :return: the list of the game, storing x,o and blank spaces
        """
        return deepcopy(self.__list)

    def add(self, coord):
        """
        function for adding a symbol on the specified coordinates in the list
        :param coord:coord[0] and coord[1] are the 2 coordinates at which the symbol needs to be put and coord[2]
        is the chosen symbol
        :return: 1 if the function worked correctly, for personal reasons,to print it and make sure the function worked
        """
        if self.__list[coord[0]][coord[1]] != ' ':
            return 0
        self.__list[coord[0]][coord[1]] = coord[2]
        if coord[2] == 'x':
            self.__x_count += 1
        else:
            self.__o_count += 1
        return 1

    def get_symbol(self):
        """
        function for finding which symbol appears more times so the ai can use it to try and win
        :return:symbol with most apparitions
        """
        if self.__x_count < self.__o_count:
            return 'o'
        else:
            return 'x'

    def check_adjacent(self, coord):
        """
        checks how many adjacent symbols (that are the same as the symbol from the position we are checking) there are
        :param coord: coord[0] is the row and coord[1] is the column, the coordinates of the position
        coord[2] is the symbol that is situated at that position
        :return: returns the number of adjacent symbols that are the same
        """
        row = coord[0]
        column = coord[1]
        symbol = coord[2]
        if self.__list[row][column] != ' ':
            return -1
        out = 0
        for p in range(-1, 2):
            for q in range(-1, 2):
                i = row + p
                j = column + q
                if 0 <= i <= 5 and 0 <= j <= 5:
                    if self.__list[i][j] == symbol:
                        out += 1
        return out

    def check_win(self):
        """
        checks if order/the human won
        :return: 1 if its true and he won and 0 otherwise
        """
        if self.__x_count + self.__o_count == 36:
            return 1
        return 0

    def check_lose(self, coord):
        """
        checks if the player/order lost and the computer won, by checking on rows, lines and diagonals if 5 symbols
        that are the same are one after another
        :param coord: coord[0] is the row and coord[1] is the column, the coordinates of the position
        coord[2] is the symbol that is situated at that position
        :return:
        """
        row = coord[0]
        column = coord[1]
        symbol = self.__list[row][column]
        if symbol not in 'xo':
            return 0
        moves = [(-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1)]
        for move in moves:
            c = 0
            i = row
            j = column
            while symbol == self.__list[i][j]:
                i += move[0]
                j += move[1]
                c += 1
                if c == 5:
                    return 1
                if not (i in range(6) and j in range(6)):
                    break
        return 0

    def check_wining_move(self):
        ok = 0
        for a in range(0, 1):
            for b in range(0, 5):
                symbol = self.__list[a][b]
                for c in range(a+1, a+5):
                    if self.__list[c][b] == symbol:
                        ok += 1
        if ok == 5:
            return 1
