package com.example.mobileapplicationproject.feature_goal.data.use_cases

import com.example.kotlindb.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo

class DeleteGoal(
    private val repository: GoalRepo
) {
    suspend operator fun invoke(goal: GoalEntity){
        repository.deleteGoal(goal)
    }
}