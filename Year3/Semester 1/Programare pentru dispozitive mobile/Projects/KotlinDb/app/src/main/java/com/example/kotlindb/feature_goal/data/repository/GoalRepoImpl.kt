package com.example.mobileapplicationproject.feature_goal.data.repository

import com.example.kotlindb.feature_goal.data.db.GoalDao
import com.example.kotlindb.feature_goal.data.model.GoalEntity
import kotlinx.coroutines.flow.Flow

class GoalRepoImpl(
    private val dao: GoalDao
) : GoalRepo {
    override fun getAllGoals(): Flow<List<GoalEntity>> {
        return dao.getAllGoals()
    }

    override suspend fun getGoalByTitle(title: String): GoalEntity? {
        return dao.getGoalByTitle(title)
    }

    override suspend fun insertGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
    }

    override suspend fun deleteGoal(goal: GoalEntity) {
        dao.deleteGoal(goal)
    }
}