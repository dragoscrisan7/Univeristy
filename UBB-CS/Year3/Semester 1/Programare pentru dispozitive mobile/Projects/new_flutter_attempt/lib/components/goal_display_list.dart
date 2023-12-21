import 'package:flutter/material.dart';
import 'goal_display_item.dart';
import '../model/goals_view_model.dart';
import '../model/goals.dart';

class GoalList extends StatefulWidget {
  final GoalViewModel viewModel;
  final void Function(Goal) onEditClick; // Add this line
  final void Function(Goal) onDeleteClick; // Add this line

  GoalList({
    required this.viewModel,
    required this.onEditClick,
    required this.onDeleteClick,
  });

  @override
  _GoalListState createState() => _GoalListState();
}

class _GoalListState extends State<GoalList> {
  String deletingGoalTitle = "";
  bool showDeleteDialog = false;

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        SizedBox(height: 30.0),
        Expanded(
          child: ListView(
            children: [
              Padding(
                padding: const EdgeInsets.all(16.0),
                child: Text(
                  "List of Goals",
                  style: TextStyle(fontSize: 30.0),
                ),
              ),
              for (var goal in widget.viewModel.getGoals())
                GoalDisplayItem(
                  goal: goal,
                  onEditClick: () {
                    widget.onEditClick(goal); // Pass the goal to the callback
                  },
                  onDeleteClick: () {
                    setState(() {
                      deletingGoalTitle = goal.title;
                      showDeleteDialog = true;
                    });
                  },
                ),
            ],
          ),
        ),
        if (showDeleteDialog)
          AlertDialog(
            title: Text("Delete Confirmation"),
            content: Text("Are you sure you want to delete the goal '$deletingGoalTitle'?"),
            actions: [
              TextButton(
                onPressed: () {
                  // Close the confirmation dialog
                  setState(() {
                    showDeleteDialog = false;
                  });
                },
                child: Text("Cancel"),
              ),
              TextButton(
                onPressed: () {
                  // Handle goal deletion here (e.g., delete it in the ViewModel)
                  widget.viewModel.deleteGoal(deletingGoalTitle);
                  // Close the confirmation dialog
                  setState(() {
                    showDeleteDialog = false;
                  });
                },
                child: Text("Delete"),
              ),
            ],
          ),
      ],
    );
  }
}