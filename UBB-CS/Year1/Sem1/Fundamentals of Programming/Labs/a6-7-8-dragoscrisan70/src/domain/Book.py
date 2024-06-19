from src.domain.Exceptions import BookException


class Book:
    """
    A class that represents a Book through an ID, a title, and an author
    """
    def __init__(self, book_id, title, author):
        """
        :param book_id: the ID of the book
        :type: integer, positive
        :param title: the title of the book
        :type: string, text
        :param author: the author of the book
        :type: string, text
        """
        self.__book_id = -1
        self.set_book_id(book_id)
        self.__title = ""
        self.set_title(title)
        self.__author = ""
        self.set_author(author)

    def get_book_id(self):
        """
        function for getting the book id
        :return: the book id
        """
        return self.__book_id

    def set_book_id(self, new):
        """
        Sets the book_id property to the given value
        :param new: the new value
        :type: int, positive integer
        """
        if int(new) < 0:
            raise BookException("Invalid book ID! The book ID cannot be less than 0.")

        self.__book_id = int(new)

    def get_title(self):
        """
        :return: the book title
        """
        return self.__title

    def set_title(self, new):
        """
        sets the new value of the book title
        :param new: new value for book title
        :type: string, text
        """
        if len(new) == 0:
            raise BookException("The book title cannot be empty.")
        self.__title = new

    def get_author(self):
        """
        :return: the book author
        """
        return self.__author

    def set_author(self, new):
        """
        sets the new value of the book author
        :param new: new value for the book author
        :type: string, text
        """
        if len(new) == 0:
            raise BookException("The book author cannot be empty.")
        self.__author = new

    def __str__(self):
        """
        :return: the string representation of a book
        """
        return "(" + str(self.__book_id) + ", " + self.__title + ":" + self.__author + ")"

    def __eq__(self, other):
        """
        :param other: other book
        :return: true if the books are the same, false otherwise
        """
        return isinstance(other, Book) and self.__book_id == other.get_book_id()
