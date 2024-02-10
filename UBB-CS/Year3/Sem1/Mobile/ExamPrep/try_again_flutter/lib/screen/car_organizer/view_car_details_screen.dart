import 'package:flutter/material.dart';

class CarDetailsScreen extends StatelessWidget {
  final Map<String, dynamic> car;

  const CarDetailsScreen({Key? key, required this.car}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Car Details'),
      ),
      body: SingleChildScrollView(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            ListTile(
              title: Text('Name'),
              subtitle: Text(car['name']),
            ),
            ListTile(
              title: Text('Supplier'),
              subtitle: Text(car['supplier']),
            ),
            ListTile(
              title: Text('Details'),
              subtitle: Text(car['details']),
            ),
            ListTile(
              title: Text('Status'),
              subtitle: Text(car['status']),
            ),
            ListTile(
              title: Text('Quantity'),
              subtitle: Text(car['quantity'].toString()),
            ),
            ListTile(
              title: Text('Type'),
              subtitle: Text(car['type']),
            ),
          ],
        ),
      ),
    );
  }
}
