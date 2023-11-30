package com.example.mobileapplicationproject.feature_goal.ui_layer.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.width
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.example.mobileapplicationproject.feature_goal.data.util.GoalOrder
import com.example.mobileapplicationproject.feature_goal.data.util.OrderType

@Composable
fun OrderSection(
    modifier: Modifier = Modifier,
    goalOrder: GoalOrder = GoalOrder.Title(OrderType.Descending),
    onOrderChange: (GoalOrder) -> Unit
) {
    Column (
        modifier = modifier
    ){
        Row(
            modifier = Modifier.fillMaxWidth()
        ){
            DefaultRadioButton(
                txt = "Title",
                selected = goalOrder is GoalOrder.Title,
                onSelect = { onOrderChange(GoalOrder.Title(goalOrder.orderType)) }
            )
            Spacer(modifier = Modifier.width(8.dp))
            DefaultRadioButton(
                txt = "Deadline",
                selected = goalOrder is GoalOrder.Deadline,
                onSelect = { onOrderChange(GoalOrder.Title(goalOrder.orderType)) }
            )
        }
        Spacer(modifier = Modifier.height((16.dp)))
        Row(
            modifier = Modifier.fillMaxWidth()
        ){
            DefaultRadioButton(
                txt = "Ascending",
                selected = goalOrder.orderType is OrderType.Ascending,
                onSelect = { onOrderChange(goalOrder.copy(OrderType.Ascending)) }
            )
            Spacer(modifier = Modifier.width(8.dp))
            DefaultRadioButton(
                txt = "Descending",
                selected = goalOrder.orderType is OrderType.Descending,
                onSelect = { onOrderChange(goalOrder.copy(OrderType.Descending)) }
            )
        }
    }
}