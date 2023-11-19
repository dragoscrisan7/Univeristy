// lib/goals.dart
class Goal {
  final int id;
  final String title;
  final String description;
  final String deadline;
  final bool isPrivate;
  final List<String> miniGoals;

  Goal({
    required this.id,
    required this.title,
    required this.description,
    required this.deadline,
    required this.isPrivate,
    required this.miniGoals,
  });

  // Factory constructor to create a Goal instance from a map (e.g., from JSON)
  factory Goal.fromJson(Map<String, dynamic> json) {
    return Goal(
      id: json['id'],
      title: json['title'],
      description: json['description'],
      deadline: json['deadline'],
      isPrivate: json['isPrivate'],
      miniGoals: List<String>.from(json['miniGoals']),
    );
  }

  // Method to convert Goal instance to a map (e.g., to JSON)
  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'title': title,
      'description': description,
      'deadline': deadline,
      'isPrivate': isPrivate,
      'miniGoals': miniGoals,
    };
  }
}