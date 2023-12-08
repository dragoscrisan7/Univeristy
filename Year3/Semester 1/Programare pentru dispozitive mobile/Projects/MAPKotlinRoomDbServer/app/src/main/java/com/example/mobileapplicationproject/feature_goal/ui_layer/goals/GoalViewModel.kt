package com.example.mobileapplicationproject.feature_goal.ui_layer.goals

import android.content.Context
import android.net.ConnectivityManager
import android.net.Network
import android.net.NetworkCapabilities
import android.os.Build
import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.mobileapplicationproject.feature_goal.data.use_cases.GoalUseCases
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder
import com.example.mobileapplicationproject.feature_goal.data.util.OrderType
import dagger.hilt.android.lifecycle.HiltViewModel
import dagger.hilt.android.qualifiers.ApplicationContext
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import javax.inject.Inject

class NetworkMonitor @Inject constructor(
    @ApplicationContext private val context: Context
) {

    private val connectivityManager =
        context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

    private val _networkStatusFlow = MutableStateFlow(isNetworkAvailable())
    val networkStatusFlow: StateFlow<Boolean> = _networkStatusFlow

    init {
        registerNetworkCallback()
    }

    private fun registerNetworkCallback() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            connectivityManager.registerDefaultNetworkCallback(object : ConnectivityManager.NetworkCallback() {
                override fun onAvailable(network: Network) {
                    _networkStatusFlow.value = true
                }

                override fun onLost(network: Network) {
                    _networkStatusFlow.value = false
                }
            })
        }
    }

    fun isNetworkAvailable(): Boolean {
        val networkCapabilities = connectivityManager.activeNetwork ?: return false
        val activeNetwork = connectivityManager.getNetworkCapabilities(networkCapabilities) ?: return false

        return activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) ||
                activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR) ||
                activeNetwork.hasTransport(NetworkCapabilities.TRANSPORT_ETHERNET)
    }
}

@HiltViewModel
class GoalViewModel @Inject constructor(
    private val goalUseCases: GoalUseCases,
    private val networkMonitor: NetworkMonitor
): ViewModel() {

    private val _state = mutableStateOf(GoalsState())
    val state: State<GoalsState> = _state

//    private var recentlyDeletedGoal: GoalEntity? = null

    private var getGoalsJob: Job? = null

    private var currentGoalId: Int? = null

    init {
        observeNetworkChanges()
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
//                    recentlyDeletedGoal=event.goal
                }
            }
//            is GoalsEvent.RestoreGoal -> {
//                viewModelScope.launch {
//                    goalUseCases.addGoal(recentlyDeletedGoal ?: return@launch)
//                    recentlyDeletedGoal = null
//                }
//            }
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
            is GoalsEvent.NetworkReconnected -> {
                goalUseCases.networkReconnected()
            }
        }
    }

    private fun observeNetworkChanges() {
        viewModelScope.launch {
            networkMonitor.networkStatusFlow.collect { isConnected ->
                if (isConnected) {
                    // Trigger the event when network is reconnected
                    onEvent(GoalsEvent.NetworkReconnected)
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