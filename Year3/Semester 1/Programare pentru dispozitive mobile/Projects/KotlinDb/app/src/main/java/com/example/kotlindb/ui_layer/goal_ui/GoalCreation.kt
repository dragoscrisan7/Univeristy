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
import com.example.kotlindb.feature_goal.data.model.GoalEntity
import com.example.mobileapplicationproject.feature_goal.ui_layer.goals.GoalViewModel

@Composable
fun GoalCreationScreen(
    viewModel: GoalViewModel,
    onGoalCreated: (GoalEntity) -> Unit
) {
    var title by remember { mutableStateOf("") }
    var isTitleError by remember { mutableStateOf(false) }
    var description by remember { mutableStateOf("") }
    var isDescriptionError by remember { mutableStateOf(false) }
    var deadline by remember { mutableStateOf("") }
    var isDeadlineError by remember { mutableStateOf(false) }
    var isPrivate by remember { mutableStateOf(false) }
    var miniGoals by remember { mutableStateOf("") }

    var isButtonEnabled by remember { mutableStateOf(true) }

    fun updateButtonEnabled() {
        isButtonEnabled = title.isNotEmpty() && description.isNotEmpty() && deadline.isNotEmpty() && !isTitleError && !isDescriptionError && !isDeadlineError
    }

    Column(
        modifier = Modifier
            .fillMaxWidth(),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = "Create a New Goal",
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
        var isPrivate by remember { mutableStateOf(false) }
        val regexPattern = """^\d{2}/\d{2}/\d{4}$""".toRegex()

        // Input fields for goal details
        TextField(
            value = title,
            onValueChange = { title = it
                            isTitleError = it.isEmpty() || it.length > 20
                            updateButtonEnabled()
                            },
            label = { Text("Title") },
            supportingText = { Text(text = "*required")},
            isError = isTitleError,
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = description,
            onValueChange = { description = it
                            isDescriptionError = it.isEmpty()
                            updateButtonEnabled()
                            },
            label = { Text("Description") },
            supportingText = { Text(text = "*required")},
            isError = isDescriptionError,
            modifier = Modifier.padding(vertical = 8.dp)
        )

        TextField(
            value = deadline,
            onValueChange = { deadline = it
                            isDeadlineError = !deadline.matches(regexPattern)
                            updateButtonEnabled()
                            },
            label = { Text("Deadline") },
            suffix = { Text("dd/mm/yyyy") },
            supportingText = { Text(text = "*required")},
            isError = isDeadlineError,
            modifier = Modifier.padding(vertical = 8.dp)
        )
        Checkbox(
            checked = isPrivate,
            onCheckedChange = { isPrivate = it }
        )

        Text(
            "Private Goal",
            modifier = Modifier.padding(vertical = 8.dp)
        )

        TextField(
            value = miniGoals,
            onValueChange = { miniGoals = it },
            label = { Text("Mini-Goals") },
            modifier = Modifier.padding(vertical = 8.dp)
        )

        // Button to create the goal
        Button(
            onClick = {
                // Validate input and create a new goal
                if (isButtonEnabled) {
                    val newGoal = GoalEntity(
                            title = title,
                    description = description,
                    deadline = deadline,
                    isPrivate = isPrivate,
                    miniGoals = miniGoals.split("\n")
                    )
                    onGoalCreated(newGoal)
                }
            },
            modifier = Modifier
                .padding(top = 16.dp)
                .fillMaxWidth(),
            enabled = isButtonEnabled
        ) {
            Text("Create Goal")
        }
    }
}

//@Preview
//@Composable
//fun GoalCreationScreenPreview() {
//    // Provide sample data for the parameters used in Preview
//    GoalCreationScreen(
//        viewModel = GoalViewModel(), // Provide an instance of your ViewModel
//        onGoalCreated = {}
//    )
//}