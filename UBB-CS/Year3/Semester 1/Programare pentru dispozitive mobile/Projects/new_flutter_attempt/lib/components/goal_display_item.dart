import 'package:flutter/material.dart';
import '../model/goals.dart';

class GoalDisplayItem extends StatelessWidget {
  final Goal goal;
  final VoidCallback onEditClick;
  final VoidCallback onDeleteClick;

  GoalDisplayItem({
    required this.goal,
    required this.onEditClick,
    required this.onDeleteClick,
  });

  @override
  Widget build(BuildContext context) {
    return Card(
      margin: EdgeInsets.all(16.0),
      child: Padding(
        padding: const EdgeInsets.all(8.0),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  goal.title,
                  style: TextStyle(fontSize: 18.0, fontWeight: FontWeight.bold),
                ),
                Text(goal.description, style: TextStyle(fontSize: 16.0)),
                Text("Deadline: ${goal.deadline}", style: TextStyle(fontSize: 16.0)),
              ],
            ),
            Column(
              children: [
                IconButton(
                  onPressed: onEditClick,
                  icon: Icon(Icons.edit),
                  tooltip: "Edit",
                ),
                IconButton(
                  onPressed: onDeleteClick,
                  icon: Icon(Icons.delete),
                  tooltip: "Delete",
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
