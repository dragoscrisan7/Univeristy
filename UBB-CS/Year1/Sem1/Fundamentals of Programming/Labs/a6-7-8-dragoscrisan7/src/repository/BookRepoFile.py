from src.domain.Book import Book
from src.repository.Exceptions import RepositoryException
from src.repository.Sort_filter import IterableDataStructure


class BookRepositoryFile:
    """
    A class that represents a book repository
    """
    def __init__(self, filename):
        """
        Constructor for the BookRepository class
        """
        self.__filename = filename
        self.__repo = IterableDataStructure([])

    def update_file(self):
        del self.__repo
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    book_id = int(parts[0])
                    title = parts[1]
                    author = parts[2]
                    book = Book(book_id, title, author)
                    self.__repo.append(book)

    def get_repo(self):
        """
        :return: the internal list
        """
        self.update_file()
        return self.__repo

    def add(self, new_book):
        """
        Adds a new book to the repository
        :param new_book: the new book
        :type: an object belonging to the Book class
        """
        self.update_file()
        for book in self.__repo:
            if book.get_book_id() == new_book.get_book_id():
                raise RepositoryException("This book id already exists")
        with open(self.__filename, 'a') as f:
            f.write(f"{new_book.get_book_id()},{new_book.get_title()},{new_book.get_author()}\n")

    def remove(self, book_id):
        """
        Removes a book from the repository
        :param book_id: the ID of the book
        :type: integer, positive
        """
        ok = 0
        with open(self.__filename, 'r+') as f:
            lines = f.readlines()
            f.seek(0)
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    if int(parts[0]) != book_id:
                        f.write(line+"\n")
                    else:
                        ok = 1
            f.truncate()
        if ok == 0:
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
        ok = 0
        with open(self.__filename, 'r+') as f:
            lines = f.readlines()
            f.seek(0)
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    if int(parts[0]) != book_id:
                        f.write(line+"\n")
                    else:
                        f.write(f"{parts[0]},{new_title},{new_author}\n")
                        ok = 1

        if ok == 0:
            raise RepositoryException("There is no book with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.update_file()
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
        self.update_file()
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
        self.update_file()
        return list(self.__repo)

    def author_list(self):
        """
        :return: a list of all the authors that have books in the book repo
        """
        self.update_file()
        authors = []
        for book in self.__repo:
            if not (book.get_author() in authors):
                authors.append(book.get_author())

        return authors
