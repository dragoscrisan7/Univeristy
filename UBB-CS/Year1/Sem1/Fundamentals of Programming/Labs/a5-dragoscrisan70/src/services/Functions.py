import copy

from src.domain.Students import Student


class Functions:
    def __init__(self):
        self.students_list = []
        self.stack_list = []

    def add_student(self, a, b, c):
        """
        adds a student to the list of students
        :param a: integer, unique
        :param b: string
        :param c: positive integer
        :return:
        """
        self.students_list.append(Student(a, b, c))
        self.generate_copy()

    def get_students(self):
        return self.students_list

    def generate_students(self):
        """
        fills the list with the 10 programmatically generated entries
        :return:
        """
        self.students_list.append(Student(635, 'David', 128))
        self.students_list.append(Student(654, 'Darius', 911))
        self.students_list.append(Student(874, 'Marcel', 654))
        self.students_list.append(Student(139, 'Pavel', 911))
        self.students_list.append(Student(823, 'Andrei', 645))
        self.students_list.append(Student(123, 'Diego', 314))
        self.students_list.append(Student(109, 'Maria', 138))
        self.students_list.append(Student(238, 'Vlad', 745))
        self.students_list.append(Student(218, 'Antonio', 911))
        self.students_list.append(Student(456, 'Tudor', 326))
        self.aux = copy.deepcopy(self.students_list)
        self.stack_list.append(self.aux)

    def delete_students(self, n):
        """
        delets all students that are in the 'n' group
        :param n: positive integer
        :return:
        """
        a = -1
        for students in self.students_list:
            a = a + 1
            if int(students.get_group) == int(n):
                del self.students_list[a]
        self.generate_copy()

    def generate_copy(self):
        """
        creates the history of lists of students, used by the delete history function
        :return:
        """
        self.aux = copy.deepcopy(self.students_list)
        self.stack_list.append(self.aux)

    def delete_history(self):
        """
        deletes the last element of the history of lists of students
        :return:
        """
        if not self.stack_list:
            raise ValueError('There is nothing to delete')
        else:
            self.stack_list.pop()
            self.students_list = copy.deepcopy(self.stack_list[len(self.stack_list)-1])


def test_add():
    newFunc = Functions()
    newFunc.add_student(123, 'Ari', 123)
    test_list = newFunc.get_students()
    student = test_list[0]
    assert int(student.get_id) == 123 and student.get_group == 123 and student.get_name == 'Ari'


def test_del():
    newFunc = Functions()
    newFunc.add_student(123, 'Ab', 123)
    newFunc.add_student(123, 'Ad', 124)
    newFunc.add_student(123, 'Ac', 123)
    test_list = newFunc.get_students()
    newFunc.delete_students(123)
    assert len(test_list) == 1
    student = test_list[0]
    assert int(student.get_id) == 123 and student.get_group == 124 and student.get_name == 'Ad'


def test_del_history():
    newFunc = Functions()
    newFunc.add_student(123, 'Ab', 123)
    newFunc.add_student(123, 'Ad', 124)
    student1 = newFunc.stack_list[len(newFunc.stack_list) - 1]
    newFunc.delete_history()
    student2 = newFunc.stack_list[len(newFunc.stack_list) - 1]
    assert student1 != student2


def tests():
    test_add()
    test_del()
    test_del_history()

