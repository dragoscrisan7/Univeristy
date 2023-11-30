package com.example.mobileapplicationproject.storage.structure

import androidx.lifecycle.ViewModel
import androidx.compose.runtime.mutableStateOf
import com.example.mobileapplicationproject.data.goal.Goal

class GoalViewModel : ViewModel() {
    private val goals: MutableList<Goal> = mutableListOf()
    private val goalsState = mutableStateOf<List<Goal>>(emptyList())
    private var lastAssignedId = 0

    init {
        // Initialize with some example goals
        addGoal(Goal(1,"Learn a new language", "Become fluent in Spanish", "2024-12-31", true, listOf("Complete Duolingo lessons", "Practice speaking with native speakers")))
        addGoal(Goal(2,"Exercise regularly", "Stay fit and healthy", "2024-06-30", false, listOf("Run 5 miles a week", "Strength training")))
    }

    fun getNumberOfGoals(): Int {
        return goals.size
    }

    fun getGoals(): List<Goal> {
        goalsState.value = goals
        return goals
    }

    fun addGoal(goal: Goal) {
        // Check if a goal with the same title already exists
        val existingGoal = goals.find { it.title == goal.title }
        if (existingGoal == null) {
            goals.add(goal)
            goalsState.value = goals
            lastAssignedId++
        }
    }

    fun getNewGoalId(): Int {
        return lastAssignedId
    }

    fun getGoalId(title: String): Int{
        return goals.indexOfFirst { it.title == title }
    }

    fun updateGoal(updatedGoal: Goal) {
        val index = updatedGoal.id
        if (index >= 0) {
            goals[index] = updatedGoal
            goalsState.value = goals
        }
    }

    fun deleteGoal(title: String) {
        goals.removeAll { it.title == title }
        goalsState.value = goals
    }

    fun getGoalByTitle(title: String): Goal? {
        return goals.firstOrNull { it.title == title }
    }
}