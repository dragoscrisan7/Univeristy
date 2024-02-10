import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

class RequestCarsScreen extends StatefulWidget {
  final String carType;

  const RequestCarsScreen({required this.carType});

  @override
  _RequestCarsScreenState createState() => _RequestCarsScreenState();
}

class _RequestCarsScreenState extends State<RequestCarsScreen> {
  Future<void> requestCar(String carType) async {
    final url = Uri.parse('http://10.0.2.2:2406/requestcar/$carType'); // Adjust URL as per your server
    final response = await http.put(url);

    if (response.statusCode == 200) {
      // Handle success
      print('Car requested successfully');
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(
        content: Text('Car requested successfully'),
      ));
      // Navigate back to the list of cars
      Navigator.pop(context);
    } else {
      // Handle error
      print('Failed to request car: ${response.statusCode}');
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(
        content: Text('Failed to request car: ${response.statusCode}'),
      ));
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Request Cars'),
      ),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: Text(
              'Car Type Selected: ${widget.carType}',
              style: TextStyle(fontWeight: FontWeight.bold),
            ),
          ),
          ElevatedButton(
            onPressed: () {
              requestCar(widget.carType);
            },
            child: Text('Request Car'),
          ),
        ],
      ),
    );
  }
}
