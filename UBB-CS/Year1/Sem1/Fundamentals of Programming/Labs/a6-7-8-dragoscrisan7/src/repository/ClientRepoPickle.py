from src.repository.Exceptions import RepositoryException

import pickle
import os.path


class ClientRepositoryPickle:
    """
    A class for the client repository
    """
    def __init__(self, filename):
        """
        Constructor for the ClientRepository class
        """
        self.__filename = filename
        self.__repo = []

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
        :return: the clients repository list
        """
        self.read()
        return self.__repo

    def add(self, new_client):
        """
        Adds a new client to the repository
        :param new_client: the new client
        :type: an object belonging to the Client class
        """
        self.read()
        for client in self.__repo:
            if client.get_client_id() == new_client.get_client_id():
                raise RepositoryException("This ID already exists")

        self.__repo.append(new_client)
        self.write()

    def remove(self, client_id):
        """
        Removes a client from the repository
        :param client_id: the ID of the client
        :type: integer, positive number
        """
        self.read()
        for client in self.__repo:
            if client.get_client_id() == client_id:
                self.__repo.remove(client)
                self.write()
                return None

        raise RepositoryException("There is no client with the given ID!")

    def update(self, client_id, new_name):
        """
        Modifies client name
        :param client_id: the ID of the client that should be updated
        :type: integer, positive number
        :param new_name: the new name of the client
        :type: string, text
        """
        self.read()
        for client in self.__repo:
            if client.get_client_id() == client_id:
                client.set_name(new_name)
                self.write()
                return None

        raise RepositoryException("There is no client with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.read()
        value = ""
        for client in self.__repo:
            value += (str(client) + "\n")

        return value.rstrip()

    def search(self, choice, data):
        """
        searches for the clients that match the criteria
        :param choice: the type of search
        :type: integer, positive, from 1 to 3
        :param data: the criteria
        :type: string, text, the name
        """
        self.read()
        clients_to_print = "" if len(self.__repo) > 0 else "The list of books is empty."
        if choice == 1:
            for client in self.__repo:
                if int(client.get_client_id()) == int(data):
                    clients_to_print += (str(client) + "\n")
            if len(clients_to_print) == 0:
                return RepositoryException("There is no client with the given ID!")
            else:
                return clients_to_print.rstrip()
        elif choice == 2:
            for client in self.__repo:
                if client.get_name().find(data) != -1:
                    clients_to_print += (str(client) + "\n")
            if len(clients_to_print) == 0:
                return RepositoryException("There is no client with the given name!")
            else:
                return clients_to_print.rstrip()

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        return list(self.__repo)
