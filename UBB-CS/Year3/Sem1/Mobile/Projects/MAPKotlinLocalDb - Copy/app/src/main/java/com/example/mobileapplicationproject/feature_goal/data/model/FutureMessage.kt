package com.example.mobileapplicationproject.feature_goal.data.model
data class FutureMessage(
    val messageContent: String,
    val deliveryDateTime: String,
    val isPrivate: Boolean,
    val isRepeated: Boolean,
    val repeatInterval: Long
)