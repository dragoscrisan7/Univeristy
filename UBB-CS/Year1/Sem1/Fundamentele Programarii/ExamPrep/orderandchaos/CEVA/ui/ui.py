
class Interface:

    def __init__(self, service):
        self.__service = service

    def run(self):
        self.__service.ai_move()
        while True:
            try:
                print(self.__service.show())
                command = input("Give Command: ")
                if command == 'exit':
                    return
                elif command == '':
                    continue
                else:
                    self.__service.add(command)
                    self.__service.ai_move()

                p = self.__service.check_win()
                if p == 1:
                    print(self.__service.show())
                    print("You Won!")
                    return
                if p == -1:
                    print(self.__service.show())
                    print("You Lost!")
                    return
            except ValueError:
                print("Give valid coordonates")



