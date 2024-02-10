from django.db import models
from rest_framework.exceptions import ValidationError


class Group(models.Model):
    groupNr = models.IntegerField(default=921)
    specialization = models.CharField(max_length=200, default='unknown name')
    language = models.CharField(max_length=200, default='romana')
    year = models.IntegerField(default=1)

    def __str__(self) -> str:
        return self.specialization


class Student(models.Model):
    firstname = models.CharField(max_length=200, default="")
    name = models.CharField(max_length=200, default="")
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

    def validate_max_classes_per_day(self):
        """Ensure that a teacher is not assigned to more than 4 classes per day."""
        days = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday']
        for day in days:
            classes_for_day = self.class_set.filter(day=day)
            if len(classes_for_day) > 4:
                raise ValidationError('Teacher {} is assigned to too many classes on {}.'.format(self.firstname, day))

    def clean(self):
        if self.years_of_experience < 0:
            raise ValidationError('Years of experience must be greater than or equal to zero.')


class Subject(models.Model):
    subject_name = models.CharField(max_length=200)
    subject_year = models.IntegerField(default=1)

    def __str__(self) -> str:
        return self.subject_name


class Class(models.Model):
    DAY_CHOICES = [
        ('Monday', 'Monday'),
        ('Tuesday', 'Tuesday'),
        ('Wednesday', 'Wednesday'),
        ('Thursday', 'Thursday'),
        ('Friday', 'Friday'),
    ]
    lesson_type_choices = [('Lab', 'Lab'), ('Sem', 'Sem'), ('Course', 'Course')]

    group_id = models.ForeignKey(Group, on_delete=models.SET_NULL, blank=True, null=True)
    subject_id = models.ForeignKey(Subject, on_delete=models.SET_NULL, blank=True, null=True)
    teacher_id = models.ForeignKey(Teacher, on_delete=models.SET_NULL, blank=True, null=True)
    lesson_type = models.CharField(max_length=200, choices=lesson_type_choices)
    day = models.CharField(max_length=200, choices=DAY_CHOICES)
    starting_hour = models.IntegerField(default=8)

    def __str__(self) -> str:
        return "{} {} {} ({})".format(self.day, self.starting_hour, self.subject_id.subject_name, self.lesson_type)

    def clean(self):
        super().clean()
        if self.teacher_id:
            self.teacher_id.validate_max_classes_per_day()
        if self.day not in dict(self.DAY_CHOICES).keys():
            raise ValidationError("Invalid value for 'day'. Must be one of: {}".format(
                ', '.join(dict(self.DAY_CHOICES).keys())))
        if self.lesson_type not in dict(self.lesson_type_choices).keys():
            raise ValidationError("Invalid value for lesson_type. Must be one of: {}".format(
                ', '.join(dict(self.lesson_type_choices).keys())))


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
