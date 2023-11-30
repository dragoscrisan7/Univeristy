package com.example.mobileapplicationproject.feature_goal.data.use_cases

import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo

class SyncWithRemote(
    private val repository: GoalRepo
) {
    suspend operator fun invoke() {
        repository.syncWithRemote()
    }
}