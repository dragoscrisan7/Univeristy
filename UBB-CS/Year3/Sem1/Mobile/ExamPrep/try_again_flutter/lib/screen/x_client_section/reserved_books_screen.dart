// import 'package:flutter/material.dart';
// import 'package:provider/provider.dart';
// import '../../model/book.dart';
// import '../../model/local_database_repository.dart';
//
// class ReservedBooksScreen extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: Text('Reserved Books'),
//       ),
//       body: Consumer<LocalDatabaseRepository>(
//         builder: (context, repository, _) {
//           List<Book> reservedBooks = repository.reservedBooks;
//           return ListView.builder(
//             itemCount: reservedBooks.length,
//             itemBuilder: (context, index) {
//               Book book = reservedBooks[index];
//               return ListTile(
//                 title: Text(book.title),
//                 subtitle: Text(book.author),
//                 trailing: IconButton(
//                   icon: Icon(Icons.library_books),
//                   onPressed: () async {
//                     // Borrow the book
//                     bool success = await repository.borrowBook(book.id);
//                     // Show AlertDialog with borrow status and book details
//                     showDialog(
//                       context: context,
//                       builder: (context) {
//                         return AlertDialog(
//                           title: Text(success ? 'Book Borrowed Successfully' : 'Failed to Borrow Book'),
//                           content: Column(
//                             mainAxisSize: MainAxisSize.min,
//                             crossAxisAlignment: CrossAxisAlignment.start,
//                             children: [
//                               Text('Title: ${book.title}'),
//                               Text('Author: ${book.author}'),
//                               Text('Genre: ${book.genre}'),
//                               Text('Quantity: ${book.quantity}'),
//                               Text('Reserved: ${book.reserved}'),
//                             ],
//                           ),
//                           actions: [
//                             TextButton(
//                               onPressed: () {
//                                 Navigator.pop(context);
//                               },
//                               child: Text('Close'),
//                             ),
//                           ],
//                         );
//                       },
//                     );
//                   },
//                 ),
//               );
//             },
//           );
//         },
//       ),
//     );
//   }
// }
