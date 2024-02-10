import 'dart:async';
import 'dart:convert';
import 'dart:developer';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:connectivity/connectivity.dart';
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';

enum ConnectionStatus { CONNECTED, CONNECTING, DISCONNECTED }

class LocalDatabaseRepository extends ChangeNotifier {
  List<Map<String, dynamic>> availableCars = [];
  ValueNotifier<ConnectionStatus> connected = ValueNotifier(ConnectionStatus.DISCONNECTED);

  List<Map<String, dynamic>> carTypes = [];

  static final String urlServer = "http://10.0.2.2:2406";

  LocalDatabaseRepository() {
    // Initialize repository
    initializeRepository();

    // Set up connectivity listener
    Connectivity().onConnectivityChanged.listen((ConnectivityResult result) {
      if (result == ConnectivityResult.none) {
        connected.value = ConnectionStatus.DISCONNECTED;
      } else {
        connected.value = ConnectionStatus.CONNECTED;
      }
    });
  }

  Future<void> initializeRepository() async {
    await fetchCars();
    await fetchCarTypes();
  }

  Future<void> fetchCarTypes() async {
    final url = Uri.parse('$urlServer/carstypes');
    final response = await http.get(url);

    if (response.statusCode == 200) {
      final List<dynamic> data = jsonDecode(response.body);
      carTypes = data.map((carType) => Map<String, dynamic>.from(carType)).toList();
    } else {
      // Handle error
      print('Failed to fetch car types: ${response.statusCode}');
    }
    notifyListeners();
  }

  Future<void> requestCar(String type) async {
    final url = Uri.parse('$urlServer/requestcar/$type');
    final response = await http.put(url);

    if (response.statusCode == 200) {
      print('Car requested successfully');
      await fetchCarTypes(); // Refresh the list of car types
    } else {
      // Handle error
      print('Failed to request car: ${response.statusCode}');
    }
  }

  Future<void> fetchCars() async {
    await checkConnectivity();
    if (connected.value == ConnectionStatus.CONNECTED) {
      connected.value = ConnectionStatus.CONNECTING;
      var url = Uri.parse('$urlServer/cars');

      final response = await http.get(url);

      if (response.statusCode == 200) {
        connected.value = ConnectionStatus.CONNECTED;
        List<Map<String, dynamic>> cars = jsonDecode(response.body).cast<Map<String, dynamic>>();

        // Update availableCars with all details from server response
        availableCars = cars.map((car) {
          return {
            'id': car['id'],
            'name': car['name'],
            'supplier': car['supplier'],
            'type': car['type'],
            'details': car['details'], // Include details
            'status': car['status'],   // Include status
            'quantity': car['quantity'], // Include quantity
          };
        }).toList();

        log('GET $urlServer/cars');
      } else {
        // Handle error
        availableCars = [];
      }
    } else {
      // Handle offline mode
      log('Currently offline, using existing available cars');
      connected.value = ConnectionStatus.DISCONNECTED;
      // Fetch available cars from local storage or cache if needed
      // availableCars = ...
    }
    notifyListeners();
  }

  Future<void> checkConnectivity() async {
    final ConnectivityResult result = await Connectivity().checkConnectivity();

    if (result == ConnectivityResult.wifi || result == ConnectivityResult.mobile) {
      connected.value = ConnectionStatus.CONNECTED;
    } else {
      connected.value = ConnectionStatus.DISCONNECTED;
    }

    log('Connected: ${connected.value}');
  }

  Future<void> addCar(Map<String, dynamic> carDetails) async {
    try {
      final response = await http.post(
        Uri.parse('$urlServer/car'),
        body: jsonEncode(carDetails),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
      );

      if (response.statusCode == 200) {
        // Update local data or notify success
        log('Car added successfully');
        await fetchCars(); // Refresh the list of cars
      } else {
        // Handle error
        log('Failed to add car');
      }
    } catch (e) {
      // Handle error
      log('Error adding car: $e');
    }
  }
}

class DatabaseHelper {
  DatabaseHelper._privateConstructor();

  static final DatabaseHelper instance = DatabaseHelper._privateConstructor();
  static const tableNameCars = 'cars';
  static Database? _database;

  Future<Database?> get database async => _database ??= await _initDatabase();

  Future<Database?> _initDatabase() async {
    try {
      Directory documentsDirectory = await getApplicationDocumentsDirectory();
      String path = join(documentsDirectory.path, 'cars.db');
      return await openDatabase(path, version: 1, onCreate: _onCreate);
    } catch (e) {
      print(e.toString());
    }
    return null;
  }

  Future<void> _onCreate(Database db, int version) async {
    await db.execute('''
      CREATE TABLE $tableNameCars (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT,
        supplier TEXT,
        type TEXT,
        details TEXT,
        status TEXT,
        quantity INTEGER
      )
    ''');
  }

  Future<int?> insertCar(Map<String, dynamic> car) async {
    Database? db = await instance.database;
    try {
      int? id = await db?.insert(tableNameCars, car);
      return id; // Return the auto-generated ID
    } catch (e) {
      print("Error inserting car: $e");
      return null;
    }
  }

  Future<List<Map<String, dynamic>>> getAllCars() async {
    Database? db = await instance.database;
    List<Map<String, dynamic>> cars = await db!.query(tableNameCars);
    return cars;
  }

  Future<void> updateCar(Map<String, dynamic> car) async {
    Database? db = await instance.database;
    await db?.update(
      tableNameCars,
      car,
      where: 'id = ?',
      whereArgs: [car['id']],
    );
  }

  Future<void> deleteCar(int id) async {
    Database? db = await instance.database;
    await db?.delete(
      tableNameCars,
      where: 'id = ?',
      whereArgs: [id],
    );
  }
}
