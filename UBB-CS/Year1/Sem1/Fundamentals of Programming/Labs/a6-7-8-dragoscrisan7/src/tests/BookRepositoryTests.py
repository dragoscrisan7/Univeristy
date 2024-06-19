from src.repository.BookRepository import BookRepository
from src.domain.Book import Book


class BookRepositoryTest:
    """
    A class that tests the BookRepository class
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
        book_repository = BookRepository()

        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book_repository.add(book1)

        book_repo = book_repository.get_repo()

        assert book_repo.get_list() == [book1]

        book_repository.add(book2)
        assert book_repo.get_list() == [book1, book2]

        book_repository.add(book3)
        assert book_repo.get_list() == [book1, book2, book3]

    @staticmethod
    def test_remove():
        """
        Tests the remove() function
        """
        book_repository = BookRepository()
        book_repo = book_repository.get_repo()

        book1 = Book(0, "test", "test")
        book2 = Book(1, "test", "test")
        book3 = Book(2, "test", "test")

        book_repository.add(book1)
        book_repository.add(book2)
        book_repository.add(book3)

        assert book_repo.get_list() == [book1, book2, book3]

        book_repository.remove(1)
        assert book_repo.get_list() == [book1, book3]

        book_repository.remove(0)
        assert book_repo.get_list() == [book3]

        book_repository.remove(2)
        assert book_repo.get_list() == []

    @staticmethod
    def test_update():
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
        assert book_repository.get_repo()[1].get_title() == "test2"
        assert book_repository.get_repo()[1].get_author() == "test3"

        book_repository.update(0, "test4", "test5")
        assert book_repository.get_repo()[0].get_title() == "test4"
        assert book_repository.get_repo()[0].get_author() == "test5"

        book_repository.update(2, "test6", "test7")
        assert book_repository.get_repo()[2].get_title() == "test6"
        assert book_repository.get_repo()[2].get_author() == "test7"
