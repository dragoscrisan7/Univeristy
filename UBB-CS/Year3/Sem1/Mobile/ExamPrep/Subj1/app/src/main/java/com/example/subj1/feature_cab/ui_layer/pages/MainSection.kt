package com.example.subj1.feature_cab.ui_layer.pages

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController

@Composable
fun MainSection(navController: NavController) {
    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Button(
            onClick = { navController.navigate("propertyOrganizerSection") },
            modifier = Modifier.padding(8.dp)
        ) {
            Text("Property Organizer Section")
        }
        Button(
            onClick = { navController.navigate("clientSection") },
            modifier = Modifier.padding(8.dp)
        ) {
            Text("Client Section")
        }
        Button(
            onClick = { navController.navigate("adminSection") },
            modifier = Modifier.padding(8.dp)
        ) {
            Text("Admin Section")
        }
    }
}