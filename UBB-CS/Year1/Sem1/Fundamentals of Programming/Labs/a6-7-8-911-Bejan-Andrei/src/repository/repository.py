from src.domain.movie import Movie
from src.domain.client import Client
from src.domain.rental import Rental
import random


class MovieRepository:

    def __init__(self):
        self.__movies = dict()

    def __getitem__(self, item):
        return self.__movies[item]

    def initiate_movies(self):
        self.add_entity(Movie(self.generate_id(), "Harry Potter",
                              "\n     Harry Potter is a series of seven fantasy novels written by British author \n"
                              "  J. K. Rowling. The novels chronicle the lives of a young wizard, Harry Potter, \n"
                              "  and his friends Hermione Granger and Ron Weasley, all of whom are students at \n"
                              "  Hogwarts School of Witchcraft and Wizardry.",
                              "Fantasy"))

        self.add_entity(Movie(self.generate_id(), "The Godfather",
                              "\n     The Godfather is an American film series that consists of three crime films \n"
                              "  directed by Francis Ford Coppola inspired by the 1969 novel of the same name \n"
                              "  by Italian American author Mario Puzo.",
                              "Crime/Drama"))

        self.add_entity(Movie(self.generate_id(), "The Wolf of Wall Street",
                              "\n     Introduced to life in the fast lane through stockbroking, Jordan Belfort takes \n"
                              "  a hit after a Wall Street crash. He teams up with Donnie Azoff, cheating his way to \n"
                              "  the top as his relationships slide.",
                              "Drama/Dark Comedy"))

        self.add_entity(Movie(self.generate_id(), "The Walk",
                              "\n     Philippe Petit, a French street performer, dreams of performing daring \n"
                              "  stunts. He attempts to walk between the Twin Towers of the World Trade Center \n"
                              "  in New York on a tightrope.",
                              "Adventure/Drama"))

        self.add_entity(Movie(self.generate_id(), "Grown Ups",
                              "\n     Five childhood friends take their families for a weekend trip to a lake house \n"
                              "  in their hometown, where they reunite to attend the funeral of their former high \n"
                              "  school basketball coach.",
                              "Comedy/Buddy"))

        self.add_entity(Movie(self.generate_id(), "Grown Ups 2",
                              "\n     Lenny Feder moves his family to his hometown and looks forward to spending \n"
                              "  time with his old friends. However, he and his companions soon face bizarre \n"
                              "  situations and new enemies.",
                              "Comedy/Buddy"))

        self.add_entity(Movie(self.generate_id(), "Uncle Drew",
                              "\n     After draining his life savings to enter a team in the Rucker Classic street \n"
                              "  ball tournament in Harlem, Dax is dealt a series of setbacks, including losing his \n"
                              "  team to his longtime rival. Desperate to win the tournament and the cash prize, Dax \n"
                              "  stumbles upon the man, the myth, the legend Uncle Drew and convinces him to return \n"
                              "  to the court one more time. The two men embark on a road trip to round up Drew's \n"
                              "  old basketball squad and prove that a group of septuagenarians can still win the \n"
                              "  big one.",
                              "Comedy/Sport"))

        self.add_entity(Movie(self.generate_id(), "Coach Carter",
                              "\n    A sports goods store owner accepts the job of basketball coach for his old \n"
                              "  high school where he was a champion athlete. Dismayed by the attitudes of his \n"
                              "  players, he sets out to change things.",
                              "Sport/Drama"))

        self.add_entity(Movie(self.generate_id(), "White Men Can't Jump",
                              "\n    Billy, a hustler, makes a living out of conning African American players into \n"
                              "  believing that he cannot play basketball. He teams up with Sidney, one of his \n"
                              "  victims, to double his chances.",
                              "Comedy/Sport"))

        self.add_entity(Movie(self.generate_id(), "The Count of Monte Cristo",
                              "\n    Dantes, a sailor is falsely accused of treason by his best friend Fernand, \n"
                              "  who wants Dantes' girlfriend Mercedes for himself. Dantes is imprisoned on the \n"
                              "  island prison of Chateau d'If for 13 years.",
                              "Adventure/Romance"))

    def add_entity(self, entity):
        try:
            if int(entity.movie_id) in self.__movies:
                raise ValueError(f"Entity with ID {entity.movie_id} already in repo!\n")
            self.__movies[int(entity.movie_id)] = entity
        except ValueError as ve:
            print(str(ve))

    def remove_entity(self, _id):
        try:
            exists = False
            for movie in self.__movies:
                if int(self.__movies[movie].movie_id) == int(_id):
                    self.__movies.pop(movie)
                    exists = True
                    break
            if not exists:
                raise ValueError(f"The ID {_id} does not exist!\n")
        except ValueError as ve:
            print(str(ve))

    def update_entity(self, _id, title, description, genre):
        try:
            found = False
            for movie in self.__movies:
                if int(self.__movies[movie].movie_id) == int(_id):
                    self.__movies[movie].title = title
                    self.__movies[movie].genre = genre
                    self.__movies[movie].description = description
                    found = True
                    break
            if not found:
                raise ValueError(f"The ID {_id} has not been found!")
        except ValueError as ve:
            print(str(ve))
            print()

    def display_movies(self):
        movies = []
        for movie in self.__movies:
            movie_to_print = f"Movie with ID {self.__movies[movie].movie_id}:\n" \
                             f" -title: {self.__movies[movie].title}\n" \
                             f" -genre: {self.__movies[movie].genre}\n" \
                             f" -description: {self.__movies[movie].description} \n"
            movies.append(movie_to_print)
        return movies

    def get_movies(self):
        movies = []
        for movie in self.__movies:
            movies.append(self.__movies[movie])
        return movies

    def generate_id(self):
        n = random.randint(100, 999)
        while n in self.__movies:
            n = random.randint(100, 999)
        return n

    @staticmethod
    def test_add_entity():
        repo = MovieRepository()
        repo.add_entity(Movie("100", "Movie 1", "Description 1", "Genre 1"))
        repo.add_entity(Movie("101", "Movie 2", "Description 2", "Genre 2"))
        assert repo[100].movie_id == "100"
        assert repo[100].title == "Movie 1"
        assert repo[100].description == "Description 1"
        assert repo[100].genre == "Genre 1"
        assert repo[101].movie_id == "101"
        assert repo[101].title == "Movie 2"
        assert repo[101].description == "Description 2"
        assert repo[101].genre == "Genre 2"

    @staticmethod
    def test_remove_entity():
        repo = MovieRepository()
        repo.add_entity(Movie("100", "Movie 1", "Description 1", "Genre 1"))
        repo.add_entity(Movie("101", "Movie 2", "Description 2", "Genre 2"))
        repo.remove_entity("101")
        assert len(repo.get_movies()) == 1

    @staticmethod
    def test_update_entity():
        repo = MovieRepository()
        repo.add_entity(Movie("100", "Movie 1", "Description 1", "Genre 1"))
        repo.add_entity(Movie("101", "Movie 2", "Description 2", "Genre 2"))
        repo.update_entity("101", "Movie 3", "Description 3", "Genre 3")
        assert repo[101].movie_id == "101"
        assert repo[101].title == "Movie 3"
        assert repo[101].description == "Description 3"
        assert repo[101].genre == "Genre 3"


