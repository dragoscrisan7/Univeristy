from src.domain.Exceptions import *
from src.repository.Exceptions import *
from datetime import datetime


class UI:
    """
    A class that represents the console user interface that is displayed to the user
    """
    def __init__(self, book_service, client_service, rental_service, undo_service):
        """
        Initializes the UI class
        :param rental_service: the rental service
        :param book_service: the book service
        :param client_service: the client service
        """
        self.__book_service = book_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__undo_service = undo_service
        self.__menu_options = ["Exit", "Add book", "Remove book", "Update book", "List of books",
                               "Add client", "Remove client", "Update client", "List of clients",
                               "Rent book", "Return book", "List of rentals", "Search book", "Search client",
                               "Most rented Books", "Most active clients", "Most rented author", "Undo", "Redo", "Menu"]

    def display_menu(self):
        """
        displays the user interface,
        then asks for input and calls the handler function
        """
        for i in range(len(self.__menu_options)):
            print((" " if i < 10 else "") + str(i) + ". " + self.__menu_options[i])
        print()

        while True:
            option = UI.get_input("Option: ")

            if option == 19:
                for i in range(len(self.__menu_options)):
                    print((" " if i < 10 else "") + str(i) + ". " + self.__menu_options[i])
                print()

            if option == 0:
                print("INFO: Quitting.")
                input("Press <ENTER> to continue.")

                return None

            self.handle_menu_option(option)

    def handle_menu_option(self, option):
        """
        Handles the given menu option using the list of complex numbers
        :param option: The menu option that was selected by the user
        """
        try:
            if option == 1:
                book_id = UI.get_input("Book ID: ")
                book_title = input("Title: ")
                book_author = input("Author: ")

                self.__book_service.create(book_id, book_title, book_author)
                print("INFO: You have added a new book to the repository.")
            elif option == 2:
                book_id = UI.get_input("Book ID: ")

                self.__book_service.delete(book_id)
                print("INFO: You have deleted a book from the repository.")
            elif option == 3:
                book_id = UI.get_input("Book ID: ")
                title = input("New Title: ")
                author = input("New Author: ")

                self.__book_service.update(book_id, title, author)
                print("INFO: You have updated the book with new information.")
            elif option == 4:
                print(self.__book_service.list())
            elif option == 5:
                client_id = UI.get_input("Client ID: ")
                name = input("Name: ")

                self.__client_service.create(client_id, name)
                print("INFO: You have added a new client to the repository.")
            elif option == 6:
                client_id = UI.get_input("Client ID: ")

                self.__client_service.delete(client_id)
                print("INFO: You have deleted a client from the repository.")
            elif option == 7:
                client_id = UI.get_input("Client ID: ")
                name = input("New Name: ")

                self.__client_service.update(client_id, name)
                print("INFO: You have updated the client with new information.")
            elif option == 8:
                print(self.__client_service.list())
            elif option == 9:
                rental_id = UI.get_input("Rental ID: ")
                book_id = UI.get_input("Book ID: ")
                client_id = UI.get_input("Client ID: ")
                start = datetime.today().strftime('%Y/%m/%d')

                self.__rental_service.create_rental(rental_id, book_id, client_id, start, "-1")
                print("INFO: You have added a rental to the repository.")
            elif option == 10:
                rental_id = UI.get_input("Rental ID: ")
                rental = self.__rental_service.get_with_rental_id(rental_id)
                start = rental[3]
                end = datetime.today().strftime('%Y/%m/%d')

                self.__rental_service.update_rental(rental_id, start, end)
                print("INFO: You have ended a book rental.")
            elif option == 11:
                print(self.__rental_service.list())
            elif option == 12:
                UI.display_book_menu()
                choice = UI.get_input("Option: ")
                try:
                    if choice == 1:
                        text = int(input("ID: "))
                    elif choice == 2:
                        text = input("Name: ")
                    elif choice == 3:
                        text = input("Author: ")
                    else:
                        raise ValueError
                    print(self.__book_service.search(choice, text))
                except ValueError:
                    print("ERROR: Invalid parameter type!")
            elif option == 13:
                UI.display_client_menu()
                choice = UI.get_input("Option: ")
                if choice == 1:
                    text = int(input("ID: "))
                elif choice == 2:
                    text = input("Name: ")
                else:
                    raise ValueError
                print(self.__client_service.search(choice, text))
            elif option == 14:
                for book in self.__rental_service.most_rented_books():
                    print(str(book))
            elif option == 15:
                for client in self.__rental_service.most_active_clients():
                    print(str(client))
            elif option == 16:
                for author in self.__rental_service.most_read_authors():
                    print(author)
            elif option == 17:
                self.__undo_service.undo()
            elif option == 18:
                self.__undo_service.redo()
        except (BookException, ClientException, RentalException, RepositoryException) as error:
            print("ERROR: " + str(error))
        except ValueError:
            print("ERROR: Invalid parameter type!")
        except IndexError:
            print("ERROR: Invalid index reached!")

        print()
        input("Press <ENTER> to continue.")

    @staticmethod
    def get_input(prompt):
        """
        :param prompt: the prompt that is shown to the user for input
        :return: a valid integer
        """
        while True:
            try:
                value = int(input(prompt))
                return value
            except ValueError:
                print()
                print("ERROR: Invalid input provided!")

    @staticmethod
    def display_book_menu():
        """
        displays the menu for the book search option
        """
        print("1.Search by id")
        print("2.Search by name")
        print("3.search by author")

    @staticmethod
    def display_client_menu():
        """
        displays the menu for the client search option
        """
        print("1.Search by id")
        print("2.Search by name")
