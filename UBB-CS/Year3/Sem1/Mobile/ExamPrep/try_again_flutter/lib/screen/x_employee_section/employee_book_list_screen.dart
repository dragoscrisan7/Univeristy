// import 'package:flutter/material.dart';
// import 'package:provider/provider.dart';
// import '../../model/local_database_repository.dart';
// import '../../model/book.dart';
// import 'add_book_screen.dart';
//
// class EmployeeBookListScreen extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Employee Book List'),
//       ),
//       body: Consumer<LocalDatabaseRepository>(
//         builder: (context, repository, _) {
//           // Sort the available books by genre and quantity
//           repository.availableBooks.sort((a, b) {
//             int genreComparison = a['genre']!.compareTo(b['genre']!);
//             if (genreComparison != 0) {
//               return genreComparison;
//             } else {
//               // Sort by quantity in ascending order
//               return int.parse(a['quantity']!) - int.parse(b['quantity']!);
//             }
//           });
//
//           return ListView.builder(
//             itemCount: repository.availableBooks.length,
//             itemBuilder: (context, index) {
//               Map<String, String> bookData = repository.availableBooks[index];
//               return ListTile(
//                 title: Text(bookData['title'] ?? ''),
//                 subtitle: Text('${bookData['author']} - ${bookData['genre']}'),
//                 trailing: Text('Quantity: ${bookData['quantity']}'),
//               );
//             },
//           );
//         },
//       ),
//       floatingActionButton: FloatingActionButton(
//         onPressed: () {
//           Navigator.push(
//             context,
//             MaterialPageRoute(builder: (context) => AddBookScreen(
//               onBookAdded: () {
//                 // Refresh the book list when a new book is added
//                 Provider.of<LocalDatabaseRepository>(context, listen: false)
//                     .fetchEmployeeBooks();
//               },
//             )),
//           );
//         },
//         tooltip: 'Add Book',
//         child: Icon(Icons.add),
//       ),
//     );
//   }
// }
