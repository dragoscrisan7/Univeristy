from src.domain.Client import Client


class ClientTest:
    """
    A class that handles the testing of the Client class
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
        self.test_get_client_id()
        self.test_set_client_id()
        self.test_get_name()
        self.test_set_name()

    @staticmethod
    def test_get_client_id():
        """
        Tests the get_client_id() function
        """
        client1 = Client(0, "test1")
        client2 = Client(1, "test2")
        client3 = Client(2, "test3")

        assert client1.get_client_id() == 0
        assert client2.get_client_id() == 1
        assert client3.get_client_id() == 2

    @staticmethod
    def test_set_client_id():
        """
        Tests the set_client_id() function
        """
        client1 = Client(0, "test1")
        client2 = Client(1, "test2")
        client3 = Client(2, "test3")

        client1.set_client_id(3)
        client2.set_client_id(4)
        client3.set_client_id(5)

        assert client1.get_client_id() == 3
        assert client2.get_client_id() == 4
        assert client3.get_client_id() == 5

    @staticmethod
    def test_get_name():
        """
        Tests the get_name() function
        """
        client1 = Client(0, "test1")
        client2 = Client(1, "test2")
        client3 = Client(2, "test3")

        assert client1.get_name() == "test1"
        assert client2.get_name() == "test2"
        assert client3.get_name() == "test3"

    @staticmethod
    def test_set_name():
        """
        Tests the set_name() function
        """
        client1 = Client(0, "test1")
        client2 = Client(1, "test2")
        client3 = Client(2, "test3")

        client1.set_name("test4")
        client2.set_name("test5")
        client3.set_name("test6")

        assert client1.get_name() == "test4"
        assert client2.get_name() == "test5"
        assert client3.get_name() == "test6"
