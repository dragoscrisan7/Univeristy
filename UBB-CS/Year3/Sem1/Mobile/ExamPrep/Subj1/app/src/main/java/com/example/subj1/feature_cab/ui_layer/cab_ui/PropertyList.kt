package com.example.subj1.feature_cab.ui_layer.cab_ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentHeight
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavController
import com.example.subj1.feature_cab.data.model.PropertyEntity
import com.example.subj1.feature_cab.ui_layer.cabs.PropertyViewModel

@Composable
fun PropertyDisplayItem(
    property: PropertyEntity
) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            horizontalArrangement = Arrangement.SpaceBetween
        ) {
            Column {
                Text(text = "Name: ${property.name}", fontSize = 18.sp, fontWeight = FontWeight.Bold)
                Text(text = "Date: ${property.date}", fontSize = 16.sp)
                Text(text = "Type: ${property.type}", fontSize = 16.sp)
                // Add other property details as needed
            }
        }
    }
}

@Composable
fun PropertyDisplayList(
    viewModel: PropertyViewModel = hiltViewModel(),
    nestedNavController: NavController,
    navController: NavController
) {
    val state = viewModel.state.value

    Column(
        modifier = Modifier.fillMaxSize(),
    ) {
        Box(
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
                .wrapContentHeight()
        ) {
            Button(
                onClick = { navController.navigate("mainSection") },
                modifier = Modifier.align(Alignment.TopEnd)
            ) {
                Text("Back to Main Section")
            }
        }

        Spacer(modifier = Modifier.height(30.dp))

        LazyColumn {
            item {
                Text(
                    text = "List of Properties",
                    modifier = Modifier.padding(16.dp),
                    fontSize = 30.sp
                )
            }
//            items(state.properties) { property ->
//                Clickable(onClick = {
//                    // Navigate to property details
//                    navController.navigate("propertyDetails/${property.id}")
//                }) {
//                    PropertyDisplayItem(
//                        property = property
//                    )
//                }
//            }

            item {
                Button(
                    onClick = {
                        // Navigate to the "Add Property" screen
                        nestedNavController.navigate("addProperty")
                    },
                    modifier = Modifier.padding(16.dp)
                ) {
                    Text("Add")
                }
            }
        }
    }
}
