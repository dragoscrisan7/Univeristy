import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

import 'package:try_again_flutter/screen/staff/request_cars_screen.dart';

class ViewCarTypesScreen extends StatefulWidget {
  @override
  _ViewCarTypesScreenState createState() => _ViewCarTypesScreenState();
}

class _ViewCarTypesScreenState extends State<ViewCarTypesScreen> {
  List<Map<String, dynamic>> carTypes = [];

  Future<void> fetchCarTypes() async {
    final url = Uri.parse('http://10.0.2.2:2406/carstypes'); // Adjust URL as per your server
    final response = await http.get(url);

    if (response.statusCode == 200) {
      final List<dynamic> data = jsonDecode(response.body);

      // Group cars by type
      Map<String, List<dynamic>> groupedCars = {};
      data.forEach((car) {
        String type = car['type'];
        if (!groupedCars.containsKey(type)) {
          groupedCars[type] = [];
        }
        groupedCars[type]!.add(car);
      });

      // Prepare car types list
      groupedCars.forEach((type, cars) {
        int totalQuantity = cars.length;
        carTypes.add({
          'type': type,
          'totalQuantity': totalQuantity,
          'cars': cars.map((car) => '${car['name']} - ${car['status']}').toList(),
        });
      });

      setState(() {}); // Update the UI
    } else {
      // Handle error
      print('Failed to fetch car types: ${response.statusCode}');
    }
  }

  @override
  void initState() {
    super.initState();
    fetchCarTypes();
  }

  void _onCarTypeSelected(String carType) {
    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => RequestCarsScreen(carType: carType),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Car Types'),
      ),
      body: ListView.builder(
        itemCount: carTypes.length,
        itemBuilder: (context, index) {
          final type = carTypes[index];
          return Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Text(
                  '${type['type']} - Total Quantity: ${type['totalQuantity']}',
                  style: TextStyle(fontWeight: FontWeight.bold),
                ),
              ),
              Column(
                children: (type['cars'] as List<String>).map((car) {
                  return ListTile(
                    title: Text(car),
                    onTap: () {
                      _onCarTypeSelected(type['type']);
                    },
                  );
                }).toList(),
              ),
              Divider(),
            ],
          );
        },
      ),
    );
  }
}
