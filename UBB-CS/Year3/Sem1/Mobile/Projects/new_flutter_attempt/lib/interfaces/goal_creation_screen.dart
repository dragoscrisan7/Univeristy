import 'package:flutter/material.dart';
import '../model/goals.dart';
import '../model/goals_view_model.dart';

class GoalCreationScreen extends StatefulWidget {
  final GoalViewModel viewModel;
  final Function(Goal) onGoalCreated;

  GoalCreationScreen({required this.viewModel, required this.onGoalCreated});

  @override
  _GoalCreationScreenState createState() => _GoalCreationScreenState();
}

class _GoalCreationScreenState extends State<GoalCreationScreen> {
  TextEditingController _titleController = TextEditingController();
  TextEditingController _descriptionController = TextEditingController();
  TextEditingController _deadlineController = TextEditingController();
  TextEditingController _miniGoalsController = TextEditingController();
  bool _isPrivate = false;

  bool _isButtonEnabled() {
    return _titleController.text.isNotEmpty &&
        _descriptionController.text.isNotEmpty &&
        _deadlineController.text.isNotEmpty &&
        !_isTitleError &&
        !_isDescriptionError &&
        !_isDeadlineError;
  }

  bool _isTitleError = false;
  bool _isDescriptionError = false;
  bool _isDeadlineError = false;

  @override
  Widget build(BuildContext context) {
    final regexPattern = RegExp(r"^\d{2}/\d{2}/\d{4}$");

    return Scaffold(
      appBar: AppBar(
        title: Text("Create a New Goal"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Text(
              "Create a New Goal",
              style: TextStyle(fontWeight: FontWeight.bold, fontSize: 24.0),
              textAlign: TextAlign.center,
            ),
            TextField(
              controller: _titleController,
              onChanged: (value) {
                setState(() {
                  _isTitleError = value.isEmpty || value.length > 20;
                });
              },
              decoration: InputDecoration(labelText: "Title", errorText: _isTitleError ? "Title is required" : null),
            ),
            TextField(
              controller: _descriptionController,
              onChanged: (value) {
                setState(() {
                  _isDescriptionError = value.isEmpty;
                });
              },
              decoration: InputDecoration(labelText: "Description", errorText: _isDescriptionError ? "Description is required" : null),
            ),
            TextField(
              controller: _deadlineController,
              onChanged: (value) {
                setState(() {
                  _isDeadlineError = !regexPattern.hasMatch(value);
                });
              },
              decoration: InputDecoration(labelText: "Deadline (dd/mm/yyyy)", errorText: _isDeadlineError ? "Invalid deadline format" : null),
            ),
            Row(
              children: [
                Checkbox(
                  value: _isPrivate,
                  onChanged: (value) {
                    setState(() {
                      _isPrivate = value ?? false;
                    });
                  },
                ),
                Text("Private Goal"),
              ],
            ),
            TextField(
              controller: _miniGoalsController,
              decoration: InputDecoration(labelText: "Mini-Goals"),
            ),
            ElevatedButton(
              onPressed: _isButtonEnabled()
                  ? () {
                final newGoalId = widget.viewModel.getNewGoalId();
                final newGoal = Goal(
                  id: newGoalId,
                  title: _titleController.text,
                  description: _descriptionController.text,
                  deadline: _deadlineController.text,
                  isPrivate: _isPrivate,
                  miniGoals: _miniGoalsController.text.split("\n"),
                );
                widget.onGoalCreated(newGoal);
              }
                  : null,
              child: Text("Create Goal"),
            ),
          ],
        ),
      ),
    );
  }
}
