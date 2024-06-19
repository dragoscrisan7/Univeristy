class RepositoryException(Exception):
    """
    Custom exceptions for repositories
    """
    def __init__(self, text):
        """
        :param text: the error message
        """
        self.__text = text

    @property
    def text(self):
        """
        :return: the error message
        """
        return self.__text

    def __str__(self):
        """
        :return: the string representation of the error
        """
        return self.__text
