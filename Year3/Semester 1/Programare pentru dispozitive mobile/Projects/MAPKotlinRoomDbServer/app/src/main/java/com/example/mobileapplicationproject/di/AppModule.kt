package com.example.mobileapplicationproject.di

import android.content.Context
import androidx.room.Room
import com.example.mobileapplicationproject.feature_goal.data.db.GoalDatabase
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepoImpl
import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import com.example.mobileapplicationproject.feature_goal.data.use_cases.AddGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.DeleteGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GetGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GetGoals
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GoalUseCases
import com.example.mobileapplicationproject.feature_goal.data.use_cases.SyncWithRemote
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object AppModule {

    @Provides
    @Singleton
    fun provideGoalDatabase(@ApplicationContext context: Context): GoalDatabase {
        return Room.databaseBuilder(
            context,
            GoalDatabase::class.java,
            "goals_db"
        ).build()
    }

    @Provides
    @Singleton
    fun provideGoalRepository(db: GoalDatabase, goalService: GoalService): GoalRepo {
        return GoalRepoImpl(db.goalDao, goalService)
    }

    @Provides
    @Singleton
    fun provideGoalUseCases(repository: GoalRepo): GoalUseCases{
        return GoalUseCases(
            getGoals = GetGoals(repository),
            deleteGoal = DeleteGoal(repository),
            addGoal = AddGoal(repository),
            getGoal = GetGoal(repository),
            updateGoal = AddGoal(repository),
            syncWithRemote = SyncWithRemote(repository)
        )
    }
}