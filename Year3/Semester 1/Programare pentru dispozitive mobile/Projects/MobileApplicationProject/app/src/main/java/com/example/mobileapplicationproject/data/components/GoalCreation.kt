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
import com.example.mobileapplicationproject.data.model.GoalViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun GoalCreationScreen(
    viewModel: GoalViewModel,
    onGoalCreated: (Goal) -> Unit
) {
    var title by remember { mutableStateOf("") }
    var description by remember { mutableStateOf("") }
    var deadline by remember { mutableStateOf("") }
    var isPrivate by remember { mutableStateOf(false) }
    var miniGoals by remember { mutableStateOf("") }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)
    ) {
        Text(text = "Create a New Goal", fontWeight = FontWeight.Bold, fontSize = 24.sp)
        var isPrivate by remember { mutableStateOf(false) }

        // Input fields for goal details
        TextField(
            value = title,
            onValueChange = { title = it },
            label = { Text("Title") }
        )
        TextField(
            value = description,
            onValueChange = { description = it },
            label = { Text("Description") }
        )

        TextField(
            value = deadline,
            onValueChange = { deadline = it },
            label = { Text("Deadline") }
        )
        Checkbox(
            checked = isPrivate,
            onCheckedChange = { isPrivate = it },
            modifier = Modifier.padding(top = 8.dp)
        )

        Text("Private Goal")

        TextField(
            value = miniGoals,
            onValueChange = { miniGoals = it },
            label = { Text("Mini-Goals") }
        )
    }

    // Button to create the goal
    Button(
        onClick = {
            // Validate input and create a new goal
            if (title.isNotEmpty() && description.isNotEmpty() && deadline.isNotEmpty()) {
                val newGoalId = viewModel.getNewGoalId()
                val newGoal = Goal(newGoalId, title, description, deadline, isPrivate, miniGoals.split("\n"))
                onGoalCreated(newGoal)
            }
        },
        modifier = Modifier.padding(top = 16.dp)
    ) {
        Text("Create Goal")
    }
}