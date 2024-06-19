class controller:
    def __init__(self, repo, vali):
        self.__repo = repo
        self.__vali = vali
        self.sentence = ""
        self.sentence_copy = []
        self.letter_list = []

    def add(self, sentence):
        """
        calls the function from repo to add a sentence to the file and repo
        :param sentence: receives a sentence from the ui
        """
        self.__vali.check_add(sentence)
        self.__repo.add(sentence)

    def start_game(self):
        """
        the function for the beggining of the game
        creates a copy in form of a list of the sentence
        formats the sentence copy in the hangman format(with the _ instead of the letters inside a word and that haven't
        appeared yet
        """
        self.sentence = self.__repo.select_sentence()
        self.sentence_copy = list(self.sentence)
        self.letter_list = []
        self.letter_list.append(self.sentence_copy[0])
        self.letter_list.append(self.sentence_copy[len(self.sentence_copy) - 1])

        for i in range(1, len(self.sentence_copy)-2):
            if self.sentence_copy[i-1] != ' ' and self.sentence_copy[i+1] != ' ' and self.sentence_copy[i] != ' ':
                self.sentence_copy[i] = '_'
            elif self.sentence_copy[i] != ' ':
                ok = 1
                for letter in self.letter_list:
                    if letter == self.sentence_copy[i]:
                        ok = 0
                if ok == 1:
                    self.letter_list.append(self.sentence_copy[i])

        for letter in self.letter_list:
            self.replace_letter(letter)

    def return_sentence(self):
        """
        :return: the sentence copy with the current state(the letters already guessed being replaced
        """
        return self.sentence_copy

    def replace_letter(self, letter):
        """
        searches for all appearances of the letter in the sentence and puts them instead of the '_' in the sentence copy
        :param letter: the letter guessed by the player
        """
        for i in range(1, len(self.sentence_copy)-2):
            if self.sentence[i] == letter:
                self.sentence_copy[i] = letter

    def check_letter(self, letter):
        """
        checks if the letter guessed by the player exists in the sentence
        :param letter: the letter guessed by the player
        :return: false if it doesnt exist, true if it appears at least once
        """
        self.__vali.check_letter(letter)
        for l in self.letter_list:
            if l == letter:
                raise
        for i in range(0, len(self.sentence)):
            if self.sentence[i] == letter:
                return True

        return False

    def check_win(self):
        """
        checks if the player guessed all letters and the game is won
        :return: false if the game is not won yet, true if the player won
        """
        for i in range(1, len(self.sentence_copy) - 2):
            if self.sentence_copy[i] == '_':
                return False

        return True
