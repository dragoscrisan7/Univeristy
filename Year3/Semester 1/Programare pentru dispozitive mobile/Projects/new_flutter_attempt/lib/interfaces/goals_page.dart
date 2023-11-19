import 'package:flutter/material.dart';
import '../components/goal_display_list.dart';
import '../model/goals_view_model.dart';
import 'goal_creation_screen.dart';
import 'goal_update_screen.dart';
import 'goal_delete_screen.dart';

class MainScreen extends StatefulWidget {
  @override
  _MainScreenState createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  late GoalViewModel viewModel;

  @override
  void initState() {
    super.initState();
    // Initialize your view model
    viewModel = GoalViewModel(); // Replace this with your actual initialization logic
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Goals App'),
      ),
      body: GoalList(
        viewModel: viewModel,
        onEditClick: (goal) {
          // Handle edit click: Navigate to goal update screen
          Navigator.push(
            context,
            MaterialPageRoute(
              builder: (context) => GoalUpdateScreen(
                viewModel: viewModel,
                goal: goal,
                onUpdate: (updatedGoal) {
                  // Handle the updated goal
                  viewModel.updateGoal(updatedGoal);
                  // Close the update screen and refresh the goal list
                  Navigator.pop(context);
                  setState(() {});
                },
              ),
            ),
          );
        },
        onDeleteClick: (goal) {
          // Handle delete click: Show delete confirmation dialog
          showDialog(
            context: context,
            builder: (context) => DeleteConfirmationDialog(
              onConfirmDelete: () {
                // Handle goal deletion
                viewModel.deleteGoal(goal.title);
                // Close the delete confirmation dialog and refresh the goal list
                Navigator.pop(context);
                setState(() {});
              },
              onDismiss: () {
                // Close the delete confirmation dialog
                Navigator.pop(context);
              },
            ),
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          // Navigate to the "Create Goal" screen
          Navigator.push(
            context,
            MaterialPageRoute(
              builder: (context) => GoalCreationScreen(
                viewModel: viewModel,
                onGoalCreated: (newGoal) {
                  // Handle the newly created goal
                  viewModel.addGoal(newGoal);
                  // Close the create goal screen and refresh the goal list
                  Navigator.pop(context);
                  setState(() {});
                },
              ),
            ),
          );
        },
        child: Icon(Icons.add),
      ),
    );
  }
}
