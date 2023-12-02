package com.example.mobileapplicationproject.di

import com.example.mobileapplicationproject.feature_goal.data.service.GoalService
import com.google.gson.Gson
import com.google.gson.GsonBuilder
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object NetworkModule {

    private const val BASE_URL = "http://127.0.0.1:5000" // Replace with your actual base URL

    @Provides
    @Singleton
    fun provideGson(): Gson {
        return GsonBuilder().create()
    }
    @Provides
    @Singleton
    fun provideRetrofit(gson: Gson): Retrofit {
        val interceptor = HttpLoggingInterceptor()
        interceptor.setLevel(HttpLoggingInterceptor.Level.BODY)  // Add this line for logging

        return Retrofit.Builder()
            .baseUrl(BASE_URL)
            .addConverterFactory(GsonConverterFactory.create(gson))
            .client(
                OkHttpClient.Builder().addInterceptor(interceptor).build()
            )  // Add this line for logging
            .build()
    }

    @Provides
    @Singleton
    fun provideGoalService(retrofit: Retrofit): GoalService {
        return retrofit.create(GoalService::class.java)
    }

}