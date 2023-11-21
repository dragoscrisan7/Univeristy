package com.example.mobileapplicationproject.ui_layer.pages

import com.example.mobileapplicationproject.storage.display.GoalRepo
import com.example.mobileapplicationproject.storage.structure.GoalViewModel
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.*
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import com.example.mobileapplicationproject.ui_layer.goal_ui.GoalCreationScreen
import com.example.mobileapplicationproject.ui_layer.goal_ui.GoalUpdateScreen

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
            GoalRepo(viewModel, navController)
        }
        composable("addGoal") {
            GoalCreationScreen(
                viewModel = viewModel,
                onGoalCreated = { newGoal ->
                    // Handle the newly created goal here (e.g., save it in the ViewModel)
                    viewModel.addGoal(newGoal)
                    // You can navigate back to the main screen or any other screen as needed
                    navController.navigate("main")
                }
            )
        }
        composable("updateGoal/{goalTitle}") { backStackEntry ->
            val arguments = requireNotNull(backStackEntry.arguments)
            val goalTitle = arguments.getString("goalTitle")
            val goal = goalTitle?.let { viewModel.getGoalByTitle(it) }

            if (goal != null) {
                GoalUpdateScreen(
                    viewModel = viewModel,
                    goal = goal,
                    onUpdate = { updatedGoal ->
                        // Handle the updated goal here (e.g., update it in the ViewModel)
                        viewModel.updateGoal(updatedGoal)
                        // You can navigate back to the main screen or any other screen as needed
                        navController.navigate("main")
                    }
                )
            } else {
                Text("Goal not found")
            }
        }
    }
}