class ClientService:

    def __init__(self, client_repo):
        self.__repo = client_repo

    def add_client(self, client):
        self.__repo.add_entity(client)

    def initiate_clients(self):
        self.__repo.initiate_clients()

    def remove_client(self, _id):
        self.__repo.remove_entity(_id)

    def update_client(self, _id):
        self.__repo.update_entity(_id)

    def display_clients(self):
        clients = self.__repo.display_clients()
        return clients

    def get_clients(self):
        clients = self.__repo.get_clients()
        return clients
