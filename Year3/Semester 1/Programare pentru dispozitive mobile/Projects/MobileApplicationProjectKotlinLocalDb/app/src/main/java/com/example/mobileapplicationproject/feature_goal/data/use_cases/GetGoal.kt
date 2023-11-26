package com.example.mobileapplicationproject.feature_goal.data.use_cases

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo

class GetGoal(
    private val repository: GoalRepo
) {
    suspend operator fun invoke(title: String): GoalEntity? {
        return repository.getGoalByTitle(title)
    }
}