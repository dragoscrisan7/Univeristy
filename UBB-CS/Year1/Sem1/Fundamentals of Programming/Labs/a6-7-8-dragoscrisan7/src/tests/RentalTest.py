from src.domain.Rental import Rental


class RentalTest:
    """
    A class that handles the testing of the Rental class
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
        self.test_get_rental_id()
        self.test_set_rental_id()
        self.test_get_book_id()
        self.test_set_book_id()
        self.test_get_client_id()
        self.test_set_client_id()
        self.test_get_rented_date()
        self.test_set_rented_date()
        self.test_get_returned_date()
        self.test_set_returned_date()

    @staticmethod
    def test_get_rental_id():
        """
        Tests the get_rental_id() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        assert rental1.get_rental_id() == 0
        assert rental2.get_rental_id() == 1
        assert rental3.get_rental_id() == 2

    @staticmethod
    def test_set_rental_id():
        """
        Tests the set_rental_id() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        rental1.set_rental_id(3)
        rental2.set_rental_id(4)
        rental3.set_rental_id(5)

        assert rental1.get_rental_id() == 3
        assert rental2.get_rental_id() == 4
        assert rental3.get_rental_id() == 5

    @staticmethod
    def test_get_book_id():
        """
        Tests the get_book_id function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        assert rental1.get_book_id() == 1
        assert rental2.get_book_id() == 3
        assert rental3.get_book_id() == 5

    @staticmethod
    def test_set_book_id():
        """
        Tests the set_book_id() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        rental1.set_book_id(7)
        rental2.set_book_id(9)
        rental3.set_book_id(11)

        assert rental1.get_book_id() == 7
        assert rental2.get_book_id() == 9
        assert rental3.get_book_id() == 11

    @staticmethod
    def test_get_client_id():
        """
        Tests the get_client_id() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        assert rental1.get_client_id() == 2
        assert rental2.get_client_id() == 4
        assert rental3.get_client_id() == 6

    @staticmethod
    def test_set_client_id():
        """
        Tests the set_client_id() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        rental1.set_client_id(8)
        rental2.set_client_id(10)
        rental3.set_client_id(12)

        assert rental1.get_client_id() == 8
        assert rental2.get_client_id() == 10
        assert rental3.get_client_id() == 12

    @staticmethod
    def test_get_rented_date():
        """
        Tests the get_rented_date() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")
        assert rental1.get_rented_date() == "2021/11/14"
        assert rental2.get_rented_date() == "2021/11/15"
        assert rental3.get_rented_date() == "2021/11/16"

    @staticmethod
    def test_set_rented_date():
        """
        Tests the set_rented_date() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/14", "-1")
        rental2 = Rental(1, 3, 4, "2021/11/15", "-1")
        rental3 = Rental(2, 5, 6, "2021/11/16", "-1")

        rental1.set_rented_date("2021/11/11")
        rental2.set_rented_date("2021/11/12")
        rental3.set_rented_date("2021/11/13")

        assert rental1.get_rented_date() == "2021/11/11"
        assert rental2.get_rented_date() == "2021/11/12"
        assert rental3.get_rented_date() == "2021/11/13"

    @staticmethod
    def test_get_returned_date():
        """
        Tests the get_returned_date() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/01", "2021/11/02")
        rental2 = Rental(1, 3, 4, "2021/11/01", "2021/11/03")
        rental3 = Rental(2, 5, 6, "2021/11/01", "2021/11/04")

        assert rental1.get_returned_date() == "2021/11/02"
        assert rental2.get_returned_date() == "2021/11/03"
        assert rental3.get_returned_date() == "2021/11/04"

    @staticmethod
    def test_set_returned_date():
        """
        Tests the set_returned_date() function
        """
        rental1 = Rental(0, 1, 2, "2021/11/01", "2021/11/02")
        rental2 = Rental(1, 3, 4, "2021/11/01", "2021/11/03")
        rental3 = Rental(2, 5, 6, "2021/11/01", "2021/11/04")

        rental1.set_returned_date("2021/11/05")
        rental2.set_returned_date("2021/11/06")
        rental3.set_returned_date("2021/11/07")

        assert rental1.get_returned_date() == "2021/11/05"
        assert rental2.get_returned_date() == "2021/11/06"
        assert rental3.get_returned_date() == "2021/11/07"
