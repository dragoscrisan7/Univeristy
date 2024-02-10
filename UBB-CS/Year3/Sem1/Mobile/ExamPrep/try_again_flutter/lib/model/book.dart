class Book {
  int id;
  String title;
  String author;
  String genre;
  int quantity;
  int reserved;

  Book({
    required this.id,
    required this.title,
    required this.author,
    required this.genre,
    required this.quantity,
    required this.reserved,
  });

  factory Book.fromJson(Map<String, dynamic> json) {
    return Book(
      id: json['id'],
      title: json['title'],
      author: json['author'],
      genre: json['genre'],
      quantity: int.parse(json['quantity'].toString()),
      reserved: int.parse(json['reserved'].toString()),
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'title': title,
      'author': author,
      'genre': genre,
      'quantity': quantity,
      'reserved': reserved,
    };
  }
}

class BookDTO {
  String title;
  String author;
  String genre;
  int quantity;
  int reserved;

  BookDTO({
    required this.title,
    required this.author,
    required this.genre,
    required this.quantity,
    required this.reserved,
  });

  factory BookDTO.fromJson(Map<String, dynamic> json) {
    return BookDTO(
      title: json['title'],
      author: json['author'],
      genre: json['genre'],
      quantity: json['quantity'],
      reserved: json['reserved'],
    );
  }

  Map<String, dynamic> toMap() {
    return {
      'title': title,
      'author': author,
      'genre': genre,
      'quantity': quantity,
      'reserved': reserved,
    };
  }
}