package com.example.mobileapplicationproject.feature_goal.ui_layer.goals

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder
import com.example.mobileapplicationproject.feature_goal.data.util.OrderType

data class GoalsState(
    val goals: List<GoalEntity> = emptyList(),
    val goalOrder: GoalOrder = GoalOrder.Title(OrderType.Descending),
    val isOrderSectionVisible: Boolean = false,
    val goal: GoalEntity? = null
)