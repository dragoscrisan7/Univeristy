import 'dart:async'; // Import async for StreamController
import 'package:flutter/material.dart';

import '../../model/local_database_repository.dart';
import 'add_car_screen.dart'; // Import LocalDatabaseRepository

class ViewAllCarsScreen extends StatefulWidget {
  @override
  _ViewAllCarsScreenState createState() => _ViewAllCarsScreenState();
}

class _ViewAllCarsScreenState extends State<ViewAllCarsScreen> {
  final LocalDatabaseRepository _repository = LocalDatabaseRepository();

  // Define a StreamController for connected status
  late StreamController<ConnectionStatus> _connectionStreamController;

  @override
  void initState() {
    super.initState();
    _repository.initializeRepository();

    // Initialize StreamController and listen to changes in connected status
    _connectionStreamController = StreamController<ConnectionStatus>();
    _repository.connected.addListener(() {
      _connectionStreamController.add(_repository.connected.value);
    });
  }

  @override
  void dispose() {
    _connectionStreamController.close(); // Close the StreamController
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('All Cars'),
      ),
      body: StreamBuilder(
        stream: _connectionStreamController.stream, // Use the StreamController's stream
        builder: (context, snapshot) {
          if (snapshot.connectionState == ConnectionState.waiting) {
            return CircularProgressIndicator();
          }

          if (snapshot.data == ConnectionStatus.DISCONNECTED) {
            return _buildOfflineMessage(context);
          }

          return _buildCarList();
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          // Navigate to AddCarScreen and pass callback function to refresh the list
          await Navigator.push(
            context,
            MaterialPageRoute(
              builder: (context) => AddCarScreen(
                onCarAdded: () {
                  setState(() {
                    // Refresh the list of cars
                    _repository.fetchCars();
                  });
                },
              ),
            ),
          );
        },
        child: Icon(Icons.add),
      ),
    );
  }

  Widget _buildOfflineMessage(BuildContext context) {
    return Center(
      child: Text('You are currently offline. Please connect to the internet.'),
    );
  }

  Widget _buildCarList() {
    return ListView.builder(
      itemCount: _repository.availableCars.length,
      itemBuilder: (context, index) {
        final car = _repository.availableCars[index];
        return ListTile(
          title: Text('${car['id']} - ${car['name']}'),
          subtitle: Text('Supplier: ${car['supplier']}, Type: ${car['type']}'),
          onTap: () {
            // Navigate to car details page passing car details
            Navigator.push(
              context,
              MaterialPageRoute(
                builder: (context) => CarDetailsScreen(car: car),
              ),
            );
          },
        );
      },
    );
  }
}

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
