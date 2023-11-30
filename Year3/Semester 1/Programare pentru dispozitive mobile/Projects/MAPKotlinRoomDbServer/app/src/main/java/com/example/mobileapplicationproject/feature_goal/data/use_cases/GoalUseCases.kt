package com.example.mobileapplicationproject.feature_goal.data.use_cases

data class GoalUseCases(
    val getGoals: GetGoals,
    val deleteGoal: DeleteGoal,
    val addGoal: AddGoal,
    val getGoal: GetGoal,
    val updateGoal: AddGoal,
    val syncWithRemote: SyncWithRemote
)
