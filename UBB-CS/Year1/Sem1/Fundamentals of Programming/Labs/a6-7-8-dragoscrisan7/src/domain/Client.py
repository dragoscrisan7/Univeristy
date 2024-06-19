from src.domain.Exceptions import ClientException


class Client:
    """
    A class that represents a client through an ID and a name
    """
    def __init__(self, client_id, name):
        """
        :param client_id: the ID of the client
        :type: integer, positive number
        :param name: the name of the client
        :type: string, text
        """
        self.__client_id = -1
        self.set_client_id(client_id)
        self.__name = ""
        self.set_name(name)

    def get_client_id(self):
        """
        :return: the client's id
        """
        return self.__client_id

    def set_client_id(self, new):
        """
        sets the new id to the value new
        :param new: new id for the client
        :type: integer, positive number
        """
        if new < 0:
            raise ClientException("The client ID cannot be less than 0.")
        self.__client_id = new

    def get_name(self):
        """
        :return: client's name
        """
        return self.__name

    def set_name(self, new):
        """
        sets the new name
        :param new: new name for the client
        :type: string, text
        """
        if len(new) == 0:
            raise ClientException("The author name cannot be empty.")
        self.__name = new

    def __str__(self):
        """
        :return: the string representation of a client
        """
        return "(" + str(self.__client_id) + ", " + self.__name + ")"

    def __eq__(self, other):
        """
        :param other: other client
        :return: true if the clients are the same, false otherwise
        """
        return isinstance(other, Client) and self.__client_id == other.get_client_id()
