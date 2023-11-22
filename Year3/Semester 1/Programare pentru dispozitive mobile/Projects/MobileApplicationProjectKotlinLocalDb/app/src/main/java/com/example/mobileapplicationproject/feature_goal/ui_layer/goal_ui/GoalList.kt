package com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
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
import com.example.mobileapplicationproject.feature_goal.data.GoalViewModel
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.runtime.livedata.observeAsState
import androidx.compose.runtime.getValue
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity

@Composable
fun GoalDisplayItem(
    goal: GoalEntity,
    onEditClick: () -> Unit,
    onDeleteClick: () -> Unit
) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            horizontalArrangement = Arrangement.SpaceBetween
        ) {
            Column {
                Text(text = goal.title, fontSize = 18.sp, fontWeight = FontWeight.Bold)
                Text(text = goal.description, fontSize = 16.sp)
                Text(text = "Deadline: ${goal.deadline}", fontSize = 16.sp)
            }

            Column {
                IconButton(onClick = onEditClick) {
                    Icon(Icons.Default.Edit, contentDescription = "Edit")
                }

                IconButton(onClick = onDeleteClick) {
                    Icon(Icons.Default.Delete, contentDescription = "Delete")
                }
            }
        }
    }
}

@Composable
fun GoalDisplayList(
    viewModel: GoalViewModel,
    navController: NavController
) {
    var deletingGoalTitle by remember { mutableStateOf ("") }
    var showDeleteDialog by remember { mutableStateOf(false) }

    val goals: State<List<GoalEntity>> = goalRepository.getAllGoals().stateIn(viewModelScope, SharingStarted.Lazily, emptyList())

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
                    onEditClick = {
                        // Handle item click: Navigate to goal details
                        navController.navigate("updateGoal/${goal.title}")
                    },
                    onDeleteClick = {
                        deletingGoalTitle = goal.title
                        showDeleteDialog = true
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

    if (showDeleteDialog) {
        DeleteConfirmationDialog(
            onConfirmDelete = {
                // Handle goal deletion here (e.g., delete it in the ViewModel)
                viewModel.deleteGoal(deletingGoalTitle)
                // Close the confirmation dialog
                showDeleteDialog = false
            },
            onDismiss = {
                // Close the confirmation dialog
                showDeleteDialog = false
            }
        )
    }
}

