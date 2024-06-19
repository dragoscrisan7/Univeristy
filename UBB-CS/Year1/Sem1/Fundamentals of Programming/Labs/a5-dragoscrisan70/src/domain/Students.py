class Student:
    def __init__(self, studid, name, group):
        """
        The students class with the data of a student
        :param studid: integer, unique
        :param name: string
        :param group: positive integer
        """
        if type(studid) != int and type(studid) != float:
            raise ValueError('Incorrect student id')
        if type(name) != str:
            raise ValueError('Incorrect student name')
        if type(group) != int and type(group) != float and int(group) <= 0:
            raise ValueError('Incorrect student group')

        self.__stud_studid = studid
        self.__stud_name = name
        self.__stud_group = group

    @property
    def get_id(self):
        return self.__stud_studid

    @property
    def get_name(self):
        return self.__stud_name

    @property
    def get_group(self):
        return self.__stud_group

    def __str__(self):
        return "Student id: " + str(self.get_id) + ", name: " + str(self.get_name) + ", group: " + str(self.get_group)