class ClientRepository:

    def __init__(self):
        self.__clients = dict()

    def __getitem__(self, item):
        return self.__clients[item]

    def initiate_clients(self):
        self.add_entity(Client(self.generate_id(), "t"))  # testing purposes
        self.add_entity(Client(self.generate_id(), "Lilly Brady"))
        self.add_entity(Client(self.generate_id(), "Emir Bullock"))
        self.add_entity(Client(self.generate_id(), "Vickie Francis"))
        self.add_entity(Client(self.generate_id(), "Mirna Markham"))
        self.add_entity(Client(self.generate_id(), "Tallulah Mccabe"))
        self.add_entity(Client(self.generate_id(), "Jaden Cameron"))
        self.add_entity(Client(self.generate_id(), "Esa Dennis"))
        self.add_entity(Client(self.generate_id(), "Halima Levine"))
        self.add_entity(Client(self.generate_id(), "Kamil Head"))
        self.add_entity(Client(self.generate_id(), "Myron Larsen"))

    def generate_id(self):
        n = random.randint(100, 999)
        while n in self.__clients:
            n = random.randint(100, 999)
        return n

    def add_entity(self, entity):
        try:
            if int(entity.client_id) in self.__clients:
                raise ValueError(f"Entity with ID {str(entity.client_id)} already in repo!\n")
            self.__clients[int(entity.client_id)] = entity
        except ValueError as ve:
            print(str(ve))
            print()

    def remove_entity(self, _id):
        try:
            exists = False
            for client in self.__clients:
                if int(self.__clients[client].client_id) == int(_id):
                    self.__clients.pop(client)
                    exists = True
                    break
            if not exists:
                raise ValueError(f"The ID {_id} does not exist!\n")
        except ValueError as ve:
            print(str(ve))

    def update_entity(self, _id, name):
        try:
            found = False
            for client in self.__clients:
                if int(self.__clients[client].client_id) == int(_id):
                    self.__clients[client].name = name
                    found = True
                    break
            if not found:
                raise ValueError(f"The ID {_id} has not been found!")
        except ValueError as ve:
            print(str(ve))
            print()

    def display_clients(self):
        clients = []
        for client in self.__clients:
            client_to_print = f"Name: {self.__clients[client].name}, ID: {self.__clients[client].client_id}"
            clients.append(client_to_print)
        return clients

    def get_clients(self):
        clients = []
        for client in self.__clients:
            clients.append(self.__clients[client])
        return clients

    @staticmethod
    def test_add_entity():
        repo = ClientRepository()
        repo.add_entity(Client("100", "Client 1"))
        repo.add_entity(Client("101", "Client 2"))
        assert repo[100].client_id == "100"
        assert repo[100].name == "Client 1"
        assert repo[101].client_id == "101"
        assert repo[101].name == "Client 2"

    @staticmethod
    def test_remove_entity():
        repo = ClientRepository()
        repo.add_entity(Client("100", "Client 1"))
        repo.add_entity(Client("101", "Client 2"))
        repo.remove_entity("101")
        assert len(repo.get_clients()) == 1

    @staticmethod
    def test_update_entity():
        repo = ClientRepository()
        repo.add_entity(Client("100", "Client 1"))
        repo.add_entity(Client("101", "Client 2"))
        repo.update_entity("101", "Client 3")
        assert repo[101].client_id == "101"
        assert repo[101].name == "Client 3"


