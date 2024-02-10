import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class ViewCarOrdersScreen extends StatefulWidget {
  @override
  _ViewCarOrdersScreenState createState() => _ViewCarOrdersScreenState();
}

class _ViewCarOrdersScreenState extends State<ViewCarOrdersScreen> {
  List<Map<String, dynamic>> carOrders = [];

  Future<void> fetchCarOrders() async {
    final url = Uri.parse("http://10.0.2.2:2406/carorders");
    final response = await http.get(url);

    if (response.statusCode == 200) {
      final List<dynamic> data = jsonDecode(response.body);
      setState(() {
        carOrders = data.map((order) => Map<String, dynamic>.from(order)).toList();
      });
    } else {
      // Handle error
      print('Failed to fetch car orders: ${response.statusCode}');
    }
  }

  @override
  void initState() {
    super.initState();
    fetchCarOrders();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Car Orders'),
      ),
      body: carOrders.isEmpty
          ? Center(
        child: Text('No orders available.'),
      )
          : ListView.builder(
        itemCount: carOrders.length,
        itemBuilder: (context, index) {
          final order = carOrders[index];
          return ListTile(
            title: Text('Order ID: ${order['id']}'),
            subtitle: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text('Car: ${order['car']}'),
                Text('Quantity: ${order['quantity']}'),
                Text('Customer: ${order['customer']}'),
                Text('Date: ${order['date']}'),
              ],
            ),
          );
        },
      ),
    );
  }
}
