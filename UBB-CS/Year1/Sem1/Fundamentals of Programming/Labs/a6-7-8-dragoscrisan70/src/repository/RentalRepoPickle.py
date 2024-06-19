from src.repository.Exceptions import RepositoryException

from datetime import datetime
import os.path
import pickle


class RentalRepositoryPickle:
    """
    A class for the rental repository
    """
    def __init__(self, filename):
        """
        Constructor for the RentalRepository class
        """
        self.__filename = filename
        self.__repo = []

    def read(self):
        if os.path.getsize(self.__filename) > 0:
            with open(self.__filename, "rb") as f:
                self.__repo = pickle.load(f)
        else:
            self.__repo.clear()

    def write(self):
        with open(self.__filename, "wb") as f:
            pickle.dump(self.__repo, f)

    def get_repo(self):
        """
        :return: the internal list
        """
        self.read()
        return self.__repo

    def rent(self, new_rental):
        """
        Adds a new rental to the repository
        :param new_rental: the new rental
        :type: an object belonging to the Rental class
        """
        self.read()
        for rental in self.__repo:
            if rental.get_rental_id() == new_rental.get_rental_id():
                raise RepositoryException("Duplicate rental ID!")

        self.__repo.append(new_rental)
        self.write()

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
        self.read()
        for rental in self.__repo:
            if rental.get_rental_id() == rental_id:
                rental.set_returned_date(end)
                rental.set_rented_date(start)
                self.write()
                return None

        raise RepositoryException("There is no rental with the given ID!")

    def remove(self, rental_id):
        """
        Removes a rental from the repository
        :param rental_id: the rental ID
        :type: integer, positive number
        """
        self.read()
        for rental in self.__repo:
            if rental.get_rental_id() == rental_id:
                self.__repo.remove(rental)
                self.write()
                return None

        raise RepositoryException("There is no rental with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.read()
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
        self.read()
        cont = 0
        for rents in self.__repo:
            if book_id == rents.get_book_id():
                cont += 1
        return cont

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        self.read()
        return list(self.__repo)

    def find_by_client_id(self, client_id):
        """
        counts the amount of times a client has rented a book
        :param client_id: the identifier for the author who's rentals we are counting
        :type: integer, positive number
        :return: the number of rentals
        """
        self.read()
        cont = 0
        for rents in self.__repo:
            if client_id == rents.get_client_id():
                if rents.get_returned_date() == "-1":
                    cont += RentalRepositoryPickle.time_to_num(datetime.today().strftime('%Y/%m/%d'),
                                                         rents.get_rented_date()).days
                else:
                    cont += RentalRepositoryPickle.time_to_num(rents.get_returned_date(), rents.get_rented_date()).days
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
