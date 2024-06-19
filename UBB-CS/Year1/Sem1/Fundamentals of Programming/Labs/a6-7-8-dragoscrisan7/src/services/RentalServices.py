from src.domain.Rental import Rental
from src.repository.Exceptions import RepositoryException
from src.services.UndoService import Call, CascadedOperation, Operation


class RentalService:
    """
    Service for rental operations
    """
    def __init__(self, rental_repo, book_repo, client_repo, undo_service):
        """
        :param rental_repo: the rental repo
        :param book_repo: the book repo
        :param client_repo: the client repo
        """
        self.__bookRepo = book_repo
        self.__clientRepo = client_repo
        self.__rental_repo = rental_repo
        self.__undo_service = undo_service

    def filter_rentals(self, client, book):
        """
        :param client: the id of a client (None = all)
        :type: integer, positive number
        :param book: the id of a book (None = all)
        :type: integer, positive number
        :return: a list of rentals performed by the provided client for the provided book
        """
        result = []
        for rental in self.__rental_repo.get_repo():
            if client is not None and rental.get_client_id() != client:
                continue
            if book is not None and rental.get_book_id() != book:
                continue
            result.append(rental)

        return result

    def create_rental(self, rental_id, book_id, client_id, start, end):
        """
        Adds a new rental to the repository
        :param rental_id: the rental ID
        :type: integer, positive number
        :param book_id: the ID of the book
        :type: integer, positive number
        :param client_id: the ID of the client
        :type: integer, positive number
        :param start: the rental start date
        :type: date, YY/MM/DD format
        :param end: the end of the rental
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        """
        rental = Rental(rental_id, book_id, client_id, start, end)

        rentals = self.filter_rentals(None, book_id)
        for rent in rentals:
            if start <= rent.get_rented_date() or\
                    (rent.get_returned_date() != "-1" and start >= rent.get_returned_date()):
                continue

            raise RepositoryException("The book is not available at the current time!")

        self.__rental_repo.rent(rental)

        undo_call = Call(self.remove_rental, rental_id)
        redo_call = Call(self.create_rental, rental_id, book_id, client_id, start, end)
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

    def create_rental_without_undo(self, rental_id, book_id, client_id, start, end):
        """
        Adds a new rental to the repository
        :param rental_id: the rental ID
        :type: integer, positive number
        :param book_id: the ID of the book
        :type: integer, positive number
        :param client_id: the ID of the client
        :type: integer, positive number
        :param start: the rental start date
        :type: date, YY/MM/DD format
        :param end: the end of the rental
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        """
        rental = Rental(rental_id, book_id, client_id, start, end)

        rentals = self.filter_rentals(None, book_id)
        for rent in rentals:
            if start <= rent.get_rented_date() or\
                    (rent.get_returned_date() != "-1" and start >= rent.get_returned_date()):
                continue

            raise RepositoryException("The book is not available at the current time!")

        self.__rental_repo.rent(rental)

    def update_rental(self, rental_id, start, end):
        """
        Modifies a rental's start date and/or end date
        :param rental_id: the ID of the rental
        :type: integer, positive number
        :param end: the end date of the rental
        :type: date, YY/MM/DD format, or -1 in case it wasn't returned yet
        :param start: start date of the rental
        :type: date, YY/MM/DD format
        """
        rental = self.get_with_rental_id(rental_id)

        undo_call = Call(self.update_rental, rental[0], rental[3], rental[4])
        redo_call = Call(self.update_rental, rental_id, start, end)
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

        self.__rental_repo.update(rental_id, start, end)

    def remove_rental(self, rental_id):
        """
        Removes a rental from the repository
        :param rental_id: the ID of the rental
        :type: integer, positive number
        """
        self.__rental_repo.remove(rental_id)

    def get_repo(self):
        """
        :return: the internal list
        """
        return self.__rental_repo.get_repo()

    def list(self):
        """
        :return: a string containing the list of rentals
        """
        return self.__rental_repo.list()

    def get_all(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        return self.__rental_repo.get_all_entities()

    def most_rented_books(self):
        """
        :return: a string containing the list of books sorted
        """
        books_sorted = self.__bookRepo.get_repo()
        books_sorted.sort(reverse=True, key=lambda x: (self.__rental_repo.find_by_book_id(x.get_book_id()),
                                                       -1*x.get_book_id()))
        return books_sorted

    def most_active_clients(self):
        """
        :return: a string containing the list of clients sorted
        """
        clients_sorted = self.__clientRepo.get_repo()
        clients_sorted.sort(reverse=True, key=lambda x: (self.__rental_repo.find_by_client_id(x.get_client_id()),
                                                         -1*x.get_client_id()))
        return clients_sorted

    def most_read_authors(self):
        """
        :return: a string containing the list of authors sorted
        """
        authors_sorted = self.__bookRepo.author_list()
        authors_sorted.sort(reverse=True, key=lambda x: self.search_for_authors(x))

        return authors_sorted

    def search_for_authors(self, author):
        """
        counts the amount of times an authors books have been rented
        :param author: the author
        :type: string, text
        :return: the amount of times
        """
        cont = 0
        for rent in self.__rental_repo.get_repo():
            book_id = rent.get_book_id()
            for book in self.__bookRepo.get_repo():
                if book.get_book_id() == book_id:
                    if book.get_author() == author:
                        cont += 1

        return cont

    def get_with_rental_id(self, rental_id):
        """
        searches for the rental with the given id
        :param rental_id: the rental id
        :type: integer, positive number
        :return: a list with all the data in the rental object
        """
        updated_rental = None
        for rental in self.__rental_repo.get_repo():
            if rental.get_rental_id() == rental_id:
                updated_rental = (rental.get_rental_id(), rental.get_book_id(), rental.get_client_id(),
                                  rental.get_rented_date(), rental.get_returned_date())

        return updated_rental
