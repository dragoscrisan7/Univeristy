// import 'package:flutter/material.dart';
// import 'package:provider/provider.dart';
// import '../model/book.dart';
// import '../model/local_database_repository.dart';
// import 'update_screen.dart';
//
// class PriceScreenWidget extends StatelessWidget {
//   const PriceScreenWidget({Key? key}) : super(key: key);
//
//   @override
//   Widget build(BuildContext context) {
//     final storage = Provider.of<LocalDatabaseRepository>(context);
//     final items = storage.getDiscountedItems();
//
//     return Scaffold(
//       appBar: AppBar(
//         title: const Text("Intensity Section"),
//         actions: [
//           PopupMenuButton(
//             itemBuilder: (context) => [
//               const PopupMenuItem<int>(
//                 value: 0,
//                 child: Text("Main"),
//               ),
//             ],
//             onSelected: (value) {
//               if (value == 0) {
//                 Navigator.pop(context);
//               }
//             },
//           ),
//         ],
//       ),
//       body: FutureBuilder<List<Entity>>(
//         future: items,
//         builder: (context, snapshot) {
//           if (snapshot.connectionState == ConnectionState.waiting) {
//             return const Center(child: CircularProgressIndicator());
//           } else if (storage.connected.value == ConnectionStatus.DISCONNECTED) {
//             return const Center(child: Text("You are not connected!"));
//           } else if (snapshot.hasError) {
//             return const Center(child: Text("Error loading data"));
//           } else {
//             final entities = snapshot.data!;
//             return ListView.builder(
//               padding: const EdgeInsets.all(8),
//               itemCount: entities.length,
//               itemBuilder: (BuildContext context, int index) {
//                 return Card(
//                   color: Colors.white70,
//                   child: ListTile(
//                     title: Column(
//                       crossAxisAlignment: CrossAxisAlignment.start,
//                       children: [
//                         Text("Name: ${entities[index].name}"),
//                         Text("Description: ${entities[index].description}"),
//                         Text("Image: ${entities[index].image}"),
//                         Text("Units: ${entities[index].units}"),
//                         Text("Price: ${entities[index].price}"),
//                       ],
//                     ),
//                     trailing: ElevatedButton(
//                       onPressed: () {
//                         Navigator.of(context).push(
//                           MaterialPageRoute<void>(
//                             builder: (context) => UpdateScreenState(entities[index]),
//                           ),
//                         );
//                       },
//                       child: const Text("Update"),
//                     ),
//                   ),
//                 );
//               },
//             );
//           }
//         },
//       ),
//     );
//   }
// }
