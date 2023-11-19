import 'package:flutter/material.dart';
import '../model/goals.dart';
import '../model/goals_view_model.dart';

class GoalUpdateScreen extends StatefulWidget {
  final GoalViewModel viewModel;
  final Goal goal;
  final Function(Goal) onUpdate;

  GoalUpdateScreen({required this.viewModel, required this.goal, required this.onUpdate});

  @override
  _GoalUpdateScreenState createState() => _GoalUpdateScreenState();
}

class _GoalUpdateScreenState extends State<GoalUpdateScreen> {
  TextEditingController _updatedTitleController = TextEditingController();
  TextEditingController _updatedDescriptionController = TextEditingController();
  TextEditingController _updatedDeadlineController = TextEditingController();
  TextEditingController _updatedMiniGoalsController = TextEditingController();
  bool _updatedIsPrivate = false;

  bool _isButtonEnabled() {
    return _updatedTitleController.text.isNotEmpty &&
        _updatedDescriptionController.text.isNotEmpty &&
        _updatedDeadlineController.text.isNotEmpty &&
        !_isTitleError &&
        !_isDescriptionError &&
        !_isDeadlineError;
  }

  bool _isTitleError = false;
  bool _isDescriptionError = false;
  bool _isDeadlineError = false;

  @override
  void initState() {
    super.initState();
    _updatedTitleController.text = widget.goal.title;
    _updatedDescriptionController.text = widget.goal.description;
    _updatedDeadlineController.text = widget.goal.deadline;
    _updatedIsPrivate = widget.goal.isPrivate;
    _updatedMiniGoalsController.text = widget.goal.miniGoals.join("\n");
  }

  @override
  Widget build(BuildContext context) {
    final regexPattern = RegExp(r"^\d{2}/\d{2}/\d{4}$");

    return Scaffold(
      appBar: AppBar(
        title: Text("Update a Goal"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Text(
              "Update a Goal",
              style: TextStyle(fontWeight: FontWeight.bold, fontSize: 24.0),
              textAlign: TextAlign.center,
            ),
            TextField(
              controller: _updatedTitleController,
              onChanged: (value) {
                setState(() {
                  _isTitleError = value.isEmpty || value.length > 20;
                });
              },
              decoration: InputDecoration(labelText: "Title", errorText: _isTitleError ? "Title is required" : null),
            ),
            TextField(
              controller: _updatedDescriptionController,
              onChanged: (value) {
                setState(() {
                  _isDescriptionError = value.isEmpty;
                });
              },
              decoration: InputDecoration(labelText: "Description", errorText: _isDescriptionError ? "Description is required" : null),
            ),
            TextField(
              controller: _updatedDeadlineController,
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
                  value: _updatedIsPrivate,
                  onChanged: (value) {
                    setState(() {
                      _updatedIsPrivate = value ?? false;
                    });
                  },
                ),
                Text("Private Goal"),
              ],
            ),
            TextField(
              controller: _updatedMiniGoalsController,
              decoration: InputDecoration(labelText: "Mini-Goals"),
            ),
            ElevatedButton(
              onPressed: _isButtonEnabled()
                  ? () {
                final updatedGoal = Goal(
                  id: widget.viewModel.getGoalId(widget.goal.title),
                  title: _updatedTitleController.text,
                  description: _updatedDescriptionController.text,
                  deadline: _updatedDeadlineController.text,
                  isPrivate: _updatedIsPrivate,
                  miniGoals: _updatedMiniGoalsController.text.split("\n"),
                );
                widget.onUpdate(updatedGoal);
              }
                  : null,
              child: Text("Update Goal"),
            ),
          ],
        ),
      ),
    );
  }
}
