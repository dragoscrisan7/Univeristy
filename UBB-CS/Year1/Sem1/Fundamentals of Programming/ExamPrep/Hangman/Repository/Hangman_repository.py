from random import randint


class repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__repo = []
        self.update()

    def update(self):
        """
        appends in the repository list with the sentences in the file
        """
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                self.__repo.append(line)

    def add(self, sentence):
        """
        adds a sentence to the file and the repository list
        :param sentence: receives a sentence from the controller
        """
        for element in self.__repo:
            if element == sentence:
                raise ValueError
        with open(self.__filename, "a") as f:
            f.write(sentence)
            f.write("\n")
        self.__repo.append(sentence)

    def select_sentence(self):
        """
        selects one random sentence from the sentences in the repository
        :return: the selected sentence
        """
        x = randint(0, len(self.__repo)-1)

        return self.__repo[x]
