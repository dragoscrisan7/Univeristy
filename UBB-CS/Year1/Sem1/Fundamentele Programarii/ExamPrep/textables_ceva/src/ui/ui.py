
class Interface:

    def __init__(self, service):
        self.__service = service

    def run(self):
        self.__table_print()
        while True:
            try:

                command = input("Give Command: ")
                command = command.split(" ", maxsplit= 1)
                if command[0] == 'exit':
                    return
                elif command[0] == '':
                    continue
                elif command[0] == 'cheat':
                    self.__cheat()
                elif command[0] == 'fire':
                    p = self.__service.fire(command[1])
                    self.__service.ai_move()
                    self.__table_print()
                    if p == 1:
                        print("HIT!")
                    else:
                        print("MISS!")
                else:
                    print("Give Valid Command!!")
                p = self.__service.check_win()
                if p == 1:
                    print('You Won')
                    return
                elif p == -1:
                    print('You Lost')
                    return

            except ValueError:
                print("Give valid coordonates!")

    def __table_print(self):
        print(self.__service.table_print())

    def __cheat(self):
        print(self.__service.cheat())
