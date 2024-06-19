from src.domain.Book import Book
from src.services.UndoService import Call, CascadedOperation, Operation


class BookService:
    """
    A service for the BookRepository class
    """
    def __init__(self, repository, rental_repo, undo_service, rental_service):
        """
        :param repository: the book repository
        """
        self.__repository = repository
        self.__rental_repo = rental_repo
        self.__undo_service = undo_service
        self.__rental_service = rental_service

    def create(self, book_id, title, author):
        """
        :param book_id: the id of the book
        :type: integer, positive
        :param title: the title of the book
        :type: string, text
        :param author: the author of the book
        :type: string, text
        """
        book = Book(book_id, title, author)
        self.__repository.add(book)

        undo_call = Call(self.delete_without_undo, book_id)
        redo_call = Call(self.create_without_undo, book_id, title, author)
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

    def create_without_undo(self, book_id, title, author):
        """
        :param book_id: the id of the book
        :type: integer, positive
        :param title: the title of the book
        :type: string, text
        :param author: the author of the book
        :type: string, text
        """
        book = Book(book_id, title, author)
        self.__repository.add(book)

    def get(self):
        """
        :return: the internal list of the repository
        """
        return self.__repository

    def get_all(self):
        """
         :return: a list of the entire repo, necessary for tests
         :type: list
         """
        return self.__repository.get_all_entities()

    def get_with_book_id(self, book_id):
        """
        searches for the book with the given id and returns the data about it in a list, necessary for undo
        :param book_id: the id of the book
        :type: integer, positive
        :return: the data of the book, under a list
        """
        updated_book = None
        for book in self.__repository.get_repo():
            if book.get_book_id() == book_id:
                updated_book = (book.get_book_id(), book.get_title(), book.get_author())

        return updated_book

    def delete(self, book_id):
        """
        deletes a book from the book repository
        :param book_id: the id of the book
        :type: integer, positive
        """
        book = self.get_with_book_id(book_id)
        self.__repository.remove(book_id)

        undo_call = Call(self.create_without_undo, book[0], book[1], book[2])
        redo_call = Call(self.delete_without_undo, book[0])
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        rentals = self.__rental_service.filter_rentals(None, book_id)
        for rent in rentals:
            undo_call = Call(self.__rental_service.create_rental_without_undo, rent.get_rental_id(), rent.get_book_id(),
                             rent.get_client_id(), rent.get_rented_date(), rent.get_returned_date())
            redo_call = Call(self.__rental_service.remove_rental, rent.get_rental_id())
            cope.add(Operation(undo_call, redo_call))
            self.__rental_repo.remove(rent.get_rental_id())

        self.__undo_service.record(cope)

    def delete_without_undo(self, book_id):
        """
        deletes a book from the book repository
        :param book_id: the id of the book
        :type: integer, positive
        """
        self.__repository.remove(book_id)

    def update(self, book_id, title, author):
        """
        modifies a book's title or/and author, if it has the matching id
        :param book_id: the id of the book
        :type: integer, positive
        :param title: the new title
        :type: string, text
        :param author: the new author
        :type: string, text
        """
        book = self.get_with_book_id(book_id)
        self.__repository.update(book_id, title, author)
        undo_call = Call(self.update, book[0], book[1], book[2])
        redo_call = Call(self.update, book[0], book[1], book[2])
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

    def list(self):
        """
        :return: a string containing the list of books
        """
        return self.__repository.list()

    def search(self, choice, data):
        """
        :return: the books that match the search criteria
        """
        return self.__repository.search(choice, data)
