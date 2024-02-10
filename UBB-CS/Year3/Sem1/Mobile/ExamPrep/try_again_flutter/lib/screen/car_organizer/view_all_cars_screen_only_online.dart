import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../../model/local_database_repository.dart';
import 'add_car_screen.dart'; // Import the AddCarScreen

class ViewAllCarsScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('All Cars'),
        actions: [
          IconButton(
            icon: Icon(Icons.add),
            onPressed: () {
              Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) => AddCarScreen(), // Navigate to AddCarScreen
                ),
              );
            },
          ),
        ],
      ),
      body: Consumer<LocalDatabaseRepository>(
        builder: (context, repository, child) {
          if (repository.connected.value == ConnectionStatus.CONNECTED) {
            return _buildCarsList(repository.availableCars);
          } else {
            return _buildOfflineMessage(context, repository);
          }
        },
      ),
    );
  }

  Widget _buildCarsList(List<Map<String, dynamic>> cars) {
    return ListView.builder(
      itemCount: cars.length,
      itemBuilder: (context, index) {
        final car = cars[index];
        return ListTile(
          title: Text(car['name']),
          subtitle: Text('Supplier: ${car['supplier']} | Type: ${car['type']}'),
          trailing: Text('ID: ${car['id']}'),
        );
      },
    );
  }

  Widget _buildOfflineMessage(
      BuildContext context, LocalDatabaseRepository repository) {
    return Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Text('You are currently offline'),
          ElevatedButton(
            onPressed: () {
              repository.fetchCars();
            },
            child: Text('Retry'),
          ),
        ],
      ),
    );
  }
}
