package com.example.mobileapplicationproject.data.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import com.example.mobileapplicationproject.data.model.Goal

@Composable
fun GoalListItem(goal: Goal) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp)
    ) {
        Text(text = goal.title, fontWeight = FontWeight.Bold)
        Text(text = goal.description, modifier = Modifier.padding(top = 8.dp))
        Text(text = "Deadline: ${goal.deadline}", modifier = Modifier.padding(top = 4.dp))
        // Add more details as needed
    }
}

@Composable
fun GoalList(goals: List<Goal>) {
    LazyColumn {
        itemsIndexed(goals) { index, goal ->
            GoalListItem(goal)
        }
    }
}

@Composable
fun GoalList(goals: List<Goal>, onDelete: (Goal) -> Unit) {
    LazyColumn {
        itemsIndexed(goals) { index, goal ->
            GoalListItem(goal)
            Row {
                IconButton(
                    onClick = {
                        DeleteConfirmationDialog(
                            goal = goal,
                            onConfirmDelete = {
                                onDelete(goal) // Call the goal deletion handler
                            },
                            onDismiss = {}
                        )
                    },
                    modifier = Modifier.padding(8.dp)
                ) {
                    Icon(imageVector = Icons.Default.Delete, contentDescription = "Delete")
                }
                IconButton(
                    onClick = {
                        // Navigate to the update screen and pass the selected goal
                        // or show the update dialog here as needed
                    },
                    modifier = Modifier.padding(8.dp)
                ) {
                    Icon(imageVector = Icons.Default.Edit, contentDescription = "Edit")
                }
            }
        }
    }
}
