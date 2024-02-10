package com.example.mobileapplicationproject.feature_goal.data.util

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.google.gson.Gson
import com.google.gson.JsonSyntaxException

object Encoder {
    fun encodeGoal(goal: GoalEntity): String {
        val gson = Gson()
        return gson.toJson(goal)
    }

    fun decodeGoal(encodedGoal: String): GoalEntity? {
        val gson = Gson()
        return try {
            gson.fromJson(encodedGoal, GoalEntity::class.java)
        } catch (e: JsonSyntaxException) {
            null
        }
    }
}