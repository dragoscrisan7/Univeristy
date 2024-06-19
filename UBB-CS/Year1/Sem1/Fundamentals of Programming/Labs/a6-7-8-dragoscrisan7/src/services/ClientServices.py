from src.domain.Client import Client
from src.services.UndoService import Call, CascadedOperation, Operation


class ClientService:
    def __init__(self, repository, rental_repo, undo_service, rental_service):
        """
        :param repository: client repository
        """
        self.__repository = repository
        self.__rental_repo = rental_repo
        self.__undo_service = undo_service
        self.__rental_service = rental_service

    def create(self, client_id, name):
        """
        Adds a new client to the repository
        :param client_id: ID of the client
        :type: integer, positive number
        :param name: name of the client
        :type: string, text
        """
        client = Client(client_id, name)
        self.__repository.add(client)

        undo_call = Call(self.delete_without_undo, client_id)
        redo_call = Call(self.create_without_undo, client_id, name)
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

    def create_without_undo(self, client_id, name):
        """
        Adds a new client to the repository
        :param client_id: ID of the client
        :type: integer, positive number
        :param name: name of the client
        :type: string, text
        """
        client = Client(client_id, name)
        self.__repository.add(client)

    def delete(self, client_id):
        """
        Removes a client from the repository
        :param client_id: client ID
        :type: integer, positive number
        """
        client = self.get_with_client_id(client_id)
        self.__repository.remove(client_id)

        undo_call = Call(self.create_without_undo, client[0], client[1])
        redo_call = Call(self.delete_without_undo, client[0])
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        rentals = self.__rental_service.filter_rentals(client_id, None)
        for rent in rentals:
            undo_call = Call(self.__rental_service.create_rental_without_undo, rent.get_rental_id(), rent.get_book_id(),
                             rent.get_client_id(), rent.get_rented_date(), rent.get_returned_date())
            redo_call = Call(self.__rental_service.remove_rental, rent.get_rental_id())
            cope.add(Operation(undo_call, redo_call))
            self.__rental_repo.remove(rent.get_rental_id())

        self.__undo_service.record(cope)

    def delete_without_undo(self, client_id):
        """
        Removes a client from the repository
        :param client_id: client ID
        :type: integer, positive number
        """
        self.__repository.remove(client_id)

    def update(self, client_id, name):
        """
        Modifies a clients name
        :param client_id: ID of the client
        :type: integer, positive number
        :param name: new name
        :type: string, text
        """
        client = self.get_with_client_id(client_id)
        self.__repository.update(client_id, name)
        undo_call = Call(self.update, client[0], client[1])
        redo_call = Call(self.update, client_id, name)
        cope = CascadedOperation()
        cope.add(Operation(undo_call, redo_call))

        self.__undo_service.record(cope)

    def list(self):
        """
        :return: a string containing the list of clients
        """
        return self.__repository.list()

    def search(self, choice, data):
        """
        :param choice: the type of search
        :type: integer, positive, from 1 to 3
        :param data: the criteria for searching
        :type: string, text, the name
        :return: the clients that match the search
        """
        return self.__repository.search(choice, data)

    def get_all(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        return self.__repository.get_all_entities()

    def get_with_client_id(self, client_id):
        """
        searches for the client with the given id and returns the data about it in a list, necessary for undo
        :param client_id:
        :type: integer, positive number
        :return:
        """
        updated_client = None
        for client in self.__repository.get_repo():
            if client.get_client_id() == client_id:
                updated_client = (client.get_client_id(), client.get_name())

        return updated_client
