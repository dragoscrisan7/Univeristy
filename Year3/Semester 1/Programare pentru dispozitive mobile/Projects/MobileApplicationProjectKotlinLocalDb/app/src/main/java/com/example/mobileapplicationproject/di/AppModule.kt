package com.example.mobileapplicationproject.di

import android.app.Application
import androidx.room.Room
import com.example.mobileapplicationproject.feature_goal.data.db.GoalDatabase
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepoImpl
import com.example.mobileapplicationproject.feature_goal.data.use_cases.DeleteGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GetGoals
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GoalUseCases
import com.google.android.datatransport.runtime.dagger.Module
import com.google.android.datatransport.runtime.dagger.Provides
import dagger.hilt.InstallIn
import javax.inject.Singleton

@Module
@InstallIn(Singleton::class)
object AppModule {

    @Provides
    @Singleton
    fun provideGoalDatabase(app: Application): GoalDatabase{
        return Room.databaseBuilder(
            app,
            GoalDatabase::class.java,
            GoalDatabase.DATABASE_NAME
        ).build()
    }

    @Provides
    @Singleton
    fun provideGoalRepository(db: GoalDatabase): GoalRepo{
        return GoalRepoImpl(db.goalDao)
    }

    @Provides
    @Singleton
    fun provideGoalUseCases(repository: GoalRepo): GoalUseCases{
        return GoalUseCases(
            getGoals = GetGoals(repository),
            deleteGoal = DeleteGoal(repository)
        )
    }
}