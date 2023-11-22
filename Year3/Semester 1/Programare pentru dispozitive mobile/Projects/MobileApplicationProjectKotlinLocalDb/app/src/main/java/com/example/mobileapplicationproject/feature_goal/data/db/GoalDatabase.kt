package com.example.mobileapplicationproject.feature_goal.data.db

import androidx.room.Database
import androidx.room.RoomDatabase
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity

@Database(
    entities = [GoalEntity::class],
    version = 1
)
abstract class GoalDatabase: RoomDatabase() {

    abstract val goalDao: GoalDao

    companion object {
        const val DATABASE_NAME = "goals_db"
    }
}