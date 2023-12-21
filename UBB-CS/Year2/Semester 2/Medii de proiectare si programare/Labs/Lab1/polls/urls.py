from django.urls import path
from rest_framework.urlpatterns import format_suffix_patterns

from . import views

urlpatterns = [
	path('students/', views.StudentList.as_view()),
	path('students/<int:pk>/', views.StudentDetails.as_view())
]

