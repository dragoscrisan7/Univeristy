package com.example.mobileapplicationproject.feature_goal.ui_layer.goals

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GoalUseCases
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder
import com.example.mobileapplicationproject.feature_goal.data.util.OrderType
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class GoalViewModel @Inject constructor(
    private val goalUseCases: GoalUseCases
): ViewModel() {

    private val _state = mutableStateOf(GoalsState())
    val state: State<GoalsState> = _state

    private var recentlyDeletedGoal: GoalEntity? = null

    private var getGoalsJob: Job? = null

    private var currentGoalId: Int? = null

    init {
        getGoals(GoalOrder.Title(OrderType.Descending))
    }
    suspend fun onEvent(event: GoalsEvent){
        when(event){
            is GoalsEvent.Order -> {
                if(state.value.goalOrder::class == event.goalOrder::class &&
                    state.value.goalOrder.orderType == event.goalOrder.orderType) {
                    return
                }
                getGoals(event.goalOrder)
            }
            is GoalsEvent.DeleteGoal -> {
                viewModelScope.launch {
                    goalUseCases.deleteGoal(event.goal)
                    recentlyDeletedGoal=event.goal
                }
            }
            is GoalsEvent.RestoreGoal -> {
                viewModelScope.launch {
                    goalUseCases.addGoal(recentlyDeletedGoal ?: return@launch)
                    recentlyDeletedGoal = null
                }
            }
            is GoalsEvent.ToggleOrderSection -> {
                _state.value = state.value.copy(
                    isOrderSectionVisible = !state.value.isOrderSectionVisible
                )
            }
            is GoalsEvent.AddGoal -> {
                viewModelScope.launch {
                    goalUseCases.addGoal(event.goal)
                }
            }
            is GoalsEvent.UpdateGoal -> {
                viewModelScope.launch {
                    goalUseCases.updateGoal(event.goal)
                }
            }
            is GoalsEvent.GetGoal -> {
                val goal = goalUseCases.getGoal(event.goalTitle)
                viewModelScope.launch {
                    goal?.let {
                        _state.value = state.value.copy(
                            goal = goal
                        )
                    }
                }
            }
        }
    }

    private fun getGoals(goalOrder: GoalOrder){
        getGoalsJob?.cancel()
        getGoalsJob =  goalUseCases.getGoals(goalOrder)
            .onEach { goals ->
                _state.value = state.value.copy(
                    goals = goals,
                    goalOrder = goalOrder
                )
            }
            .launchIn(viewModelScope)
    }
}