class RentalRepository:
    def __init__(self):
        self.__rented_movies = dict()
        self.__movie_repo = dict()
        self.__client_repo = dict()
        self.__rental_id = "1000"

    def rent_movie(self, movies, clients, movie_title, client_name):
        try:
            self.search_movie(movies, movie_title)
            self.search_client(clients, client_name)
            self.add_movie(movies, movie_title, clients, client_name)
        except ValueError as ve:
            print(str(ve))

    def return_movie(self, movies, clients, movie_title, client_name):
        try:
            self.search_movie(movies, movie_title)
            self.search_client(clients, client_name)
            self.remove_movie(movies, movie_title)
        except ValueError as ve:
            print(str(ve))

    @staticmethod
    def search_movie(movies, movie_title):
        found = False
        for movie in movies:
            if movie.title == movie_title:
                found = True
                break
        if not found:
            raise ValueError("The movie does not exist!\n")

    @staticmethod
    def search_client(clients, client_name):
        found = False
        for client in clients:
            if client.name == client_name:
                found = True
                break
        if not found:
            raise ValueError("The client is not registered yet!\n")

    def add_movie(self, movies, movie_title, clients, client_name):
        c_id = ''
        for client in clients:
            if client.name == client_name:
                c_id = client.client_id
                break

        can_rent = True
        for rental in self.__rented_movies:
            if self.__rented_movies[rental].client_id == c_id and not \
               self.__rented_movies[rental].returned_date <= self.__rented_movies[rental].due_date:
                can_rent = False

        if can_rent:
            movie_id = ''
            client_id = ''
            rental_id = self.__rental_id
            for movie in movies:
                if movie.title == movie_title:
                    movie_id = movie.movie_id

            for client in clients:
                if client.name == client_name:
                    client_id = client.client_id

            rented_date = input("Enter the day you rent the movie: ")
            due_date = input("Enter the day the movie has to be returned: ")
            returned_date = input("Enter the day you returned the movie: ")
            print()
            rental = Rental(rental_id, movie_id, client_id, rented_date, due_date, returned_date)
            self.__rented_movies[int(rental_id)] = rental
            self.__rental_id = str(int(self.__rental_id) + 1)
        else:
            raise ValueError("The client didn't return a movie in time!\n")

    def remove_movie(self, movies, movie_title):
        m_id = ''
        for movie in movies:
            if movie.title == movie_title:
                m_id = movie.movie_id
                break
        for rental in self.__rented_movies:
            if self.__rented_movies[rental].movie_id == m_id:
                self.__rented_movies.pop(rental)
                break
        print()

    def display_rentals(self):
        rentals = []
        for rental in self.__rented_movies:
            print(str(self.__rented_movies[rental].client_id) + " " + str(self.__rented_movies[rental].movie_id) +
                  " " + str(self.__rented_movies[rental].rental_id))
        return rentals


MovieRepository.test_add_entity()
MovieRepository.test_remove_entity()
MovieRepository.test_update_entity()
ClientRepository.test_add_entity()
ClientRepository.test_remove_entity()
ClientRepository.test_update_entity()
