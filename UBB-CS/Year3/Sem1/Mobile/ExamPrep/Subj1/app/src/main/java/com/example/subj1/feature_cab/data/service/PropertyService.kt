package com.example.subj1.feature_cab.data.service

import com.example.subj1.feature_cab.data.model.PropertyEntity
import retrofit2.Response
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface PropertyService {
    @GET("/listings")
    suspend fun getAllProperties(): List<PropertyEntity>

    @POST("/property")
    @Headers("Content-Type: application/json")
    suspend fun insertProperty(@Body property: PropertyEntity): Response<PropertyEntity>

    @GET("/interest")
    suspend fun getPropertyInterest(): List<PropertyEntity>

    @GET("/types")
    suspend fun getPropertyTypes(): List<String>

    @GET("/property/{id}")
    suspend fun getPropertyById(@Path("id") id: Long): PropertyEntity

    @PUT("/register/{type}")
    suspend fun registerInterest(@Path("type") type: String): PropertyEntity
}