// import 'dart:convert';
// import 'package:flutter/material.dart';
// import 'package:http/http.dart' as http;
// import 'package:provider/provider.dart';
// import '../../model/local_database_repository.dart';
//
// class ReserveBookScreen extends StatelessWidget {
//   final int bookId;
//
//   ReserveBookScreen({required this.bookId});
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Reserve Book'),
//       ),
//       body: Center(
//         child: ElevatedButton(
//           onPressed: () {
//             reserveBook(context);
//           },
//           child: Text('Reserve Book'),
//         ),
//       ),
//     );
//   }
//
//   Future<void> reserveBook(BuildContext context) async {
//     try {
//       final response =
//       await http.put(Uri.parse('${LocalDatabaseRepository.urlServer}/reserve/$bookId'));
//       if (response.statusCode == 200) {
//         // Update local data
//         Provider.of<LocalDatabaseRepository>(context, listen: false)
//             .notifyListeners();
//         // Extract book details from the response
//         Map<String, dynamic> bookDetails = jsonDecode(response.body);
//         // Show a message with book details
//         showDialog(
//           context: context,
//           builder: (BuildContext context) {
//             return AlertDialog(
//               title: Text('Book Reserved'),
//               content: Column(
//                 crossAxisAlignment: CrossAxisAlignment.start,
//                 mainAxisSize: MainAxisSize.min,
//                 children: [
//                   Text('Title: ${bookDetails['title']}'),
//                   Text('Author: ${bookDetails['author']}'),
//                   Text('Genre: ${bookDetails['genre']}'),
//                   Text('Quantity: ${bookDetails['quantity']}'),
//                   Text('Reserved: ${bookDetails['reserved']}'),
//                 ],
//               ),
//               actions: [
//                 TextButton(
//                   onPressed: () {
//                     Navigator.of(context).pop();
//                   },
//                   child: Text('OK'),
//                 ),
//               ],
//             );
//           },
//         );
//       } else {
//         // Show an error message
//         showDialog(
//           context: context,
//           builder: (BuildContext context) {
//             return AlertDialog(
//               title: Text('Reservation Failed'),
//               content: Text('Failed to reserve the book.'),
//               actions: [
//                 TextButton(
//                   onPressed: () {
//                     Navigator.of(context).pop();
//                   },
//                   child: Text('OK'),
//                 ),
//               ],
//             );
//           },
//         );
//       }
//     } catch (e) {
//       // Handle error
//       showDialog(
//         context: context,
//         builder: (BuildContext context) {
//           return AlertDialog(
//             title: Text('Error'),
//             content: Text('An error occurred while reserving the book.'),
//             actions: [
//               TextButton(
//                 onPressed: () {
//                   Navigator.of(context).pop();
//                 },
//                 child: Text('OK'),
//               ),
//             ],
//           );
//         },
//       );
//     }
//   }
// }
