class ui:

    def __init__(self, srv):
        self.srv = srv

    def run(self):
        while True:
            cmd = input("sex: ")
            cmd_name = cmd.split(' ')[0]
            if cmd_name == 'exit':
                return
            elif cmd_name == '':
                continue
            elif cmd_name == 'add':
                self.add(cmd[4:])
            elif cmd_name == 'create':
                self.create(cmd[7:])
            elif cmd_name == 'start':
                self.start(cmd[6:])
            else:
                print("please give valid command")

    def add(self, cmd):
        try:
            self.srv.add(cmd)
            print("added successfully")
        except ValueError:
            print("wrong input")
        except:
            print("id already exists")

    def create(self, cmd):
        try:
            self.srv.create(cmd)
        except ValueError:
            print("wrong input")

    def start(self, cmd):
        try:
            self.srv.start(cmd)
        except ValueError:
            print("wrong input")
