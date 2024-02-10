import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

class AddCarScreen extends StatefulWidget {
  final VoidCallback? onCarAdded;

  const AddCarScreen({Key? key, this.onCarAdded}) : super(key: key);

  @override
  _AddCarScreenState createState() => _AddCarScreenState();
}

class _AddCarScreenState extends State<AddCarScreen> {
  final _formKey = GlobalKey<FormState>();

  TextEditingController _nameController = TextEditingController();
  TextEditingController _supplierController = TextEditingController();
  TextEditingController _detailsController = TextEditingController();
  TextEditingController _statusController = TextEditingController();
  TextEditingController _quantityController = TextEditingController();
  TextEditingController _typeController = TextEditingController();

  @override
  void dispose() {
    _nameController.dispose();
    _supplierController.dispose();
    _detailsController.dispose();
    _statusController.dispose();
    _quantityController.dispose();
    _typeController.dispose();
    super.dispose();
  }

  Future<void> _addCar() async {
    if (_formKey.currentState!.validate()) {
      final name = _nameController.text.trim();
      final supplier = _supplierController.text.trim();
      final details = _detailsController.text.trim();
      final status = _statusController.text.trim();
      final quantity = int.parse(_quantityController.text.trim());
      final type = _typeController.text.trim();

      final url = Uri.parse("http://10.0.2.2:2406/car");

      try {
        final response = await http.post(
          url,
          body: {
            'name': name,
            'supplier': supplier,
            'details': details,
            'status': status,
            'quantity': quantity.toString(),
            'type': type,
          },
        );

        if (response.statusCode == 200) {
          // Car added successfully
          ScaffoldMessenger.of(context).showSnackBar(
            SnackBar(
              content: Text('Car added successfully'),
            ),
          );

          // Call the callback function to notify the parent widget
          widget.onCarAdded?.call();

          // Navigate back to the previous screen
          Navigator.of(context).pop();
        } else {
          // Error adding car
          ScaffoldMessenger.of(context).showSnackBar(
            SnackBar(
              content: Text('Failed to add car'),
            ),
          );
        }
      } catch (e) {
        // Error communicating with server
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(
            content: Text('Error: $e'),
          ),
        );
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Add New Car'),
      ),
      body: SingleChildScrollView(
        child: Padding(
          padding: EdgeInsets.all(16.0),
          child: Form(
            key: _formKey,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                TextFormField(
                  controller: _nameController,
                  decoration: InputDecoration(labelText: 'Name'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter a name';
                    }
                    return null;
                  },
                ),
                TextFormField(
                  controller: _supplierController,
                  decoration: InputDecoration(labelText: 'Supplier'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter a supplier';
                    }
                    return null;
                  },
                ),
                TextFormField(
                  controller: _detailsController,
                  decoration: InputDecoration(labelText: 'Details'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter details';
                    }
                    return null;
                  },
                ),
                TextFormField(
                  controller: _statusController,
                  decoration: InputDecoration(labelText: 'Status'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter a status';
                    }
                    return null;
                  },
                ),
                TextFormField(
                  controller: _quantityController,
                  keyboardType: TextInputType.number,
                  decoration: InputDecoration(labelText: 'Quantity'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter a quantity';
                    }
                    return null;
                  },
                ),
                TextFormField(
                  controller: _typeController,
                  decoration: InputDecoration(labelText: 'Type'),
                  validator: (value) {
                    if (value == null || value.isEmpty) {
                      return 'Please enter a type';
                    }
                    return null;
                  },
                ),
                SizedBox(height: 20),
                ElevatedButton(
                  onPressed: _addCar,
                  child: Text('Add Car'),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
