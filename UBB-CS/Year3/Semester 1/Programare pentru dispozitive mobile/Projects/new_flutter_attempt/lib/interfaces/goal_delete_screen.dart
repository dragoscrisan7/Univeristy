import 'package:flutter/material.dart';

class DeleteConfirmationDialog extends StatelessWidget {
  final VoidCallback onConfirmDelete;
  final VoidCallback onDismiss;

  DeleteConfirmationDialog({required this.onConfirmDelete, required this.onDismiss});

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text("Confirm Deletion"),
      content: Text("Are you sure you want to delete this goal?"),
      actions: [
        TextButton(
          onPressed: () {
            onDismiss();
          },
          child: Text("Cancel"),
        ),
        TextButton(
          onPressed: () {
            onConfirmDelete();
            onDismiss();
          },
          child: Text("Delete"),
        ),
      ],
    );
  }
}
