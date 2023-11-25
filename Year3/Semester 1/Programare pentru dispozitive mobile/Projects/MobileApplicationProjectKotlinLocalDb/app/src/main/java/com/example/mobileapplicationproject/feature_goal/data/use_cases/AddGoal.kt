package com.example.mobileapplicationproject.feature_goal.data.use_cases

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.model.InvalidGoalException
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo

class AddGoal(
    private val repository: GoalRepo
) {
    @Throws(InvalidGoalException::class)
    suspend operator fun invoke(goal: GoalEntity){
        if(goal.title.isBlank()) {
            throw InvalidGoalException("The title of the goal cant be empty")
        }
        if(goal.description.isBlank()) {
            throw InvalidGoalException("The description of the goal cant be empty")
        }
        repository.insertGoal(goal)
    }
}