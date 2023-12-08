package com.example.mobileapplicationproject.feature_goal.data.model

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "offline_commands")
data class OfflineCommand(
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    val type: CommandType,
    val goal: GoalEntity? = null,
    val goalId: Int? = null
) {
    enum class CommandType {
        INSERT, DELETE, UPDATE
    }
}