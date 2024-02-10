package com.example.subj1.feature_cab.ui_layer.pages

import androidx.compose.runtime.Composable
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.subj1.feature_cab.ui_layer.cabs.PropertyViewModel

@Composable
fun MainNavHost() {
    val viewModel: PropertyViewModel = viewModel()
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = "mainSection"
    ) {
        composable("mainSection"){
            MainSection(navController)
        }
        composable("propertyOrganizerSection") {
            PropertyOrganizerSection(navController, viewModel)
        }
        composable("clientSection") {
            ManageSection(navController, viewModel)
        }
        composable("adminSection"){
            ReportsSection(navController)
        }
    }
}