package com.example.mobileapplicationproject.feature_goal.data.repository

import com.example.mobileapplicationproject.feature_goal.data.db.GoalDao
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.first

class GoalRepoImpl(
    private val dao: GoalDao,
    private val goalService: GoalService
) : GoalRepo {
    override fun getAllGoals(): Flow<List<GoalEntity>> {
        return dao.getAllGoals()
    }

    override suspend fun getGoalByTitle(title: String): GoalEntity? {
        return dao.getGoalByTitle(title)
    }

    override suspend fun insertGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
        goalService.insertGoal(goal)
    }

    override suspend fun deleteGoal(goal: GoalEntity) {
        dao.deleteGoal(goal)
        goalService.deleteGoal(goal.id)
    }

    override suspend fun updateGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
        goalService.updateGoal(goal.id, goal)
    }

    override suspend fun syncWithRemote() {
        try {
            val localGoals = dao.getAllGoals().first()

            val remoteGoals = goalService.getAllGoals()

            for (remoteGoal in remoteGoals) {
                val existingLocalGoal = dao.getGoalByTitle(remoteGoal.title)

                if (existingLocalGoal == null) {
                    dao.insertGoal(remoteGoal)
                } else {
                    if (existingLocalGoal != remoteGoal) {
                        dao.insertGoal(remoteGoal)
                    }
                }
            }

            // Remove local goals that are not present on the server
            for (localGoal in localGoals) {
                val remoteGoal = goalService.getGoalByTitle(localGoal.title)
                if (remoteGoal == null) {
                    dao.deleteGoal(localGoal)
                }
            }

        } catch (e: Exception) {
            // Handle network or other errors
            e.printStackTrace()
        }
    }
}