package com.example.mobileapplicationproject.feature_goal.data

import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.stateIn

class GoalViewModel(private val goalRepository: GoalRepository) : ViewModel() {

    // Use LiveData or Flow to observe changes in the list of goals
    val goals: State<List<GoalEntity>> = goalRepository.getAllGoals().stateIn(viewModelScope, SharingStarted.Lazily, emptyList())

    fun getAllGoalsLiveData() = goals
    // ViewModelScope for coroutine management

    fun addGoal(goal: GoalEntity) {
        viewModelScope.launch(Dispatchers.IO) {
            goalRepository.insertGoal(goal)
        }
    }

    fun updateGoal(goal: GoalEntity) {
        viewModelScope.launch(Dispatchers.IO) {
            goalRepository.updateGoal(goal)
        }
    }

    fun deleteGoal(goal: GoalEntity) {
        viewModelScope.launch(Dispatchers.IO) {
            goalRepository.deleteGoal(goal)
        }
    }
}