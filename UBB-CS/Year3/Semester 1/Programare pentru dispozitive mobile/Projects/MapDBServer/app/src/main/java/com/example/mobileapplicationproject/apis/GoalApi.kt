package com.example.mobileapplicationproject.apis

import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object GoalApi {
    private const val BASE_URL = " http://10.0.2.2:8085"
    private val retrofit = Retrofit.Builder()
        .addConverterFactory(GsonConverterFactory.create())
        .baseUrl(BASE_URL)
        .build()
    val retrofitService: GoalService by lazy {
        retrofit.create(GoalService::class.java)
    }
}