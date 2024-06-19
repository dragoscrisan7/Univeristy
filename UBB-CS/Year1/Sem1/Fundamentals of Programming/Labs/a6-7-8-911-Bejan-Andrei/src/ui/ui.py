from src.domain.movie import Movie
from src.domain.client import Client


class Ui:
    def __init__(self, movie_service, client_service, rental_service):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service

    @staticmethod
    def display_menu():
        print("1. Add movie.")
        print("2. Add client.")
        print("3. Remove movie.")
        print("4. Remove client.")
        print("5. Update movie.")
        print("6. Update client.")
        print("7. List movies.")
        print("8. List clients.")
        print("9. Rent movie.")
        print("10. Return movie.")
        print("11. Show rentals.")
        print("0. Exit program.")
        print()

    @staticmethod
    def user_input():
        return input("prompt> ")

    def user_input_movie(self):
        valid = False
        _id = ''
        title = ''
        genre = ''
        description = ''
        while not valid:
            try:
                _id = input("ID: ")
                self.check_id(_id)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()

        valid = False
        while not valid:
            try:
                title = input("Title: ")
                self.check_title(title)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()

        valid = False
        while not valid:
            try:
                genre = input("Genre: ")
                self.check_genre(genre)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()

        valid = False
        while not valid:
            try:
                description = input("Description: ")
                self.check_description(description)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()

        movie = Movie(_id, title, description, genre)
        return movie

    def user_input_client(self):
        valid = False
        _id = ''
        name = ''
        while not valid:
            try:
                _id = input("ID: ")
                self.check_id(_id)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()

        valid = False
        while not valid:
            try:
                name = input("Name: ")
                self.check_name(name)
                valid = True
            except ValueError as ve:
                print(str(ve))
                print()
        client = Client(_id, name)
        return client

    def user_input_movie_id(self):
        valid = False
        while not valid:
            try:
                _id = input("Enter the movie ID: ")
                self.check_id(_id)
                valid = True
                print()
                return _id
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_client_id(self):
        valid = False
        while not valid:
            try:
                _id = input("Enter the client ID: ")
                self.check_id(_id)
                valid = True
                print()
                return _id
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_movie_title(self):
        valid = False
        while not valid:
            try:
                title = input("Enter the movie title: ")
                self.check_title(title)
                valid = True
                return title
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_movie_genre(self):
        valid = False
        while not valid:
            try:
                genre = input("Enter the movie genre: ")
                self.check_genre(genre)
                valid = True
                return genre
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_movie_description(self):
        valid = False
        while not valid:
            try:
                description = input("Enter the movie description: ")
                self.check_title(description)
                valid = True
                return description
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_client_name_rental(self):
        valid = False
        while not valid:
            try:
                name = input("The name under you want to rent the movie: ")
                self.check_name(name)
                valid = True
                return name
            except ValueError as ve:
                print(str(ve))
                print()

    def user_input_client_name_return(self):
        valid = False
        while not valid:
            try:
                name = input("The name under you want to return the movie: ")
                self.check_name(name)
                valid = True
                return name
            except ValueError as ve:
                print(str(ve))
                print()

    @staticmethod
    def check_id(_id):
        if not isinstance(int(_id), int):
            raise ValueError("Enter a number!\n")

    @staticmethod
    def check_title(title):
        if not isinstance(title, str):
            raise ValueError("Enter a string!\n")

    @staticmethod
    def check_genre(genre):
        if not isinstance(genre, str):
            raise ValueError("Enter a string!\n")

    @staticmethod
    def check_description(description):
        if not isinstance(description, str):
            raise ValueError("Enter a string!\n")

    @staticmethod
    def check_name(name):
        if not isinstance(name, str):
            raise ValueError("Enter a string!\n")

    def display_movies(self):
        movies = self.__movie_service.display_movies()
        for movie in movies:
            print(movie)
        print()

    def display_clients(self):
        clients = self.__client_service.display_clients()
        for client in clients:
            print(client)
        print()

    def display_rentals(self):
        rentals = self.__rental_service.display_rentals()
        for rental in rentals:
            print(rental)
        print()

    def get_movies(self):
        movies = self.__movie_service.get_movies()
        return movies

    def get_clients(self):
        clients = self.__client_service.get_clients()
        return clients

    def start(self):
        self.__movie_service.initiate_movies()
        self.__client_service.initiate_clients()
        self.display_menu()
        while True:
            try:
                command = self.user_input()
                if command == "1":  # add movie
                    movie = self.user_input_movie()
                    self.__movie_service.add_movie(movie)
                elif command == "2":  # add client
                    client = self.user_input_client()
                    self.__client_service.add_client(client)
                elif command == "3":  # remove movie
                    _id = self.user_input_movie_id()
                    self.__movie_service.remove_movie(_id)
                elif command == "4":  # remove client
                    _id = self.user_input_client_id()
                    self.__client_service.remove_client(_id)
                elif command == "5":  # update movie
                    _id = self.user_input_movie_id()
                    title = self.user_input_movie_title()
                    genre = self.user_input_movie_genre()
                    description = self.user_input_movie_id()
                    self.__movie_service.update_movie(_id, title, genre, description)
                elif command == "6":  # update client
                    _id = self.user_input_client_id()
                    self.__client_service.update_client(_id)
                elif command == "7":  # show movies
                    self.display_movies()
                elif command == "8":  # show clients
                    self.display_clients()
                elif command == "9":  # rent a movie
                    title = self.user_input_movie_title()
                    client_name = self.user_input_client_name_rental()
                    movies = self.get_movies()
                    clients = self.get_clients()
                    self.__rental_service.rent_movie(movies, clients, title, client_name)
                elif command == "10":  # return a movie
                    title = self.user_input_movie_title()
                    client_name = self.user_input_client_name_return()
                    movies = self.get_movies()
                    clients = self.get_clients()
                    self.__rental_service.return_movie(movies, clients, title, client_name)
                elif command == "11":  # show rentals
                    self.display_rentals()
                elif command == "0":  # exit program
                    return
            except ValueError as ve:
                print(str(ve))
                print()
