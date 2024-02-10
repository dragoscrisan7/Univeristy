package com.example.mobileapplicationproject.feature_goal.data.db

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import com.example.mobileapplicationproject.feature_goal.data.model.Converters
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity


@Database(
    entities = [GoalEntity::class],
    version = 1,
    exportSchema = false
)
@TypeConverters(Converters::class)
abstract class GoalDatabase: RoomDatabase() {

    abstract val goalDao: GoalDao
}