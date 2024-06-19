from ui.UI import UI
"""
from repository.BookRepository import BookRepository
from repository.ClientRepository import ClientRepository
from repository.RentalRepository import RentalRepository
from repository.BookRepoFile import BookRepositoryFile
from repository.ClientRepoFile import ClientRepositoryFile
"""
from repository.RentalRepoPickle import RentalRepositoryPickle
from repository.BookRepositoryPickle import BookRepositoryPickle
from repository.ClientRepoPickle import ClientRepositoryPickle

from services.BooksServices import BookService
from services.ClientServices import ClientService
from services.RentalServices import RentalService
from services.UndoService import UndoService

from tests.BookTest import BookTest
from tests.ClientTest import ClientTest
from tests.RentalTest import RentalTest
from tests.BookRepositoryTests import BookRepositoryTest
from tests.ClientRepositoryTest import ClientRepositoryTest
from tests.RentalRepositoryTest import RentalRepositoryTest


# Program entry point
def main():
    book_test = BookTest()
    client_test = ClientTest()
    rental_test = RentalTest()
    book_repo_test = BookRepositoryTest()
    client_repo_test = ClientRepositoryTest()
    rental_repo_test = RentalRepositoryTest()

    book_test.run_all_tests()
    client_test.run_all_tests()
    rental_test.run_all_tests()
    book_repo_test.run_all_tests()
    client_repo_test.run_all_tests()
    rental_repo_test.run_all_tests()

    """
    rental_repo = RentalRepository()
    book_repo = BookRepository()
    client_repo = ClientRepository()
    rental_repo.initial_load()
    book_repo.initial_load()
    client_repo.initial_load()
    """

    rental_repo = RentalRepositoryPickle("repository/Rental_file")
    book_repo = BookRepositoryPickle("repository/Book_file")
    client_repo = ClientRepositoryPickle("repository/Client_file")

    undo_service = UndoService()
    rental_service = RentalService(rental_repo, book_repo, client_repo, undo_service)
    book_service = BookService(book_repo, rental_repo, undo_service, rental_service)
    client_service = ClientService(client_repo, rental_repo, undo_service, rental_service)

    menu = UI(book_service, client_service, rental_service, undo_service)
    menu.display_menu()


# Execute the main function
# if this file is ran directly
if __name__ == "__main__":
    main()

"""
La modificarea din pickle in fisiere .txt trebuie moddificate importurile la repo din pickle in file si
la linia 51 din pickle in file si adaugat .txt
"""