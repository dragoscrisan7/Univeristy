package com.example.mobileapplicationproject

import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import com.example.mobileapplicationproject.data.components.GoalCreationScreen
import com.example.mobileapplicationproject.data.components.GoalRepo
import com.example.mobileapplicationproject.data.interfaces.GoalsPage
import com.example.mobileapplicationproject.data.model.Goal
import com.example.mobileapplicationproject.ui.theme.MobileApplicationProjectTheme

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MobileApplicationProjectTheme {
                GoalsPage()
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    GoalsPage()
                }
            }
        }
    }
}
