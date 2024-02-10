package com.example.subj1.feature_cab.ui_layer.cabs

import com.example.subj1.feature_cab.data.model.PropertyEntity

data class PropertiesState(
    val properties: List<PropertyEntity> = emptyList(),
    val property: PropertyEntity? = null,
    val propertyTypes: List<String> = emptyList()
)