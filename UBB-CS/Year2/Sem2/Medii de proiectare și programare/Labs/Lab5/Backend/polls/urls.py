from django.urls import path

from . import views

urlpatterns = [
	path('students/', views.StudentList.as_view()),
	path('students/<int:pk>/', views.StudentDetails.as_view()),
	path('groups/', views.GroupList.as_view()),
	path('groups/<int:pk>/', views.GroupDetails.as_view()),
	path('teachers/', views.TeacherList.as_view()),
	path('teachers/<int:pk>/', views.TeacherDetails.as_view()),
	path('subjects/', views.SubjectList.as_view()),
	path('subjects/<int:pk>/', views.SubjectDetails.as_view()),
	path('class/', views.ClassList.as_view()),
	path('class/<int:pk>/', views.ClassDetails.as_view()),
	path('group_favorite_numbers/', views.GroupFavoriteNumberView.as_view(), name='group_favorite_numbers'),
	path('teacher_nr_classes/', views.TeacherNrOfClassesView.as_view(), name='teacher_nr_classes'),
	path('groups/<int:pk>/students/', views.StudentGroupUpdateView.as_view()),
]

