package com.example.mobileapplicationproject.feature_goal.ui_layer.goals

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder

sealed class GoalsEvent{
    data class Order(val goalOrder: GoalOrder): GoalsEvent()
    data class DeleteGoal(val goal: GoalEntity): GoalsEvent()
    data class AddGoal(val goal: GoalEntity) : GoalsEvent()
    data class UpdateGoal(val goal: GoalEntity) : GoalsEvent()
    data class GetGoal(val goalTitle: String) : GoalsEvent()
    object ToggleOrderSection: GoalsEvent()
    object Sync : GoalsEvent()
}
