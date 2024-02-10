package com.example.mobileapplicationproject.data.future_message
data class FutureMessage(
    val messageContent: String,
    val deliveryDateTime: String,
    val isPrivate: Boolean,
    val isRepeated: Boolean,
    val repeatInterval: Long
)