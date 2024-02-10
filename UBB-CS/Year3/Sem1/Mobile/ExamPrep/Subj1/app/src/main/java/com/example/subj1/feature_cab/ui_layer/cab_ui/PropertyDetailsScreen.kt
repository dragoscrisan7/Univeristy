package com.example.subj1.feature_cab.ui_layer.cab_ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.subj1.feature_cab.data.model.PropertyEntity

@Composable
fun PropertyDetailsScreen(property: PropertyEntity) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = "Property Details",
            fontWeight = FontWeight.Bold,
            fontSize = 24.sp,
            modifier = Modifier.padding(vertical = 16.dp)
        )
        PropertyDetail("Name", property.name)
        PropertyDetail("Date", property.date)
        PropertyDetail("Details", property.details)
        PropertyDetail("Status", property.status)
        PropertyDetail("Viewers", property.viewers.toString())
        PropertyDetail("Type", property.type)
    }
}

@Composable
private fun PropertyDetail(label: String, value: String) {
    Text(
        text = "$label: $value",
        fontSize = 18.sp,
        modifier = Modifier.padding(vertical = 8.dp)
    )
}