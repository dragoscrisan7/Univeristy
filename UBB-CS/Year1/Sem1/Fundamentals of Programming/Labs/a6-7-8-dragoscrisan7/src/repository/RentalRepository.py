from src.domain.Rental import Rental
from src.repository.Exceptions import RepositoryException

from random import randint
from datetime import datetime, timedelta


class RentalRepository:
    """
    A class for the rental repository
    """
    def __init__(self):
        """
        Constructor for the RentalRepository class
        """
        self.__repo = []

    def initial_load(self):
        """
        Preloads the repository with 20 randomly generated items
        """
        current_rental = 0
        available_books = list(range(20))
        available_clients = list(range(20))

        for iterator in range(20):
            if randint(0, 2) == 0:
                book = randint(0, len(available_books) - 1)
                client = randint(0, len(available_books) - 1)
                start = (datetime.today() - timedelta(randint(300, 600))).strftime('%Y/%m/%d')
                end = (datetime.today() - timedelta(randint(0, 299))).strftime('%Y/%m/%d')

                self.__repo.append(Rental(current_rental, available_books[book], available_clients[client],
                                          start, end if randint(0, 2) == 0 else "-1"))

                available_books.pop(book)
                available_clients.pop(client)
                current_rental += 1

    def get_repo(self):
        """
        :return: the internal list
        """
        return self.__repo

    def rent(self, new_rental):
        """
        Adds a new rental to the repository
        :param new_rental: the new rental
        :type: an object belonging to the Rental class
        """
        for rental in self.__repo:
            if rental.get_rental_id() == new_rental.get_rental_id():
                raise RepositoryException("Duplicate rental ID!")

        self.__repo.append(new_rental)

    def update(self, rental_id, start, end):
        """
        modifies the start date and/or end date of a rental
        :param rental_id:
        :type: integer, positive number
        :param start:
        :type: date, YY/MM/DD format
        :param end:
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        """
        for rental in self.__repo:
            if rental.get_rental_id() == rental_id:
                rental.set_returned_date(end)
                rental.set_rented_date(start)
                return None

        raise RepositoryException("There is no rental with the given ID!")

    def remove(self, rental_id):
        """
        Removes a rental from the repository
        :param rental_id: the rental ID
        :type: integer, positive number
        """
        print(rental_id)
        for rental in self.__repo:
            if rental.get_rental_id() == rental_id:
                self.__repo.remove(rental)
                return None

        raise RepositoryException("There is no rental with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        value = ""
        for rents in self.__repo:
            value += (str(rents) + "\n")

        return value.rstrip()

    def find_by_book_id(self, book_id):
        """
        counts the amount of times a book has been rented
        :param book_id: the identifier for the book who's rentals we are counting
        :type: integer, positive number
        :return: the number of rentals
        """
        cont = 0
        for rents in self.__repo:
            if book_id == rents.get_book_id():
                cont += 1
        return cont

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        return list(self.__repo)

    def find_by_client_id(self, client_id):
        """
        counts the amount of times a client has rented a book
        :param client_id: the identifier for the author who's rentals we are counting
        :type: integer, positive number
        :return: the number of rentals
        """
        cont = 0
        for rents in self.__repo:
            if client_id == rents.get_client_id():
                if rents.get_returned_date() == "-1":
                    cont += RentalRepository.time_to_num(datetime.today().strftime('%Y/%m/%d'),
                                                         rents.get_rented_date()).days
                else:
                    cont += RentalRepository.time_to_num(rents.get_returned_date(), rents.get_rented_date()).days
        return cont

    @staticmethod
    def time_to_num(time1, time2):
        """
        subtracts the start date from the end date to see how many days there are between them
        :param time1: the end date
        :type: date, YY/MM/DD format
        :param time2: the start date
        :type: date, YY/MM/DD format
        :return: the number of days between the 2 dates
        """
        start_date = datetime.strptime(time2, "%Y/%m/%d")
        end_date = datetime.strptime(time1, "%Y/%m/%d")
        diff = end_date.date()-start_date.date()

        return diff
