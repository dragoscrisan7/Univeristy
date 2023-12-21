from django.shortcuts import get_object_or_404
from django_filters.rest_framework import DjangoFilterBackend
from rest_framework.response import Response

from django.db.models import Avg, Count
from .models import Student, Group, Teacher, Subject, Class, GroupFavoriteNumberDto
from .serializers import StudentSerializer, GroupSerializer, TeacherSerializer, SubjectSerializer, ClassSerializer
from .serializers import GroupFavoriteNumberSerializer, TeacherNrOfClassesSerializer
from rest_framework import generics, status, filters


class StudentList(generics.ListCreateAPIView):
    queryset = Student.objects.all()
    serializer_class = StudentSerializer
    filter_backends = [DjangoFilterBackend]
    filterset_fields = {'CNP': ['gt', 'lt']}
    filter_backends = [filters.OrderingFilter]
    ordering_fields = ['firstname', 'name']


class StudentDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Student.objects.all()
    serializer_class = StudentSerializer

    def get_object2(self, id):
        return get_object_or_404(self.get_queryset(), id=id)

    def retrieve(self, request, pk=None, *args, **kwargs):
        Stid = pk or request.query_params.get('id')
        student = self.get_object2(Stid)
        group = student.GroupId
        student_serializer = self.serializer_class(student, fields=('id', 'firstname', 'name', 'CNP',
                                                                    'favorite_colour'), many=False)
        group_serializer = GroupSerializer(group, read_only=True, fields=('id', 'groupNr', 'groupNickname', 'language',
                                                                          'year'))
        data = student_serializer.data
        data['group'] = group_serializer.data

        return Response(data)


class GroupList(generics.ListCreateAPIView):
    queryset = Group.objects.all()
    serializer_class = GroupSerializer

    def get_queryset(self):
        serializer_group = GroupSerializer(Group.objects.all(),
                                           fields=('id', 'groupNr', 'specialization', 'language', 'year'), many=True)
        return serializer_group.data


class GroupDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Group.objects.all()
    serializer_class = GroupSerializer


class StudentGroupUpdateView(generics.RetrieveUpdateDestroyAPIView):
    queryset = Student.objects.all()
    serializer_class = StudentSerializer

    def put(self, request, *args, **kwargs):
        group_id = self.kwargs.get('pk')
        try:
            group = Group.objects.get(id=group_id)
        except Group.DoesNotExist:
            return Response({'message': 'Group not found.'}, status=status.HTTP_404_NOT_FOUND)

        students_data = self.request.data
        for student_data in students_data:
            try:
                student = Student.objects.get(CNP=student_data['CNP'])
                student.GroupId = group
                student.save()
            except Student.DoesNotExist:
                Student.objects.create(firstname=student_data['firstname'], name=student_data['name'],
                                       CNP=student_data['CNP'],
                                       favorite_colour=student_data['favorite_colour'],
                                       GroupId=group)

        return Response({'message': 'Students moved to group successfully.'}, status=status.HTTP_200_OK)


class SubjectList(generics.ListCreateAPIView):
    queryset = Subject.objects.all()
    serializer_class = SubjectSerializer


class SubjectDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Subject.objects.all()
    serializer_class = SubjectSerializer


class TeacherList(generics.ListCreateAPIView):
    queryset = Teacher.objects.all()
    serializer_class = TeacherSerializer


class TeacherDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Teacher.objects.all()
    serializer_class = TeacherSerializer


class ClassList(generics.ListCreateAPIView):
    queryset = Class.objects.all()
    serializer_class = ClassSerializer


class ClassDetails(generics.RetrieveUpdateDestroyAPIView):
    queryset = Class.objects.all()
    serializer_class = ClassSerializer


class GroupFavoriteNumberView(generics.ListAPIView):
    serializer_class = GroupFavoriteNumberSerializer

    def get_queryset(self):
        # Query all the groups with their respective students' favoriteNumber
        queryset = Group.objects.annotate(
            average_favorite_number=Avg('students__favoriteNumber', default=0)
        ).all()

        # Create a list of DTOs containing the group ID, specialization, and average favoriteNumber
        dto_list = []
        for group in queryset:
            dto = GroupFavoriteNumberDto(
                group_id=group.id,
                group_specialization=group.specialization,
                average_favorite_number=group.average_favorite_number
            )
            dto_list.append(dto)

        # Sort the list of DTOs by the average favoriteNumber in ascending order
        dto_list.sort(key=lambda x: x.average_favorite_number)

        return dto_list


class TeacherNrOfClassesView(generics.ListAPIView):
    serializer_class = TeacherNrOfClassesSerializer

    def get_queryset(self):
        queryset = Teacher.objects.annotate(
            nr_of_classes=Count('class__id')
        ).order_by('-nr_of_classes')
        return queryset
