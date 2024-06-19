from unittest import TestCase
from src.repository.ClientRepository import ClientRepository
from src.services.RentalServices import RentalService
from src.repository.RentalRepository import RentalRepository
from src.repository.BookRepository import BookRepository
from src.services.ClientServices import ClientService


class TestClientService(TestCase):
    client_repo = ClientRepository()
    rental_repo = RentalRepository()
    book_repo = BookRepository()
    rental_serv = RentalService(rental_repo, book_repo, client_repo)
    client_service_test = ClientService(client_repo)

    def test_create(self):
        self.client_service_test.create(1, "Darius")
        client = self.client_service_test.get_all()
        assert client[0].get_client_id() == 1 and client[0].get_name() == "Darius"

    def test_delete(self):
        self.client_service_test.create(2, "Damascus")
        self.client_service_test.delete(2)
        client = self.client_service_test.get_all()
        assert len(client) == 1

    def test_update(self):
        self.client_service_test.create(2, "Damascus")
        self.client_service_test.update(2, "Dragos")
        client = self.client_service_test.get_all()
        assert client[1].get_client_id() == 2 and client[1].get_name() == "Dragos"
