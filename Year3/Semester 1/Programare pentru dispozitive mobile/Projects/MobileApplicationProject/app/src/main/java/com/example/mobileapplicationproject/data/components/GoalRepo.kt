package com.example.mobileapplicationproject.data.components

import android.util.Log
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import com.example.mobileapplicationproject.data.model.Goal
import com.example.mobileapplicationproject.data.model.GoalViewModel
import androidx.compose.foundation.lazy.items


@Composable
fun GoalDisplayItem(
    goal: Goal,
    onClick: () -> Unit
) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .clickable { onClick() } // Handle item click
            .padding(16.dp)
    ) {
        Column {
            Text(text = goal.title, fontSize = 18.sp, fontWeight = FontWeight.Bold)
            Text(text = goal.description, fontSize = 16.sp)
            Text(text = "Deadline: ${goal.deadline}", fontSize = 16.sp)
            // Add more details as needed
        }
    }
}


@Composable
fun GoalRepo(
    viewModel: GoalViewModel,
    navController: NavController
) {
    val goals: List<Goal> = viewModel.getGoals()

    Column(
        modifier = Modifier.fillMaxSize(),
    ) {
        Spacer(modifier = Modifier.height(30.dp))

        LazyColumn {
            item {
                Text(
                    text = "List of Goals",
                    modifier = Modifier.padding(16.dp),
                    fontSize = 30.sp
                )
            }
            items(goals) { goal ->
                GoalDisplayItem(
                    goal = goal,
                    onClick = {
                        // Handle item click: Navigate to goal details
                        navController.navigate("goalDetail/${goal.id}")
                    }
                )
            }

            item {
                Button(
                    onClick = {
                        // Navigate to the "Add Goal" screen
                        navController.navigate("addGoal")
                    },
                    modifier = Modifier.padding(16.dp)
                ) {
                    Text("Add")
                }
            }
        }
    }
}