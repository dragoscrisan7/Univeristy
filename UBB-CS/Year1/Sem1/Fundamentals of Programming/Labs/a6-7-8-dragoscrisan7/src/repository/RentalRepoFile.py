from src.domain.Rental import Rental
from src.repository.Exceptions import RepositoryException

from datetime import datetime


class RentalRepositoryFile:
    """
    A class for the rental repository
    """
    def __init__(self, filename):
        """
        Constructor for the RentalRepository class
        """
        self.__filename = filename
        self.__repo = []

    def update_file(self):
        self.__repo.clear()
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    rental_id = int(parts[0])
                    book_id = int(parts[1])
                    client_id = int(parts[2])
                    rented_date = parts[3]
                    returned_date = parts[4]
                    rental = Rental(rental_id, book_id, client_id, rented_date, returned_date)
                    self.__repo.append(rental)

    def get_repo(self):
        """
        :return: the internal list
        """
        self.update_file()
        return self.__repo

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.update_file()
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
        self.update_file()
        cont = 0
        for rents in self.__repo:
            if book_id == rents.get_book_id():
                cont += 1
        return cont

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        self.update_file()
        return list(self.__repo)

    def find_by_client_id(self, client_id):
        """
        counts the amount of times a client has rented a book
        :param client_id: the identifier for the author who's rentals we are counting
        :type: integer, positive number
        :return: the number of rentals
        """
        self.update_file()
        cont = 0
        for rents in self.__repo:
            if client_id == rents.get_client_id():
                if rents.get_returned_date() == "-1":
                    cont += RentalRepositoryFile.time_to_num(datetime.today().strftime('%Y/%m/%d'),
                                                         rents.get_rented_date()).days
                else:
                    cont += RentalRepositoryFile.time_to_num(rents.get_returned_date(), rents.get_rented_date()).days
        return cont

    def rent(self, new_rental):
        """
        Adds a new rental to the repository
        :param new_rental: the new rental
        :type: an object belonging to the Rental class
        """
        self.update_file()
        for rental in self.__repo:
            if rental.get_rental_id() == new_rental.get_rental_id():
                raise RepositoryException("Duplicate rental ID!")
        with open(self.__filename, 'a') as f:
            f.write(f"{new_rental.get_rental_id()},{new_rental.get_book_id()},{new_rental.get_client_id()},"
                    f"{new_rental.get_rented_date()},{new_rental.get_returned_date()}\n")

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
        ok = 0
        with open(self.__filename, 'r+') as f:
            lines = f.readlines()
            f.seek(0)
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    if int(parts[0]) != rental_id:
                        f.write(line+"\n")
                    else:
                        f.write(f"{parts[0]},{parts[1]},{parts[2]},{start},{end}\n")
                        ok = 1

        if ok == 0:
            raise RepositoryException("There is no rental with the given ID!")

    def remove(self, rental_id):
        """
        Removes a rental from the repository
        :param rental_id: the rental ID
        :type: integer, positive number
        """
        ok = 0
        with open(self.__filename, 'r+') as f:
            lines = f.readlines()
            f.seek(0)
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    if int(parts[0]) != rental_id:
                        f.write(line+"\n")
                    else:
                        ok = 1
            f.truncate()
        if ok == 0:
            raise RepositoryException("There is no rental with the given ID!")

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
