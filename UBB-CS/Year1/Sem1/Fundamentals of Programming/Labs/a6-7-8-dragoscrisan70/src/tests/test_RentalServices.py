from unittest import TestCase
from src.repository.BookRepository import BookRepository
from src.repository.RentalRepository import RentalRepository
from src.repository.ClientRepository import ClientRepository
from src.services.RentalServices import RentalService
from datetime import datetime
from src.domain.Book import Book
from src.domain.Client import Client
from src.services.UndoService import UndoService


class TestRentalService(TestCase):
    book_repo = BookRepository()
    client_repo = ClientRepository()
    rental_repo = RentalRepository()
    undo_service = UndoService()
    rental_services_test = RentalService(rental_repo, book_repo, client_repo, undo_service)

    def test_create_rental(self):
        self.rental_services_test.create_rental(0, 5, 10, "2021/11/14", "-1")
        rentals = self.rental_services_test.get_all()
        assert rentals[0].get_rental_id() == 0 and rentals[0].get_book_id() == 5 and \
               rentals[0].get_client_id() == 10 and rentals[0].get_rented_date() == "2021/11/14" and \
               rentals[0].get_returned_date() == "-1"
        self.rental_services_test.remove_rental(0)

    def test_filter_rentals(self):
        self.rental_services_test.create_rental(0, 5, 10, "2021/11/14", "-1")
        self.rental_services_test.create_rental(1, 7, 11, "2021/10/15", "-1")
        end = datetime.today().strftime('%Y/%m/%d')
        self.rental_services_test.update_rental(0, "2021/11/14", end)
        self.rental_services_test.create_rental(2, 5, 10, "2021/10/15", "-1")
        rentals = self.rental_services_test.filter_rentals(None, 5)
        assert len(rentals) == 2
        assert rentals[0].get_rental_id() == 0 and rentals[0].get_book_id() == 5 and \
               rentals[0].get_client_id() == 10 and rentals[0].get_rented_date() == "2021/11/14" and \
               rentals[0].get_returned_date() == end and rentals[1].get_rental_id() == 2 and \
               rentals[1].get_book_id() == 5 and rentals[1].get_client_id() == 10 and \
               rentals[1].get_rented_date() == "2021/10/15" and rentals[1].get_returned_date() == "-1"
        self.rental_services_test.remove_rental(1)
        self.rental_services_test.remove_rental(2)
        self.rental_services_test.remove_rental(0)

    def test_remove_rental(self):
        self.rental_services_test.create_rental(0, 5, 10, "2021/11/14", "-1")
        self.rental_services_test.create_rental(1, 7, 11, "2021/10/15", "-1")
        self.rental_services_test.create_rental(2, 5, 10, "2021/10/15", "-1")
        self.rental_services_test.remove_rental(1)
        self.rental_services_test.remove_rental(2)
        rentals = self.rental_services_test.get_all()
        assert len(rentals) == 1
        assert rentals[0].get_rental_id() == 0 and rentals[0].get_book_id() == 5 and \
               rentals[0].get_client_id() == 10 and rentals[0].get_rented_date() == "2021/11/14" and \
               rentals[0].get_returned_date() == "-1"
        self.rental_services_test.remove_rental(0)

    def test_return_rental(self):
        self.rental_services_test.create_rental(0, 5, 10, "2021/11/14", "-1")
        self.rental_services_test.create_rental(1, 7, 11, "2021/10/15", "-1")
        end = datetime.today().strftime('%Y/%m/%d')
        self.rental_services_test.update_rental(1, "2021/10/15", end)
        rentals = self.rental_services_test.get_all()
        end = datetime.today().strftime('%Y/%m/%d')
        assert rentals[1].get_returned_date() == end
        self.rental_services_test.remove_rental(0)
        self.rental_services_test.remove_rental(1)

    def test_most_rented_books(self):
        self.rental_services_test.create_rental(0, 1, 10, "2021/11/14", "-1")
        self.rental_services_test.create_rental(1, 0, 11, "2021/10/15", "-1")
        end = datetime.today().strftime('%Y/%m/%d')
        self.rental_services_test.update_rental(0, "2021/11/14", end)
        self.rental_services_test.create_rental(2, 1, 12, "2021/10/15", "-1")
        book1 = Book(0, "Test1", "test1")
        book2 = Book(1, "Test2", "test2")
        self.book_repo.add(book1)
        self.book_repo.add(book2)
        books_sorted = list(self.rental_services_test.most_rented_books())
        assert books_sorted[0].get_book_id() == 1 and books_sorted[0].get_title() == "Test2" \
               and books_sorted[0].get_author() == "test2" and books_sorted[1].get_book_id() == 0 \
               and books_sorted[1].get_title() == "Test1" and books_sorted[1].get_author() == "test1"
        self.rental_services_test.remove_rental(0)
        self.rental_services_test.remove_rental(1)
        self.rental_services_test.remove_rental(2)

    def test_most_active_clients(self):
        self.rental_services_test.create_rental(0, 1, 1, "2021/11/14", "-1")
        self.rental_services_test.create_rental(1, 0, 1, "2021/10/16", "-1")
        end = datetime.today().strftime('%Y/%m/%d')
        self.rental_services_test.update_rental(0, "2021/11/14", end)
        self.rental_services_test.create_rental(2, 1, 0, "2021/10/16", "-1")
        client1 = Client(0, "Andrei")
        client2 = Client(1, "Marcus")
        self.client_repo.add(client1)
        self.client_repo.add(client2)
        clients_sorted = list(self.rental_services_test.most_active_clients())
        assert clients_sorted[0].get_client_id() == 1 and clients_sorted[0].get_name() == "Marcus" \
               and clients_sorted[1].get_client_id() == 0 and clients_sorted[1].get_name() == "Andrei"
        self.rental_services_test.remove_rental(0)
        self.rental_services_test.remove_rental(1)
        self.rental_services_test.remove_rental(2)
