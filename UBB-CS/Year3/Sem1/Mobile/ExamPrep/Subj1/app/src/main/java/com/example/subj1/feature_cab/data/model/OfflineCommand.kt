package com.example.subj1.feature_cab.data.model

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "offline_commands")
data class OfflineCommand(
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    val type: CommandType,
    val property: PropertyEntity? = null,
    val propertyId: Long? = null
) {
    enum class CommandType {
        INSERT
    }
}