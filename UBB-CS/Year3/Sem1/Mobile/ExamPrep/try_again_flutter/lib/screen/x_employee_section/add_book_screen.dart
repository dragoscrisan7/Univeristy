// import 'package:flutter/material.dart';
// import 'package:http/http.dart' as http;
//
// class AddBookScreen extends StatefulWidget {
//   final VoidCallback? onBookAdded;
//
//   const AddBookScreen({Key? key, this.onBookAdded}) : super(key: key);
//
//   @override
//   _AddBookScreenState createState() => _AddBookScreenState();
// }
//
// class _AddBookScreenState extends State<AddBookScreen> {
//   final _formKey = GlobalKey<FormState>();
//
//   TextEditingController _titleController = TextEditingController();
//   TextEditingController _authorController = TextEditingController();
//   TextEditingController _genreController = TextEditingController();
//   TextEditingController _quantityController = TextEditingController();
//   TextEditingController _reservedController = TextEditingController();
//
//   @override
//   void dispose() {
//     _titleController.dispose();
//     _authorController.dispose();
//     _genreController.dispose();
//     _quantityController.dispose();
//     _reservedController.dispose();
//     super.dispose();
//   }
//
//   Future<void> _addBook() async {
//     if (_formKey.currentState!.validate()) {
//       final title = _titleController.text.trim();
//       final author = _authorController.text.trim();
//       final genre = _genreController.text.trim();
//       final quantity = int.parse(_quantityController.text.trim());
//       final reserved = int.parse(_reservedController.text.trim());
//
//       final url = Uri.parse("http://10.0.2.2:2429/book");
//
//       try {
//         final response = await http.post(
//           url,
//           body: {
//             'title': title,
//             'author': author,
//             'genre': genre,
//             'quantity': quantity.toString(),
//             'reserved': reserved.toString(),
//           },
//         );
//
//         if (response.statusCode == 200) {
//           // Book added successfully
//           ScaffoldMessenger.of(context).showSnackBar(
//             SnackBar(
//               content: Text('Book added successfully'),
//             ),
//           );
//
//           // Call the callback function to notify the parent widget
//           widget.onBookAdded?.call();
//
//           // Navigate back to the previous screen
//           Navigator.of(context).pop();
//         } else {
//           // Error adding book
//           ScaffoldMessenger.of(context).showSnackBar(
//             SnackBar(
//               content: Text('Failed to add book'),
//             ),
//           );
//         }
//       } catch (e) {
//         // Error communicating with server
//         ScaffoldMessenger.of(context).showSnackBar(
//           SnackBar(
//             content: Text('Error: $e'),
//           ),
//         );
//       }
//     }
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Add New Book'),
//       ),
//       body: SingleChildScrollView(
//         child: Padding(
//           padding: EdgeInsets.all(16.0),
//           child: Form(
//             key: _formKey,
//             child: Column(
//               crossAxisAlignment: CrossAxisAlignment.start,
//               children: <Widget>[
//                 TextFormField(
//                   controller: _titleController,
//                   decoration: InputDecoration(labelText: 'Title'),
//                   validator: (value) {
//                     if (value == null || value.isEmpty) {
//                       return 'Please enter a title';
//                     }
//                     return null;
//                   },
//                 ),
//                 TextFormField(
//                   controller: _authorController,
//                   decoration: InputDecoration(labelText: 'Author'),
//                   validator: (value) {
//                     if (value == null || value.isEmpty) {
//                       return 'Please enter an author';
//                     }
//                     return null;
//                   },
//                 ),
//                 TextFormField(
//                   controller: _genreController,
//                   decoration: InputDecoration(labelText: 'Genre'),
//                   validator: (value) {
//                     if (value == null || value.isEmpty) {
//                       return 'Please enter a genre';
//                     }
//                     return null;
//                   },
//                 ),
//                 TextFormField(
//                   controller: _quantityController,
//                   keyboardType: TextInputType.number,
//                   decoration: InputDecoration(labelText: 'Quantity'),
//                   validator: (value) {
//                     if (value == null || value.isEmpty) {
//                       return 'Please enter a quantity';
//                     }
//                     return null;
//                   },
//                 ),
//                 TextFormField(
//                   controller: _reservedController,
//                   keyboardType: TextInputType.number,
//                   decoration: InputDecoration(labelText: 'Reserved'),
//                   validator: (value) {
//                     if (value == null || value.isEmpty) {
//                       return 'Please enter a reserved';
//                     }
//                     return null;
//                   },
//                 ),
//                 SizedBox(height: 20),
//                 ElevatedButton(
//                   onPressed: _addBook,
//                   child: Text('Add Book'),
//                 ),
//               ],
//             ),
//           ),
//         ),
//       ),
//     );
//   }
// }
