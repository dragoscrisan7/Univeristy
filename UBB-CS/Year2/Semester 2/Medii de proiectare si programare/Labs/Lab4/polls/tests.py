from unittest import mock

from django.test import TestCase, Client, RequestFactory

from rest_framework import status

from polls.models import Teacher, Group, Student, Class
from polls.views import GroupFavoriteNumberView, TeacherNrOfClassesView


class TeacherNrOfClassesViewTestCase(TestCase):
    def setUp(self):
        self.factory = RequestFactory()

    def test_teacher_nr_of_classes_view(self):
        teacher1 = Teacher.objects.create(firstname='John', name='Doe', TeachingSubject='Math', years_of_experience=5)
        teacher2 = Teacher.objects.create(firstname='Jane', name='Smith', TeachingSubject='English', years_of_experience=3)
        class1 = Class.objects.create(teacher_id=teacher1)
        class2 = Class.objects.create(teacher_id=teacher1)
        class3 = Class.objects.create(teacher_id=teacher2)

        request = self.factory.get('/teacher_nr_classes/')
        response = TeacherNrOfClassesView.as_view()(request)

        self.assertEqual(response.status_code, 200)
        self.assertEqual(len(response.data), 2)
        self.assertEqual(response.data[0]['firstname'], 'John')
        self.assertEqual(response.data[0]['TeachingSubject'], 'Math')
        self.assertEqual(response.data[0]['nr_of_classes'], 2)
        self.assertEqual(response.data[1]['firstname'], 'Jane')
        self.assertEqual(response.data[1]['TeachingSubject'], 'English')
        self.assertEqual(response.data[1]['nr_of_classes'], 1)


class testGroupFvNrView(TestCase):
    def setUp(self):
        self.factory = RequestFactory()

    def testGrFvNrView(self):
        group = Group.objects.create(id=1, groupNr=921, specialization='E', year=1, language='engloish')
        student_1 = Student.objects.create(name='D', favoriteNumber=4, GroupId=group)
        student_2 = Student.objects.create(name='A', favoriteNumber=2, GroupId=group)

        request = self.factory.get('/group_favorite_numbers/')
        response = GroupFavoriteNumberView.as_view()(request)

        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 1)
        self.assertEqual(response.data[0]['group_id'], group.id)
        self.assertEqual(response.data[0]['group_specialization'], group.specialization)
        self.assertEqual(response.data[0]['average_favorite_number'], 3)
