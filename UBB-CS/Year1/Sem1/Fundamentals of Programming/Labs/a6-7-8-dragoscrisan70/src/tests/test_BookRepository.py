from unittest import TestCase
from src.domain.Book import Book
from src.repository.BookRepository import BookRepository


class TestBookRepository(TestCase):
    def test_add(self):
        book_repository = BookRepository()

        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book_repository.add(book1)
        book_repository.add(book2)
        book_repository.add(book3)

        assert book_repository.get_repo() == [book1, book2, book3]

    def test_remove(self):
        book_repository = BookRepository()

        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book_repository.add(book1)
        book_repository.add(book2)
        book_repository.add(book3)

        book_repository.remove(1)
        book_repository.remove(0)

        assert book_repository.get_repo() == [book3]

    def test_update(self):
        """
        Tests the update() function
        """
        book_repository = BookRepository()

        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book_repository.add(book1)
        book_repository.add(book2)
        book_repository.add(book3)

        book_repository.update(1, "test2", "test3")
        book_repository.update(0, "test4", "test5")
        book_repository.update(2, "test6", "test7")
        assert book_repository.get_repo()[1].get_title() == "test2" and \
               book_repository.get_repo()[1].get_author() == "test3" and \
               book_repository.get_repo()[0].get_title() == "test4" and \
               book_repository.get_repo()[0].get_author() == "test5" and \
               book_repository.get_repo()[2].get_title() == "test6" and \
               book_repository.get_repo()[2].get_author() == "test7"
