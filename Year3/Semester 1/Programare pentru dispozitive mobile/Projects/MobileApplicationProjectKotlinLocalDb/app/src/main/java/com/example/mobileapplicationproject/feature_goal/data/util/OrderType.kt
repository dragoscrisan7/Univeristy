package com.example.mobileapplicationproject.feature_goal.data.util

sealed class OrderType{
    object Ascending: OrderType()
    object Descending: OrderType()
}
