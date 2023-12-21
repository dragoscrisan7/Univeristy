package com.example.mobileapplicationproject.feature_goal.data.repository

import android.content.Context
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.os.Build
import com.example.mobileapplicationproject.feature_goal.data.db.GoalDao
import com.example.mobileapplicationproject.feature_goal.data.db.OfflineCommandsDao
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.model.OfflineCommand
import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import dagger.hilt.android.qualifiers.ApplicationContext
import kotlinx.coroutines.flow.Flow
import java.io.IOException
import javax.inject.Inject

class GoalRepoImpl @Inject constructor(
    private val dao: GoalDao,
    private val goalService: GoalService,
    private val oCdao: OfflineCommandsDao,
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
        if(goal2 != null && isServerReachable()) {
            goalService.insertGoal(goal2.id, goal)
        }
        else if(goal2 != null){
            // Save the offline insert command
            val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.INSERT, goal = goal, goalId = goal2.id)
            oCdao.insertCommand(offlineCommand)
        }
    }

    override suspend fun deleteGoal(goal: GoalEntity) {
        dao.deleteGoal(goal)
        if(isServerReachable()) {
            goalService.deleteGoal(goal.id)
        }
        else {
            // Store the delete command locally when offline
            val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.DELETE, goal = goal)
            oCdao.insertCommand(offlineCommand)
        }
    }

    override suspend fun updateGoal(goal: GoalEntity) {
        dao.insertGoal(goal)
        if(isServerReachable()) {
            goalService.updateGoal(goal.id, goal)
        }
        else {
            // Store the update command locally when offline
            val offlineCommand = OfflineCommand(type = OfflineCommand.CommandType.UPDATE, goal = goal, goalId = goal.id)
            oCdao.insertCommand(offlineCommand)
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

    suspend fun isServerReachable(): Boolean {
        return try {
            val response = goalService.pingServer()
            val isReachable = response.isSuccessful

            if (isReachable) {
                processOfflineCommands()
            }

            isReachable
        } catch (e: IOException) {
            false
        }
    }

    override suspend fun processOfflineCommands() {
        // Fetch all offline commands from the database
        val offlineCommands = oCdao.getAllCommands()

        // Execute each command based on its type
        for (command in offlineCommands) {
            when (command.type) {
                OfflineCommand.CommandType.INSERT -> {
                    // Execute insert operation on the server
                    goalService.insertGoal(command.goalId ?: 0, command.goal!!)
                }
                OfflineCommand.CommandType.DELETE -> {
                    // Execute delete operation on the server
                    goalService.deleteGoal(command.goal!!.id)
                }
                OfflineCommand.CommandType.UPDATE -> {
                    // Execute update operation on the server
                    goalService.updateGoal(command.goalId ?: 0, command.goal!!)
                }
            }
        }

        // Clear the processed commands from the database
        oCdao.clearCommands()
    }

}