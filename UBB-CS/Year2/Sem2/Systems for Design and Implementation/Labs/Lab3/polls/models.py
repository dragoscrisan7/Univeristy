from django.db import models


class Group(models.Model):
    groupNr = models.IntegerField(default=921)
    specialization = models.CharField(max_length=200, default='unknown name')
    language = models.CharField(max_length=200, default='romana')
    year = models.IntegerField(default=1)

    def __str__(self) -> str:
        return self.specialization


class Student(models.Model):
    firstname = models.CharField(max_length=200)
    name = models.CharField(max_length=200)
    favoriteNumber = models.IntegerField(default=0)
    favorite_colour = models.CharField(max_length=200, default='blue')
    GroupId = models.ForeignKey(Group, related_name='students', on_delete=models.CASCADE)

    class Meta:
        unique_together = ['name', 'firstname', 'GroupId']

    def __str__(self) -> str:
        return self.name


class Teacher(models.Model):
    firstname = models.CharField(max_length=200)
    name = models.CharField(max_length=200)
    TeachingSubject = models.CharField(max_length=200)
    years_of_experience = models.IntegerField(default=0)

    def __str__(self) -> str:
        return self.firstname


class Subject(models.Model):
    subject_name = models.CharField(max_length=200)
    subject_year = models.IntegerField(default=1)

    def __str__(self) -> str:
        return self.subject_name


class Class(models.Model):
    group_id = models.ForeignKey(Group, on_delete=models.SET_NULL, blank=True, null=True)
    subject_id = models.ForeignKey(Subject, on_delete=models.SET_NULL, blank=True, null=True)
    teacher_id = models.ForeignKey(Teacher, on_delete=models.SET_NULL, blank=True, null=True)
    lesson_type = models.CharField(max_length=200)
    day = models.CharField(max_length=200)
    starting_hour = models.IntegerField(default=8)


class GroupFavoriteNumberDto:
    def __init__(self, group_id, group_specialization, average_favorite_number):
        self.group_id = group_id
        self.group_specialization = group_specialization
        self.average_favorite_number = average_favorite_number


class TeacherNrOfClasses:
    def __init__(self, teacher_id, teacher_firstname, teaching_subject, nr_of_classes):
        self.teacher_id = teacher_id
        self.teacher_firstname = teacher_firstname
        self.teaching_subject = teaching_subject
        self.nr_of_classes = nr_of_classes
