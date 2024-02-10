// import 'package:flutter/material.dart';
// import 'package:provider/provider.dart';
// import '../../model/book.dart';
// import '../../model/local_database_repository.dart';
// import 'reserve_book_screen.dart';
// import 'reserved_books_screen.dart'; // Import the ReservedBooksScreen
//
// class BookListScreen extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Book List'),
//         actions: [
//           IconButton(
//             icon: Icon(Icons.list),
//             onPressed: () {
//               // Navigate to the ReservedBooksScreen
//               Navigator.push(
//                 context,
//                 MaterialPageRoute(builder: (context) => ReservedBooksScreen()),
//               );
//             },
//           ),
//         ],
//       ),
//       body: Consumer<LocalDatabaseRepository>(
//         builder: (context, repository, _) {
//           List<Map<String, String>> availableBooks =
//               repository.availableBooks;
//           return ListView.builder(
//             itemCount: availableBooks.length,
//             itemBuilder: (context, index) {
//               Map<String, String> bookData = availableBooks[index];
//               return ListTile(
//                 title: Text(bookData['title'] ?? ''),
//                 subtitle: Text(bookData['author'] ?? ''),
//                 onTap: () {
//                   // Navigate to the ReserveBookScreen and pass the book ID
//                   Navigator.of(context).push(
//                     MaterialPageRoute(
//                       builder: (context) =>
//                           ReserveBookScreen(bookId: index + 1),
//                     ),
//                   );
//                 },
//               );
//             },
//           );
//         },
//       ),
//     );
//   }
// }
