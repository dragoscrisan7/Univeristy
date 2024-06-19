from unittest import TestCase
from src.repository.ClientRepository import ClientRepository
from src.domain.Client import Client


class TestClientRepository(TestCase):
    def test_add(self):
        """
                Tests the add() function
                """
        client_repository = ClientRepository()

        client1 = Client(0, "test")
        client2 = Client(1, "test")
        client3 = Client(2, "test")

        client_repository.add(client1)
        client_repository.add(client2)
        client_repository.add(client3)

        assert client_repository.get_repo() == [client1, client2, client3]

    def test_remove(self):
        """
        Tests the remove() function
        """
        client_repository = ClientRepository()

        client1 = Client(0, "test")
        client2 = Client(1, "test")
        client3 = Client(2, "test")

        client_repository.add(client1)
        client_repository.add(client2)
        client_repository.add(client3)

        client_repository.remove(1)
        client_repository.remove(0)

        assert client_repository.get_repo() == [client3]

    def test_update(self):
        """
                Tests the update() function
                """
        client_repository = ClientRepository()

        client1 = Client(0, "test")
        client2 = Client(1, "test")
        client3 = Client(2, "test")

        client_repository.add(client1)
        client_repository.add(client2)
        client_repository.add(client3)

        client_repository.update(1, "test2")
        client_repository.update(0, "test4")
        client_repository.update(2, "test6")

        assert client_repository.get_repo()[2].get_name() == "test6" and \
               client_repository.get_repo()[1].get_name() == "test2" and \
               client_repository.get_repo()[0].get_name() == "test4"
