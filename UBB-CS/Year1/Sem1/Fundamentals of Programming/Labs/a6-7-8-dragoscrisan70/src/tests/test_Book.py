from unittest import TestCase
from src.domain.Book import Book

class TestBook(TestCase):
    def test_get_book_id(self):
        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        assert book1.get_book_id() == 0
        assert book2.get_book_id() == 1
        assert book3.get_book_id() == 2

    def test_set_book_id(self):
        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book1.set_book_id(3)
        book2.set_book_id(4)
        book3.set_book_id(5)

        assert book1.get_book_id() == 3
        assert book2.get_book_id() == 4
        assert book3.get_book_id() == 5

    def test_get_title(self):
        book1 = Book(0, "test1", "test")
        book2 = Book(1, "test2", "test")
        book3 = Book(2, "test3", "test")

        assert book1.get_title() == "test1"
        assert book2.get_title() == "test2"
        assert book3.get_title() == "test3"

    def test_set_title(self):
        book1 = Book(0, "test1", "test")
        book2 = Book(1, "test2", "test")
        book3 = Book(2, "test3", "test")

        book1.set_title("test4")
        book2.set_title("test5")
        book3.set_title("test6")

        assert book1.get_title() == "test4"
        assert book2.get_title() == "test5"
        assert book3.get_title() == "test6"

    def test_get_author(self):
        book1 = Book(0, "test", "test1")
        book2 = Book(1, "test", "test2")
        book3 = Book(2, "test", "test3")

        assert book1.get_author() == "test1"
        assert book2.get_author() == "test2"
        assert book3.get_author() == "test3"

    def test_set_author(self):
        book1 = Book(0, "test", "test1")
        book2 = Book(1, "test", "test2")
        book3 = Book(2, "test", "test3")

        book1.set_author("test4")
        book2.set_author("test5")
        book3.set_author("test6")

        assert book1.get_author() == "test4"
        assert book2.get_author() == "test5"
        assert book3.get_author() == "test6"
