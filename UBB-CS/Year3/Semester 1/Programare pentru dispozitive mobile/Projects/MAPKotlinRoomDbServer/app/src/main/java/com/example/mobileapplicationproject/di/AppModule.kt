package com.example.mobileapplicationproject.di

import android.content.Context
import androidx.room.Room
import com.example.mobileapplicationproject.feature_goal.data.db.GoalDatabase
import com.example.mobileapplicationproject.feature_goal.data.db.OfflineCommandDatabase
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepoImpl
import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import com.example.mobileapplicationproject.feature_goal.data.use_cases.AddGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.DeleteGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GetGoal
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GetGoals
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GoalUseCases
import com.example.mobileapplicationproject.feature_goal.data.use_cases.NetworkReconnected
import com.example.mobileapplicationproject.feature_goal.data.use_cases.UpdateGoal
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
    fun provideContext(@ApplicationContext context: Context): Context {
        return context
    }

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
    fun provideOfflineCommandDatabase(@ApplicationContext context: Context): OfflineCommandDatabase {
        return Room.databaseBuilder(
            context,
            OfflineCommandDatabase::class.java,
            "offline_commands_db"
        ).build()
    }


    @Provides
    @Singleton
    fun provideGoalRepository(
        db: GoalDatabase,
        goalService: GoalService,
        oCdb : OfflineCommandDatabase,
        @ApplicationContext context: Context
    ): GoalRepo {
        return GoalRepoImpl(db.goalDao, goalService, oCdb.oCdao, context)
    }

    @Provides
    @Singleton
    fun provideGoalUseCases(repository: GoalRepo): GoalUseCases{
        return GoalUseCases(
            getGoals = GetGoals(repository),
            deleteGoal = DeleteGoal(repository),
            addGoal = AddGoal(repository),
            getGoal = GetGoal(repository),
            updateGoal = UpdateGoal(repository),
            networkReconnected = NetworkReconnected(repository)
        )
    }
}