class BookException(Exception):
    """
        Custom exception for the Book class
    """
    def __init__(self, text):
        """
        :param text: the error message
        """
        self.__text = text

    def __str__(self):
        """
        :return: the error message
        """
        return self.__text


class ClientException(Exception):
    """
    Custom exception for the client
    """
    def __init__(self, text):
        """
        :param text: the error message
        """
        self.__text = text

    def __str__(self):
        """
        :return: the error message
        """
        return self.__text


class RentalException(Exception):
    """
    custom exception for rental
    """
    def __init__(self, text):
        """
        :param text: the error message
        """
        self.__text = text

    def __str__(self):
        """
        :return: the error message
        """
        return self.__text


class UndoRedoException(Exception):
    """
    custom exception for rental
    """
    def __init__(self, text):
        """
        :param text: the error message
        """
        self.__text = text

    def __str__(self):
        """
        :return: the error message
        """
        return self.__text
