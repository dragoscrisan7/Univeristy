package com.example.mobileapplicationproject.feature_goal.data.model

import android.os.Parcelable
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.TypeConverter
import com.google.firebase.crashlytics.buildtools.reloc.com.google.common.reflect.TypeToken
import com.google.gson.Gson
import kotlinx.android.parcel.Parcelize

@Parcelize
@Entity(tableName = "goals") // Define the table name if you want to customize it
data class GoalEntity(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0, // Room will auto-generate IDs if set to true
    val title: String,
    val description: String,
    val deadline: String,
    val isPrivate: Boolean,
    @ColumnInfo(name = "miniGoals")
    val miniGoals: List<String>
): Parcelable

class Converters {
    @TypeConverter
    fun fromString(value: String?): List<String>? {
        val listType = object : TypeToken<List<String>>() {}.type
        return Gson().fromJson(value, listType)
    }

    @TypeConverter
    fun toString(value: List<String>?): String {
        return Gson().toJson(value)
    }
}
class InvalidGoalException(message: String): Exception (message)