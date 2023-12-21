from django.db import models


class Student(models.Model):
    firstname = models.CharField(max_length=200)
    name = models.CharField(max_length=200)
    group = models.IntegerField(default=921)
    favorite_colour = models.CharField(max_length=200, default='blue')

    def __str__(self) -> str:
        return self.name