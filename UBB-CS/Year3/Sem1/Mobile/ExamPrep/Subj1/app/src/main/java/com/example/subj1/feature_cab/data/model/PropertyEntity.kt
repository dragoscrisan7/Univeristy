package com.example.subj1.feature_cab.data.model

import android.os.Parcelable
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.TypeConverter
import com.google.firebase.crashlytics.buildtools.reloc.com.google.common.reflect.TypeToken
import com.google.gson.Gson
import kotlinx.android.parcel.Parcelize

@Parcelize
@Entity(tableName = "properties")
data class PropertyEntity(
    @PrimaryKey(autoGenerate = true)
    val id: Long = 0,
    val name: String,
    val date: String,
    val details: String,
    val status: String,
    val viewers: Int,
    val type: String
) : Parcelable


class Converters {
    @TypeConverter
    fun fromStringList(value: String?): List<String>? {
        val listType = object : TypeToken<List<String>>() {}.type
        return Gson().fromJson(value, listType)
    }

    @TypeConverter
    fun toStringList(value: List<String>?): String {
        return Gson().toJson(value)
    }

    @TypeConverter
    fun fromPropertyEntity(cabEntity: PropertyEntity?): String? {
        return Gson().toJson(cabEntity)
    }

    @TypeConverter
    fun toPropertyEntity(json: String?): PropertyEntity? {
        return Gson().fromJson(json, PropertyEntity::class.java)
    }
}
class InvalidGoalException(message: String): Exception (message)
