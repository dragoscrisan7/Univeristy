package com.example.mobileapplicationproject.feature_goal.data.repository

import android.content.Context
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.os.Build
import com.example.mobileapplicationproject.feature_goal.data.db.GoalDao
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import dagger.hilt.android.qualifiers.ApplicationContext
import kotlinx.coroutines.flow.Flow
import javax.inject.Inject

class GoalRepoImpl @Inject constructor(
    private val dao: GoalDao,
    private val goalService: GoalService,
    @ApplicationContext private val context: Context
) : GoalRepo {
    override fun getAllGoals(): Flow<List<GoalEntity>> {
        return dao.getAllGoals()
    }

    override suspend fun getGoalByTitle(title: String): GoalEntity? {
        return dao.getGoalByTitle(title)
    }

    override suspend fun insertGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
        val goal2 = dao.getGoalByTitle(goal.title)
        if(goal2 != null && isNetworkAvailable()) {
            goalService.insertGoal(goal2.id, goal)
        }
    }

    override suspend fun deleteGoal(goal: GoalEntity) {
        dao.deleteGoal(goal)
        if(isNetworkAvailable()) {
            goalService.deleteGoal(goal.id)
        }
    }

    override suspend fun updateGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
        if(isNetworkAvailable()) {
            goalService.updateGoal(goal.id, goal)
        }
    }

    suspend fun isNetworkAvailable(): Boolean {
        val connectivityManager =
            context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            val networkCapabilities = connectivityManager.activeNetwork ?: return false
            val activeNetwork =
                connectivityManager.getNetworkCapabilities(networkCapabilities) ?: return false

            return activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) ||
                    activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR) ||
                    activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_ETHERNET)
        } else {
            val activeNetworkInfo = connectivityManager.activeNetworkInfo
            return activeNetworkInfo != null && activeNetworkInfo.isConnected
        }
    }
}