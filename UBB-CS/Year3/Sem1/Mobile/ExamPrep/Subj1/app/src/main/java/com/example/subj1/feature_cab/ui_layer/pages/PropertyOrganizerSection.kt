package com.example.subj1.feature_cab.ui_layer.pages

import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.rememberCoroutineScope
import androidx.navigation.NavController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.subj1.feature_cab.ui_layer.cab_ui.PropertyCreationScreen
import com.example.subj1.feature_cab.ui_layer.cab_ui.PropertyDetailsScreen
import com.example.subj1.feature_cab.ui_layer.cab_ui.PropertyDisplayList
import com.example.subj1.feature_cab.ui_layer.cabs.PropertiesEvent
import com.example.subj1.feature_cab.ui_layer.cabs.PropertyViewModel
import kotlinx.coroutines.launch
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue


@Composable
fun PropertyOrganizerSection(navController: NavController, viewModel: PropertyViewModel) {
    val nestedNavController = rememberNavController()

    NavHost(
        navController = nestedNavController,
        startDestination = "main"
    ) {
        composable("main") {
            PropertyDisplayList(viewModel, nestedNavController, navController)
        }
        composable("addProperty") {
            val coroutineScope = rememberCoroutineScope()

            PropertyCreationScreen(
                viewModel = viewModel,
                onPropertyCreated = { newProperty ->
                    coroutineScope.launch {
                        viewModel.onEvent(PropertiesEvent.AddProperty(newProperty))
                        nestedNavController.navigate("main")
                    }
                }
            )
        }
//        composable("propertyDetails/{propertyId}") { backStackEntry ->
//            val propertyId = backStackEntry.arguments?.getString("propertyId")
//
//            LaunchedEffect(propertyId) {
//                propertyId?.let {
//                    viewModel.onEvent(PropertiesEvent.GetProperty(it.toLong()))
//                }
//            }
//
//            val propertyStateFlow = viewModel.state
//            val propertyState = propertyStateFlow.collectAsState().value
//
//            PropertyDetailsScreen(propertyState.property)
//        }
    }
}