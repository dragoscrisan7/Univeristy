package com.example.mobileapplicationproject.feature_goal.data.service

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface GoalService {
    @GET("/goals")
    suspend fun getAllGoals(): List<GoalEntity>

    @GET("/goals/{id}")
    suspend fun getGoalById(@Path("id") id: Int): GoalEntity?

    @POST("/add_goal")
    suspend fun insertGoal(@Body goal: GoalEntity)

    @DELETE("/goals/{id}")
    suspend fun deleteGoal(@Path("id") id: Int)

    @PUT("/goals/{id}")
    suspend fun updateGoal(@Path("id") id: Int, @Body goal: GoalEntity)
}
