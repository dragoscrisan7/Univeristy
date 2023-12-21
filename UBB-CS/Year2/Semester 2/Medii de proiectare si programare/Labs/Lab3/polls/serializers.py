from rest_framework import serializers
from .models import Student, Group, Teacher, Subject, Class


class DynamicFieldsModelSerializer(serializers.ModelSerializer):
    """
    A ModelSerializer that takes an additional `fields` argument that
    controls which fields should be displayed.
    """

    def __init__(self, *args, **kwargs):
        # Don't pass the 'fields' arg up to the superclass
        fields = kwargs.pop('fields', None)

        # Instantiate the superclass normally
        super().__init__(*args, **kwargs)

        if fields is not None:
            # Drop any fields that are not specified in the `fields` argument.
            allowed = set(fields)
            existing = set(self.fields)
            for field_name in existing - allowed:
                self.fields.pop(field_name)


class StudentSerializer(DynamicFieldsModelSerializer):
    class Meta:
        model = Student
        fields = ('id', 'firstname', 'name', 'favoriteNumber', 'favorite_colour', 'GroupId')


class GroupSerializer(DynamicFieldsModelSerializer):
    students = StudentSerializer(read_only=True, many=True, fields=('id', 'firstname', 'name'))

    class Meta:
        model = Group
        fields = ('id', 'groupNr', 'specialization', 'language', 'year', 'students')


class TeacherSerializer(DynamicFieldsModelSerializer):
    class Meta:
        model = Teacher
        fields = ('id', 'firstname', 'name', 'TeachingSubject', 'years_of_experience')


class SubjectSerializer(DynamicFieldsModelSerializer):
    class Meta:
        model = Subject
        fields = ('id', 'subject_name', 'subject_year')


class ClassSerializer(DynamicFieldsModelSerializer):
    class Meta:
        model = Class
        fields = ('id', 'group_id', 'subject_id', 'teacher_id', 'lesson_type', 'day', 'starting_hour')


class GroupFavoriteNumberSerializer(serializers.Serializer):
    group_id = serializers.IntegerField()
    group_specialization = serializers.CharField()
    average_favorite_number = serializers.FloatField(default=0)


class TeacherNrOfClassesSerializer(serializers.Serializer):
    id = serializers.IntegerField()
    firstname = serializers.CharField()
    TeachingSubject = serializers.CharField()
    nr_of_classes = serializers.IntegerField(default=0)
