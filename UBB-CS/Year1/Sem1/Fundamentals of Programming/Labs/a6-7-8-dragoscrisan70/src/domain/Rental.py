from src.domain.Exceptions import RentalException


class Rental:
    """
    A class that represents a rental through a rental ID, a book ID, a client ID, a rented date, and a returned date
    """
    def __init__(self, rental_id, book_id, client_id, rented_date, returned_date):
        """
        :param rental_id: the ID of the rental
        :type: integer, positive number
        :param book_id: the ID of the book that was rented
        :type: integer, positive number
        :param client_id: the ID of the client that rented
        :type: integer, positive number
        :param rented_date: the start date of the rental
        :type: date, YY/MM/DD format
        :param returned_date: the end date of the rental
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        """
        self.__rental_id = -1
        self.set_rental_id(rental_id)
        self.__book_id = -1
        self.set_book_id(book_id)
        self.__client_id = -1
        self.set_client_id(client_id)
        self.__rented_date = "-1"
        self.set_rented_date(rented_date)
        self.__returned_date = "-1"
        self.set_returned_date(returned_date)

    def get_rental_id(self):
        """
        :return: rental id
        """
        return self.__rental_id

    def set_rental_id(self, new):
        """
        sets new rental id to the new value
        :param new: new value for rental id
        :type: integer, positive number
        """
        if new < 0:
            raise RentalException("The rental ID cannot be less than 0.")

        self.__rental_id = new

    def get_book_id(self):
        """
        :return: book id
        """
        return self.__book_id

    def set_book_id(self, new):
        """
        sets new book id to the new value
        :param new: new value for book id
        :type: integer, positive number
        """
        if new < 0:
            raise RentalException("The book ID cannot be less than 0.")

        self.__book_id = new

    def get_rented_date(self):
        """
        :return: rented date
        """
        return self.__rented_date

    def set_rented_date(self, new):
        """
        sets the rented date to the new value
        :param new: new value for the rented date
        :type: integer, positive number
        """
        if len(new) != 10 and new[2] != "/" and new[5] != "/":
            raise RentalException("Invalid rented date! Please use the following format: dd/mm/yyyy")

        self.__rented_date = new

    def get_client_id(self):
        """
        :return: client id
        """
        return self.__client_id

    def set_client_id(self, new):
        """
        sets the client id to the new value
        :param new: new value for the client id
        :type: date, YY/MM/DD format
        """
        if new < 0:
            raise RentalException("Invalid client ID! The client ID cannot be less than 0.")

        self.__client_id = new

    def get_returned_date(self):
        """
        :return: returned date
        """
        return self.__returned_date

    def set_returned_date(self, new):
        """
        sets the returned date to the new value
        :param new: new value for the returned date
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        """
        if new == "-1":
            self.__returned_date = "-1"
            return None

        if len(new) != 10 and new[2] != "/" and new[5] != "/":
            raise RentalException("Invalid returned date! Please use the following format: dd/mm/yyyy")

        self.__returned_date = new

    def __str__(self):
        """
        :return: the string representation of a rental
        """
        return str(self.__rental_id) + " | Book with ID: " + str(self.__book_id) +\
            " rented by client with ID: " + str(self.__client_id) + " at date: " + self.__rented_date +\
            ("; Not returned yet" if self.__returned_date == "-1" else ("; Returned at date: " + self.__returned_date))

    def __eq__(self, other):
        """
        :param other: other rental
        :return: true if the rentals are the same, false otherwise
        """
        return isinstance(other, Rental) and self.__rental_id == other.get_rental_id()
