package com.example.mobileapplicationproject.feature_goal.ui_layer.pages

import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.rememberCoroutineScope
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui.GoalCreationScreen
import com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui.GoalDisplayList
import com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui.GoalUpdateScreen
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalViewModel
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalsEvent
import kotlinx.coroutines.launch

@Composable
fun GoalsPage()
{
    val viewModel: GoalViewModel = viewModel()
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = "main"
    ) {
        composable("main") {
            GoalDisplayList(viewModel, navController)
        }
        composable("addGoal") {
            val coroutineScope = rememberCoroutineScope()

            GoalCreationScreen(
                viewModel = viewModel,
                onGoalCreated = { newGoal ->
                    coroutineScope.launch {
                        // Handle the newly created goal here (e.g., save it in the ViewModel)
                        viewModel.onEvent(GoalsEvent.AddGoal(newGoal))
                        // You can navigate back to the main screen or any other screen as needed
                        navController.navigate("main")
                    }
                }
            )
        }
        composable("updateGoal/{goalTitle}") { backStackEntry ->
            val arguments = requireNotNull(backStackEntry.arguments)
            val goalTitle = arguments.getString("goalTitle")
            val goal: GoalEntity? = goalTitle?.let { title ->
                var result: GoalEntity? = null
                LaunchedEffect(viewModel) {
                    viewModel.onEvent(GoalsEvent.GetGoal(title) { loadedGoal ->
                        result = loadedGoal
                    })
                }
                result
            }

            if (goal != null) {
                val coroutineScope = rememberCoroutineScope()

                LaunchedEffect(viewModel, coroutineScope) {
                    coroutineScope.launch {
                        viewModel.onEvent(GoalsEvent.UpdateGoal(goal))
                        // You can navigate back to the main screen or any other screen as needed
                        navController.navigate("main")
                    }
                }

                GoalUpdateScreen(
                    viewModel = viewModel,
                    goal = goal,
                    onUpdate = { updatedGoal ->
                        // This lambda is now a suspend function because it is called within a coroutine
                    }
                )
            } else {
                Text("Goal not found")
            }
        }
    }
}