package com.example.subj1.feature_cab.ui_layer.pages

import androidx.compose.runtime.Composable
import androidx.navigation.NavController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.subj1.feature_cab.ui_layer.cabs.PropertyViewModel
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.launch

@OptIn(ExperimentalCoroutinesApi::class)
@Composable
fun ManageSection(navController: NavController, viewModel: PropertyViewModel) {
    val nestedNavController = rememberNavController()


}