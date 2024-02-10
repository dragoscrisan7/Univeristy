package com.example.subj1.feature_cab.data.repository

import com.example.subj1.feature_cab.data.model.PropertyEntity
import kotlinx.coroutines.flow.Flow

interface PropertyRepo {
    // Property Organizer Section
    fun getAllProperties(): Flow<List<PropertyEntity>>
    suspend fun getPropertyById(id: Long): PropertyEntity?
    suspend fun insertProperty(property: PropertyEntity)
    suspend fun processOfflineCommands()

    // Client Section
    suspend fun getPropertyTypes(): List<String>
    suspend fun expressInterest(propertyType: String)

}