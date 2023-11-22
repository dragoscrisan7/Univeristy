package com.example.mobileapplicationproject.feature_goal.data.model

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "goals") // Define the table name if you want to customize it
data class GoalEntity(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0, // Room will auto-generate IDs if set to true
    val title: String,
    val description: String,
    val deadline: String,
    val isPrivate: Boolean,
    val miniGoals: List<String>
)