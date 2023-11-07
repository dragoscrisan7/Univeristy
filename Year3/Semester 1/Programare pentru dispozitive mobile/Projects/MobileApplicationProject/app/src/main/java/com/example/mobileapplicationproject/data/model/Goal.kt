package com.example.mobileapplicationproject.data.model

import java.util.Date

data class Goal(
    val title: String,
    val description: String,
    val deadline: String,
    val isPrivate: Boolean,
    val miniGoals: List<String> // List of sub-goals or steps
)