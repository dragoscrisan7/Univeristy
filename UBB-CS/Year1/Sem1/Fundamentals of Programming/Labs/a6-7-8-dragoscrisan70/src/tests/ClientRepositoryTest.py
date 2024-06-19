from src.repository.ClientRepository import ClientRepository
from src.domain.Client import Client


class ClientRepositoryTest:
    """
    A class that tests the ClientRepository class
    """
    def __init__(self):
        """
        Initialize the class
        """
        pass

    def run_all_tests(self):
        """
        Run all the tests
        """
        self.test_add()
        self.test_remove()
        self.test_update()

    @staticmethod
    def test_add():
        """
        Tests the add() function
        """
        client_repository = ClientRepository()

        client1 = Client(0, "test")
        client2 = Client(1, "test")
        client3 = Client(2, "test")

        client_repository.add(client1)
        assert client_repository.get_repo() == [client1]

        client_repository.add(client2)
        assert client_repository.get_repo() == [client1, client2]

        client_repository.add(client3)
        assert client_repository.get_repo() == [client1, client2, client3]

    @staticmethod
    def test_remove():
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

        assert client_repository.get_repo() == [client1, client2, client3]

        client_repository.remove(1)
        assert client_repository.get_repo() == [client1, client3]

        client_repository.remove(0)
        assert client_repository.get_repo() == [client3]

        client_repository.remove(2)
        assert client_repository.get_repo() == []

    @staticmethod
    def test_update():
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
        assert client_repository.get_repo()[1].get_name() == "test2"

        client_repository.update(0, "test4")
        assert client_repository.get_repo()[0].get_name() == "test4"

        client_repository.update(2, "test6")
        assert client_repository.get_repo()[2].get_name() == "test6"
