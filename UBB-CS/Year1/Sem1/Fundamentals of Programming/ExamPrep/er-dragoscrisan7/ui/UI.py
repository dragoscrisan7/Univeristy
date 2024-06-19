class ui:
    def __init__(self, srv):
        self.__srv = srv

    def run(self):
        while True:
            try:
                print(self.__srv.show())
                cmd = input("Command: ")
                if cmd == 'exit':
                    return
                elif cmd == '':
                    continue
                else:
                    self.__srv.add(cmd)
                    self.__srv.ai_move()

                win_condition = self.__srv.check_win()
                if win_condition == 1:
                    print(self.__srv.show())
                    print("You(chaos) Won! :)")
                    return
                if win_condition == -1:
                    print(self.__srv.show())
                    print("You Lost! Order won :((")
                    return
            except ValueError:
                print("Please give valid coordinates! Between 1 and 6 and with ',' between them")
