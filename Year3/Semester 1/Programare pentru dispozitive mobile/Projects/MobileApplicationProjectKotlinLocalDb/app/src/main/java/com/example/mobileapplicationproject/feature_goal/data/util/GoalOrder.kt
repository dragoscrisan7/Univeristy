package com.example.mobileapplicationproject.feature_goal.data.util

sealed class GoalOrder(val orderType: OrderType){
    class Title(orderType: OrderType): GoalOrder(orderType)
    class Deadline(orderType: OrderType): GoalOrder(orderType)
}
