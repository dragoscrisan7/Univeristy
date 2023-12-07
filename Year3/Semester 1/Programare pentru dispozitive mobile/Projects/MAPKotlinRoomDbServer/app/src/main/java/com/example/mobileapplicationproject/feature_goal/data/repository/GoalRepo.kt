package com.example.mobileapplicationproject.feature_goal.data.repository

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import kotlinx.coroutines.flow.Flow

interface GoalRepo {
    fun getAllGoals(): Flow<List<GoalEntity>>

    suspend fun getGoalByTitle(title: String): GoalEntity?

    suspend fun insertGoal(goal: GoalEntity)

    suspend fun deleteGoal(goal: GoalEntity)

    suspend fun updateGoal(goal: GoalEntity)

}