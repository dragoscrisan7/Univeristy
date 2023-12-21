package com.example.mobileapplicationproject.feature_goal.data.use_cases

import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.repository.GoalRepo
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder
import com.example.mobileapplicationproject.feature_goal.data.util.OrderType
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

class GetGoals(
    private val repository: GoalRepo
) {
    operator fun invoke(
        goalOrder: GoalOrder = GoalOrder.Title(OrderType.Descending)
    ): Flow<List<GoalEntity>>{
        return repository.getAllGoals().map { goals ->
            when(goalOrder.orderType) {
                is OrderType.Ascending -> {
                    when(goalOrder){
                        is GoalOrder.Title -> goals.sortedBy { it.title.lowercase() }
                        is GoalOrder.Deadline -> goals.sortedBy { it.deadline }
                    }
                }
                is OrderType.Descending -> {
                    when(goalOrder){
                        is GoalOrder.Title -> goals.sortedByDescending{ it.title.lowercase() }
                        is GoalOrder.Deadline -> goals.sortedByDescending { it.deadline }
                    }
                }
            }
        }
    }
}