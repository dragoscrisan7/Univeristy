package com.example.mobileapplicationproject.feature_goal.data.service

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface GoalService {
    @GET("goals")
    suspend fun getAllGoals(): List<GoalEntity>

    @GET("goals/{id}")
    suspend fun getGoalById(@Path("id") id: Int): GoalEntity?

    @POST("/add_goal/{id}")
    @Headers("Content-Type: application/json")
    suspend fun insertGoal(@Path("id") id: Int, @Body goal: GoalEntity)

    @DELETE("goals/{id}")
    suspend fun deleteGoal(@Path("id") id: Int)

    @PUT("/update_goal/{id}")
    @Headers("Content-Type: application/json")
    suspend fun updateGoal(@Path("id") id: Int, @Body goal: GoalEntity)
}
