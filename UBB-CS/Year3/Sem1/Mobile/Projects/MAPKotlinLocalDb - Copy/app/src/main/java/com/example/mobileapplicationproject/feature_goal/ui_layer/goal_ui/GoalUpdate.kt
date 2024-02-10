package com.example.mobileapplicationproject.feature_goal.ui_layer.goal_ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.mobileapplicationproject.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalViewModel

@Composable
fun GoalUpdateScreen(
    viewModel: GoalViewModel,
    goal: GoalEntity,
    onUpdate: (GoalEntity) -> Unit
) {
    var updatedTitle by remember { mutableStateOf(goal.title) }
    var isTitleError by remember { mutableStateOf(false) }
    var updatedDescription by remember { mutableStateOf(goal.description) }
    var isDescriptionError by remember { mutableStateOf(false) }
    var updatedDeadline by remember { mutableStateOf(goal.deadline) }
    var isDeadlineError by remember { mutableStateOf(false) }
    var updatedIsPrivate by remember { mutableStateOf(goal.isPrivate) }
    var miniGoals by remember { mutableStateOf("") }
    var updatedMiniGoals by remember { mutableStateOf(goal.miniGoals.joinToString("\n")) }

    var isButtonEnabled by remember { mutableStateOf(true) }

    fun updateButtonEnabled() {
        isButtonEnabled = updatedTitle.isNotEmpty() && updatedDescription.isNotEmpty() && updatedDeadline.isNotEmpty() && !isTitleError && !isDescriptionError && !isDeadlineError
    }

    Column(
        modifier = Modifier
            .fillMaxWidth(),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = "Update a Goal",
            fontWeight = FontWeight.Bold,
            fontSize = 24.sp,
            modifier = Modifier.padding(vertical = 16.dp)
        )
    }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally

    ) {
        val regexPattern = """^\d{2}/\d{2}/\d{4}$""".toRegex()

        // Input fields for updating goal details
        TextField(
            value = updatedTitle,
            onValueChange = { updatedTitle = it
                            isTitleError = it.isEmpty() || it.length > 20
                            updateButtonEnabled()},
            label = { Text("Title") },
            supportingText = { Text(text = "*required")},
            isError = isTitleError,
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = updatedDescription,
            onValueChange = { updatedDescription = it
                            isDescriptionError = it.isEmpty()
                            updateButtonEnabled()
                            },
            label = { Text("Description") },
            supportingText = { Text(text = "*required")},
            isError = isDescriptionError,
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = updatedDeadline,
            onValueChange = { updatedDeadline = it
                        isDeadlineError = !updatedDeadline.matches(regexPattern)
                        updateButtonEnabled()
                        },
            label = { Text("Deadline") },
            suffix = { Text("dd/mm/yyyy") },
            supportingText = { Text(text = "*required")},
            isError = isDeadlineError,
            modifier = Modifier.padding(vertical = 8.dp)
        )
        Checkbox(
            checked = updatedIsPrivate,
            onCheckedChange = { updatedIsPrivate = it },
        )
        Text(
            "Private Goal",
            modifier = Modifier.padding(top = 8.dp)
        )

        TextField(
            value = updatedMiniGoals,
            onValueChange = { updatedMiniGoals = it },
            label = { Text("Mini-Goals") },
            modifier = Modifier.padding(vertical = 8.dp)
        )

        // Button to update the goal
        Button(
            onClick = {
                // Validate input and update the goal
                if (updatedTitle.isNotEmpty() && updatedDescription.isNotEmpty() && updatedDeadline.isNotEmpty()) {
                    val updatedGoal = GoalEntity(
                        id = goal.id, // Retain the existing ID
                        title = updatedTitle,
                        description = updatedDescription,
                        deadline = updatedDeadline,
                        isPrivate = updatedIsPrivate,
                        miniGoals = updatedMiniGoals.split("\n")
                    )
                    onUpdate(updatedGoal)
                }
            },
            modifier = Modifier
                .padding(top = 16.dp)
                .fillMaxWidth(),
            enabled = isButtonEnabled
        ) {
            Text("Update Goal")
        }
    }
}
