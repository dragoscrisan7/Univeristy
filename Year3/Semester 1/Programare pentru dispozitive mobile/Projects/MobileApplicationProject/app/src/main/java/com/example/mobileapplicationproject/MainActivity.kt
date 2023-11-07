package com.example.mobileapplicationproject

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.mobileapplicationproject.data.components.GoalCreationScreen
import com.example.mobileapplicationproject.data.components.GoalList
import com.example.mobileapplicationproject.data.model.Goal
import com.example.mobileapplicationproject.ui.theme.MobileApplicationProjectTheme

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MobileApplicationProjectTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    GoalApp()
                }
            }
        }
    }
}

@Composable
fun GoalApp() {
    val goals = remember { mutableStateListOf<Goal>() }

    GoalList(goals)

    GoalList(goals) { goal ->
        goals.remove(goal) // Remove the goal from the list
    }

    GoalCreationScreen { newGoal ->
        goals.add(newGoal)
    }
}