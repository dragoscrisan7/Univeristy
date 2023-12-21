package com.example.mobileapplicationproject.apis

import com.example.mobileapplicationproject.model.Goal
import retrofit2.Call
import retrofit2.http.*

interface GoalService {
    @GET("/goals/{id}")
    fun retrieveGoal(@Path("id") id: Int) : Call<Goal>
    @GET("/goals")
    fun retrieveAllStories() : Call<List<Goal>>
    @DELETE("/goals/{id}")
    fun deleteGoal(@Path("id") id: Long) : Call<Goal>
    @POST("/goals")
    fun createGoal(@Body story: Goal) : Call<Goal>
    @PUT("/goals/{id}")
    fun updateGoal(@Path("id") id: Long, @Body story: Goal) : Call<Goal>
}