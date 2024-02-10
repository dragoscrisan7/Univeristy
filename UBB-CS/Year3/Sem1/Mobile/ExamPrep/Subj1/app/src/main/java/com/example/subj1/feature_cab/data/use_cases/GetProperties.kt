package com.example.subj1.feature_cab.data.use_cases

import com.example.subj1.feature_cab.data.model.PropertyEntity
import com.example.subj1.feature_cab.data.repository.PropertyRepo
import kotlinx.coroutines.flow.Flow

class GetProperties(
    private val repository: PropertyRepo
){
    operator fun invoke(): Flow<List<PropertyEntity>> {
        return repository.getAllProperties()
    }
}

class GetProperty(
    private val repository: PropertyRepo
) {
    suspend operator fun invoke(propertyId: Long): PropertyEntity? {
        return repository.getPropertyById(propertyId)
    }
}

class AddProperty(
    private val repository: PropertyRepo
) {
    suspend operator fun invoke(property: PropertyEntity) {
        repository.insertProperty(property)
    }
}

class GetAllPropertyTypes(
    private val repository: PropertyRepo
) {
    suspend operator fun invoke(): List<String> {
        return repository.getPropertyTypes()
    }
}