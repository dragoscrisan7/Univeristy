package com.example.subj1.feature_cab.data.utils

import com.example.subj1.feature_cab.data.model.PropertyEntity
import com.google.gson.Gson
import com.google.gson.JsonSyntaxException

object Encoder {
    fun encodeProperty(property: PropertyEntity): String {
        val gson = Gson()
        return gson.toJson(property)
    }

    fun decodeProperty(encodedCab: String): PropertyEntity? {
        val gson = Gson()
        return try {
            gson.fromJson(encodedCab, PropertyEntity::class.java)
        } catch (e: JsonSyntaxException) {
            null
        }
    }
}