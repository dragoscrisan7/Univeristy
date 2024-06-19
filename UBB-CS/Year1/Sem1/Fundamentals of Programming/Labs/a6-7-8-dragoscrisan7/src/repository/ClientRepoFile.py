from src.domain.Client import Client
from src.repository.Exceptions import RepositoryException


class ClientRepositoryFile:
    """
    A class for the client repository
    """
    def __init__(self, filename):
        """
        Constructor for the ClientRepository class
        """
        self.__filename = filename
        self.__repo = []

    def update_file(self):
        self.__repo.clear()
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    client_id = int(parts[0])
                    name = parts[1]
                    client = Client(client_id, name)
                    self.__repo.append(client)

    def get_repo(self):
        """
        :return: the clients repository list
        """
        self.update_file()
        return self.__repo

    def add(self, new_client):
        """
        Adds a new client to the repository
        :param new_client: the new client
        :type: an object belonging to the Client class
        """
        self.update_file()
        for client in self.__repo:
            if client.get_client_id() == new_client.get_client_id():
                raise RepositoryException("This ID already exists")
        with open(self.__filename, 'a') as f:
            f.write(f"{new_client.get_client_id()},{new_client.get_name()}\n")

    def remove(self, client_id):
        """
        Removes a client from the repository
        :param client_id: the ID of the client
        :type: integer, positive number
        """
        ok = 0
        with open(self.__filename, 'r+') as f:
            lines = f.readlines()
            f.seek(0)
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(',')
                    if int(parts[0]) != client_id:
                        f.write(line+"\n")
                    else:
                        ok = 1
            f.truncate()
        if ok == 0:
            raise RepositoryException("There is no client with the given ID!")

    def update(self, client_id, new_name):
        """
        Modifies client name
        :param client_id: the ID of the client that should be updated
        :type: integer, positive number
        :param new_name: the new name of the client
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
                    if int(parts[0]) != client_id:
                        f.write(line+"\n")
                    else:
                        f.write(f"{parts[0]},{new_name}\n")
                        ok = 1

        if ok == 0:
            raise RepositoryException("There is no client with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        self.update_file()
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
        self.update_file()
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
        self.update_file()
        return list(self.__repo)
