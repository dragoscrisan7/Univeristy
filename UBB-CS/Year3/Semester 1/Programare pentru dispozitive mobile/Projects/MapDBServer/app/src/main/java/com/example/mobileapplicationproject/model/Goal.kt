package com.example.mobileapplicationproject.model

import android.os.Parcelable
import androidx.room.ColumnInfo
import androidx.room.PrimaryKey
import kotlinx.android.parcel.Parcelize

@Parcelize
data class Goal (
    @PrimaryKey(autoGenerate = true)
    var id: Int = 0,
    var title: String,
    var description: String,
    var deadline: String,
    var isPrivate: Boolean,
    @ColumnInfo(name = "miniGoals")
    var miniGoals: List<String>
) : Parcelable