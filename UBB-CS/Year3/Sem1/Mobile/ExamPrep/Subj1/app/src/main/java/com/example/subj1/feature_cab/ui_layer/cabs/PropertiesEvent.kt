package com.example.subj1.feature_cab.ui_layer.cabs

import com.example.subj1.feature_cab.data.model.PropertyEntity

sealed class PropertiesEvent {
    data class AddProperty(val property: PropertyEntity) : PropertiesEvent()
    data class GetProperty(val propertyId: Long) : PropertiesEvent()
    object GetProperties : PropertiesEvent()
    object GetAllPropertyTypes : PropertiesEvent()
}
