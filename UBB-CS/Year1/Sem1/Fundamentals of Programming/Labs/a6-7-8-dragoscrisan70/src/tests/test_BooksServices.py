from unittest import TestCase
from src.repository.BookRepository import BookRepository
from src.services.BooksServices import BookService
from src.services.RentalServices import RentalService
from src.repository.ClientRepository import ClientRepository
from src.repository.RentalRepository import RentalRepository
from src.services.UndoService import UndoService


class TestBookService(TestCase):
    book_repository_test = BookRepository()
    client_repo = ClientRepository()
    rental_repo = RentalRepository()
    undo_service = UndoService()
    rental_services = RentalService(rental_repo, book_repository_test, client_repo, undo_service)
    book_services_test = BookService(book_repository_test, rental_repo, undo_service, rental_services)

    def test_create(self):
        self.book_services_test.create(1, "asa", "bine")
        books = self.book_services_test.get_all()
        assert books[0].get_book_id() == 1 and books[0].get_title() == "asa" and books[0].get_author() == "bine"

    def test_delete(self):
        self.book_services_test.create(2, "a", "b")
        self.book_services_test.delete(2)
        books = self.book_services_test.get_all()
        assert len(books) == 1

    def test_update(self):
        self.book_services_test.update(1, "sss", "bn")
        books = self.book_services_test.get_all()
        assert books[0].get_book_id() == 1 and books[0].get_title() == "sss" and books[0].get_author() == "bn"
