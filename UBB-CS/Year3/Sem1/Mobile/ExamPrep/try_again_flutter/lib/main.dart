import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:try_again_flutter/screen/car_organizer/add_car_screen.dart';
import 'package:try_again_flutter/screen/car_organizer/view_all_cars_screen.dart';
import 'package:try_again_flutter/screen/staff/view_car_types_screen.dart';
import 'package:try_again_flutter/screen/supplier/view_car_orders_screen.dart'; // Import the supplier screen

import 'model/local_database_repository.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MultiProvider(
      providers: [
        ChangeNotifierProvider<LocalDatabaseRepository>(
          create: (_) => LocalDatabaseRepository(),
        ),
      ],
      child: MaterialApp(
        title: 'Your App Title',
        theme: ThemeData(
          primarySwatch: Colors.blue,
          visualDensity: VisualDensity.adaptivePlatformDensity,
        ),
        home: HomeScreen(),
      ),
    );
  }
}

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  int _selectedIndex = 0;

  static List<Widget> _widgetOptions = <Widget>[
    ViewAllCarsScreen(), // Car Section
    ViewCarTypesScreen(), // Staff Section
    ViewCarOrdersScreen(), // Supplier Section
  ];

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Your App'),
      ),
      body: _widgetOptions.elementAt(_selectedIndex),
      bottomNavigationBar: BottomNavigationBar(
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.list),
            label: 'Car Section', // Changed label
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.supervisor_account),
            label: 'Staff Section', // Changed label
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.shopping_cart),
            label: 'Supplier Section', // Supplier label
          ),
        ],
        currentIndex: _selectedIndex,
        selectedItemColor: Colors.blue,
        onTap: _onItemTapped,
      ),
    );
  }
}
