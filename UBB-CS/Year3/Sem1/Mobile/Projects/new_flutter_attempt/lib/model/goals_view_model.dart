import 'package:flutter/material.dart';
import 'goals.dart';

class GoalViewModel extends ChangeNotifier {
  final List<Goal> _goals = [];
  int _lastAssignedId = 0;

  GoalViewModel() {
    // Initialize with some example goals
    addGoal(Goal(
      id: getNewGoalId(),
      title: "Learn a new language",
      description: "Become fluent in Spanish",
      deadline: "2024-12-31",
      isPrivate: true,
      miniGoals: ["Complete Duolingo lessons", "Practice speaking with native speakers"],
    ));
    addGoal(Goal(
      id: getNewGoalId(),
      title: "Exercise regularly",
      description: "Stay fit and healthy",
      deadline: "2024-06-30",
      isPrivate: false,
      miniGoals: ["Run 5 miles a week", "Strength training"],
    ));
  }

  int getNumberOfGoals() {
    return _goals.length;
  }

  List<Goal> getGoals() {
    return List.from(_goals);
  }

  void addGoal(Goal goal) {
    // Check if a goal with the same title already exists
    final existingGoal = _goals.firstWhere((g) => g.title == goal.title, orElse: () => Goal(id: -1, title: "", description: "", deadline: "", isPrivate: false, miniGoals: []));
    if (existingGoal.id == -1) {
      _goals.add(goal);
      notifyListeners();
      _lastAssignedId++;
    }
  }

  int getNewGoalId() {
    return _lastAssignedId;
  }

  int getGoalId(String title) {
    return _goals.indexWhere((g) => g.title == title);
  }

  void updateGoal(Goal updatedGoal) {
    final index = _goals.indexWhere((g) => g.id == updatedGoal.id);
    if (index != -1) {
      _goals[index] = updatedGoal;
      notifyListeners();
    }
  }

  void deleteGoal(String title) {
    _goals.removeWhere((g) => g.title == title);
    notifyListeners();
  }

  Goal? getGoalByTitle(String title) {
    try {
      return _goals.firstWhere((g) => g.title == title);
    } catch (e) {
      return null;
    }
  }
}