class RentalService:

    def __init__(self, rental_repo):
        self.__repo = rental_repo

    def rent_movie(self, movies, clients, movie_title, client_name):
        self.__repo.rent_movie(movies, clients, movie_title, client_name)

    def return_movie(self, movies, clients, movie_title, client_name):
        self.__repo.return_movie(movies, clients, movie_title, client_name)

    def display_rentals(self):
        rentals = self.__repo.display_rentals()
        return rentals
