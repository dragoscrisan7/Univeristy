package com.example.kotlindb.feature_goal.data.util

sealed class OrderType{
    object Ascending: OrderType()
    object Descending: OrderType()
}
