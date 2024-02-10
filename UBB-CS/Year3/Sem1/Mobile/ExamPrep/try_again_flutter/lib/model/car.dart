class Car {
  int id;
  String name;
  String supplier;
  String details;
  String status;
  int quantity;
  String type;

  Car({
    required this.id,
    required this.name,
    required this.supplier,
    required this.details,
    required this.status,
    required this.quantity,
    required this.type,
  });

  factory Car.fromJson(Map<String, dynamic> json) {
    return Car(
      id: json['id'],
      name: json['name'],
      supplier: json['supplier'],
      details: json['details'],
      status: json['status'],
      quantity: json['quantity'],
      type: json['type'],
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'name': name,
      'supplier': supplier,
      'details': details,
      'status': status,
      'quantity': quantity,
      'type': type,
    };
  }
}

class CarDTO {
  String name;
  String supplier;
  String details;
  String status;
  int quantity;
  String type;

  CarDTO({
    required this.name,
    required this.supplier,
    required this.details,
    required this.status,
    required this.quantity,
    required this.type,
  });

  factory CarDTO.fromJson(Map<String, dynamic> json) {
    return CarDTO(
      name: json['name'],
      supplier: json['supplier'],
      details: json['details'],
      status: json['status'],
      quantity: json['quantity'],
      type: json['type'],
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'supplier': supplier,
      'details': details,
      'status': status,
      'quantity': quantity,
      'type': type,
    };
  }
}
