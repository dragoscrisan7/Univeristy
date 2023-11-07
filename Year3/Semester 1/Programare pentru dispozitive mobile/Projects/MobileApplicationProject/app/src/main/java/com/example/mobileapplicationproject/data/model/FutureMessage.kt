package com.example.mobileapplicationproject.data.model
data class FutureMessage(
    val messageContent: String,
    val deliveryDateTime: String,
    val isPrivate: Boolean,
    val isRepeated: Boolean,
    val repeatInterval: Long
)