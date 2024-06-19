from src.services.Functions import Functions, tests


class Console:
    def __init__(self):
        self._functions = Functions()

    def show_menu(self):
        print('1. Add students')
        print('2. Display list of students')
        print('3. Delete students from specified group')
        print('4. Undo')
        print('5. Close')

    def get_values(self):
        a = int(input('id: '))
        b = input('name: ')
        c = int(input('group: '))
        self._functions.add_student(a, b, c)
        print('Student succesfully added')

    def generate_students(self):
        self._functions.generate_students()

    def display_students(self):
        students = self._functions.get_students()
        for a in students:
            print(str(a))

    def delete_group(self):
        a = input('group: ')
        self._functions.delete_students(a)
        print('Student succesfully deleted')

    def undo(self):
        self._functions.delete_history()
        print('Last operation was reversed')

    def start(self):
        self.generate_students()
        tests()
        while True:
            self.show_menu()
            option = int(input('option: '))
            if option == 1:
                self.get_values()
            elif option == 2:
                self.display_students()
            elif option == 3:
                self.delete_group()
            elif option == 4:
                self.undo()
            elif option == 5:
                return
            else:
                raise ValueError('Incorrect Input')


ui = Console()
ui.start()
