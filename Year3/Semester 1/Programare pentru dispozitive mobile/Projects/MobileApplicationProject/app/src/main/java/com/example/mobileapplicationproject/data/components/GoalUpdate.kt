package com.example.mobileapplicationproject.data.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Checkbox
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.mobileapplicationproject.data.model.Goal

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun GoalUpdateScreen(
    goal: Goal,
    onUpdate: (Goal) -> Unit
) {
    var updatedTitle by remember { mutableStateOf(goal.title) }
    var updatedDescription by remember { mutableStateOf(goal.description) }
    var updatedDeadline by remember { mutableStateOf(goal.deadline) }
    var updatedIsPrivate by remember { mutableStateOf(goal.isPrivate) }
    var updatedMiniGoals by remember { mutableStateOf(goal.miniGoals.joinToString("\n")) }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)
    ) {
        Text(text = "Update Goal", fontWeight = FontWeight.Bold, fontSize = 24.sp)

        // Input fields for updating goal details
        TextField(
            value = updatedTitle,
            onValueChange = { updatedTitle = it },
            label = { Text("Title") }
        )
        TextField(
            value = updatedDescription,
            onValueChange = { updatedDescription = it },
            label = { Text("Description") }
        )
        TextField(
            value = updatedDeadline,
            onValueChange = { updatedDeadline = it },
            label = { Text("Deadline") }
        )
        Checkbox(
            checked = updatedIsPrivate,
            onCheckedChange = { updatedIsPrivate = it },
            modifier = Modifier.padding(top = 8.dp)
        )
        Text("Private Goal")

        TextField(
            value = updatedMiniGoals,
            onValueChange = { updatedMiniGoals = it },
            label = { Text("Mini-Goals") }
        )
    }

    // Button to update the goal
    Button(
        onClick = {
            // Validate input and update the goal
            if (updatedTitle.isNotEmpty() && updatedDescription.isNotEmpty() && updatedDeadline.isNotEmpty()) {
                val updatedGoal = Goal(updatedTitle, updatedDescription, updatedDeadline, updatedIsPrivate, updatedMiniGoals.split("\n"))
                onUpdate(updatedGoal)
            }
        },
        modifier = Modifier.padding(top = 16.dp)
    ) {
        Text("Update Goal")
    }
}