class ui:
    def __init__(self, srv):
        self.__srv = srv
        self.count = 0

    def run(self):
        while True:
            cmd = input("Command: ")
            parts = cmd.split(' ', 1)
            if cmd == '':
                continue
            elif cmd == 'x':
                break
            elif parts[0] == 'add':
                self.add(parts[1])
            elif parts[0] == 'start':
                self.start_game()
            else:
                break

    def add(self, sentence):
        try:
            self.__srv.add(sentence)
        except ValueError:
            print("incorrect input")

    def start_game(self):
        self.__srv.start_game()
        sentence = self.__srv.return_sentence()
        for elem in sentence:
            print(elem, end="")
        while True:
            hangman = "hangman"
            cmd = input("Letter: ")
            self.check_letter(cmd)
            sentence = self.__srv.return_sentence()
            for elem in sentence:
                print(elem, end="")
            for i in range(0, self.count):
                print(hangman[i], end="")
            print()
            if self.count == len(hangman):
                print("Game over")
                break
            if self.__srv.check_win():
                print("You won")
                self.count = 0
                break

    def check_letter(self, letter):
        try:
            if self.__srv.check_letter(letter):
                self.__srv.replace_letter(letter)
            else:
                self.count += 1
        except ValueError:
            print("Incorrect input")
        except:
            print("Letter already checked")
