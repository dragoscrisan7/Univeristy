from src.repository.Exceptions import RepositoryException
from src.repository.Sort_filter import IterableDataStructure

import pickle
import os.path

class BookRepositoryPickle:
    """
    A class that represents a book repository
    """
    def __init__(self, filename):
        """
        Constructor for the BookRepository class
        """
        self.__filename = filename
        self.__repo = []
        #self.__repo = IterableDataStructure([])

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

    def add(self, new_book):
        """
        Adds a new book to the repository
        :param new_book: the new book
        :type: an object belonging to the Book class
        """
        self.read()
        for book in self.__repo:
            if book.get_book_id() == new_book.get_book_id():
                raise RepositoryException("This book id already exists")

        self.__repo.append(new_book)
        self.write()

    def remove(self, book_id):
        """
        Removes a book from the repository
        :param book_id: the ID of the book
        :type: integer, positive
        """
        self.read()
        for book in self.__repo:
            if book.get_book_id() == book_id:
                del self.__repo[book_id]
                self.write()
                return None

        raise RepositoryException("There is no book with the given ID!")

    def update(self, book_id, new_title, new_author):
        """
        changes the title and/or author of a book
        :param book_id: the ID of the book that should be updated
        :type: integer, positive
        :param new_title: the new title of the book
        :type: string, text
        :param new_author: the new author of the book
        :type: string, text
        """
        self.read()
        for book in self.__repo:
            if book.get_book_id() == book_id:
                book.set_title(new_title)
                book.set_author(new_author)
                self.write()
                return None

        raise RepositoryException("There is no book with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.read()
        value = "" if len(self.__repo) > 0 else "The list of books is empty."
        for book in self.__repo:
            value += (str(book) + "\n")

        return value.rstrip()

    def search(self, choice, data):
        """
        searches for the book
        :param choice: the option selected
        :type: integer, positive, from 1 to 3
        :param data: the data selected
        :type: integer or string, depending on the option
        :return:
        """
        self.read()
        books_to_print = "" if len(self.__repo) > 0 else "The list of books is empty."
        if choice == 1:
            for book in self.__repo:
                if int(book.get_book_id()) == int(data):
                    books_to_print += (str(book) + "\n")
            if len(books_to_print) == 0:
                return RepositoryException("There is no book with the given ID!")
            else:
                return books_to_print.rstrip()
        elif choice == 2:
            for book in self.__repo:
                if book.get_title().find(data) != -1:
                    books_to_print += (str(book) + "\n")
            if len(books_to_print) == 0:
                return RepositoryException("There is no book with the given name!")
            else:
                return books_to_print.rstrip()
        elif choice == 3:
            for book in self.__repo:
                if book.get_author().find(data) != -1:
                    books_to_print += (str(book) + "\n")
            if len(books_to_print) == 0:
                return RepositoryException("There is no book with the given author!")
            else:
                return books_to_print.rstrip()

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        :type: list
        """
        self.read()
        return list(self.__repo)

    def author_list(self):
        """
        :return: a list of all the authors that have books in the book repo
        """
        self.read()
        authors = []
        for book in self.__repo:
            if not (book.get_author() in authors):
                authors.append(book.get_author())

        return authors
