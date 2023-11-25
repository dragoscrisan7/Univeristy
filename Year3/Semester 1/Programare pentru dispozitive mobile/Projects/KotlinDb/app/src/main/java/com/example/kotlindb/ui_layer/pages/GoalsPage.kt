package com.example.mobileapplicationproject.feature_goal.ui_layer.pages

import androidx.compose.runtime.Composable
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui.GoalCreationScreen
import com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui.GoalDisplayList
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalViewModel
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalsEvent

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
            GoalCreationScreen(
                viewModel = viewModel,
                onGoalCreated = { newGoal ->
                    // Handle the newly created goal here (e.g., save it in the ViewModel)
                    viewModel.onEvent(GoalsEvent.AddGoal(newGoal))
                    // You can navigate back to the main screen or any other screen as needed
                    navController.navigate("main")
                }
            )
        }
//        composable("updateGoal/{goalTitle}") { backStackEntry ->
//            val arguments = requireNotNull(backStackEntry.arguments)
//            val goalTitle = arguments.getString("goalTitle")
//            val goal = goalTitle?.let { viewModel.getGoalByTitle(it) }
//
//            if (goal != null) {
//                GoalUpdateScreen(
//                    viewModel = viewModel,
//                    goal = goal,
//                    onUpdate = { updatedGoal ->
//                        // Handle the updated goal here (e.g., update it in the ViewModel)
//                        viewModel.onEvent(GoalsEvent.UpdateGoal(updatedGoal))
//                        // You can navigate back to the main screen or any other screen as needed
//                        navController.navigate("main")
//                    }
//                )
//            } else {
//                Text("Goal not found")
//            }
//        }
    }
}