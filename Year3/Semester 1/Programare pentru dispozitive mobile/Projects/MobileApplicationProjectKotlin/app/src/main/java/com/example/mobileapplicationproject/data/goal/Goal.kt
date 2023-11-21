package com.example.mobileapplicationproject.data.goal

data class Goal(
    val id: Int,
    val title: String,
    val description: String,
    val deadline: String,
    val isPrivate: Boolean,
    val miniGoals: List<String> // List of sub-goals or steps
)