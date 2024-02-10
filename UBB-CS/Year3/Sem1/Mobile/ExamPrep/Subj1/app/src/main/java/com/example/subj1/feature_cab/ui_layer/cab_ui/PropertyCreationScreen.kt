package com.example.subj1.feature_cab.ui_layer.cab_ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.subj1.feature_cab.data.model.PropertyEntity
import com.example.subj1.feature_cab.ui_layer.cabs.PropertyViewModel

@Composable
fun PropertyCreationScreen(
    viewModel: PropertyViewModel,
    onPropertyCreated: (PropertyEntity) -> Unit
) {
    var name by remember { mutableStateOf("") }
    var date by remember { mutableStateOf("") }
    var details by remember { mutableStateOf("") }
    var status by remember { mutableStateOf("") }
    var viewers by remember { mutableStateOf("") }
    var type by remember { mutableStateOf("") }

    var isButtonEnabled by remember { mutableStateOf(true) }

    fun updateButtonEnabled() {
        isButtonEnabled = name.isNotEmpty() && date.isNotEmpty() && details.isNotEmpty() && status.isNotEmpty() && viewers.isNotEmpty() && type.isNotEmpty()
    }

    Column(
        modifier = Modifier.fillMaxWidth(),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = "Create a New Property Listing",
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
        TextField(
            value = name,
            onValueChange = { name = it; updateButtonEnabled() },
            label = { Text("Name") },
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = date,
            onValueChange = { date = it; updateButtonEnabled() },
            label = { Text("Date") },
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = details,
            onValueChange = { details = it; updateButtonEnabled() },
            label = { Text("Details") },
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = status,
            onValueChange = { status = it; updateButtonEnabled() },
            label = { Text("Status") },
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = viewers,
            onValueChange = { viewers = it; updateButtonEnabled() },
            label = { Text("Viewers") },
            modifier = Modifier.padding(vertical = 8.dp)
        )
        TextField(
            value = type,
            onValueChange = { type = it; updateButtonEnabled() },
            label = { Text("Type") },
            modifier = Modifier.padding(vertical = 8.dp)
        )

        Button(
            onClick = {
                if (isButtonEnabled) {
                    val newProperty = PropertyEntity(
                        name = name,
                        date = date,
                        details = details,
                        status = status,
                        viewers = viewers.toInt(),
                        type = type
                    )
                    onPropertyCreated(newProperty)
                }
            },
            modifier = Modifier
                .padding(top = 16.dp)
                .fillMaxWidth(),
            enabled = isButtonEnabled
        ) {
            Text("Create Property")
        }
    }
}