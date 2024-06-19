from src.repository.RentalRepository import RentalRepository
from src.domain.Rental import Rental


class RentalRepositoryTest:
    """
    A class that tests the RentalRepository class
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
        self.test_rent()
        self.test_unrent()
        self.test_remove()

    @staticmethod
    def test_rent():
        """
        Tests the rent() function
        """
        rental_repository = RentalRepository()

        rental1 = Rental(0, 5, 10, "2021/11/14", "-1")
        rental2 = Rental(1, 10, 15, "2021/11/15", "-1")
        rental3 = Rental(2, 15, 20, "2021/11/16", "-1")

        rental_repository.rent(rental1)
        assert rental_repository.get_repo() == [rental1]

        rental_repository.rent(rental2)
        assert rental_repository.get_repo() == [rental1, rental2]

        rental_repository.rent(rental3)
        assert rental_repository.get_repo() == [rental1, rental2, rental3]

    @staticmethod
    def test_unrent():
        """
        Tests the unrent() function
        """
        rental_repository = RentalRepository()

        rental1 = Rental(0, 5, 10, "2021/11/11", "-1")
        rental2 = Rental(1, 10, 15, "2021/11/12", "-1")
        rental3 = Rental(2, 15, 20, "2021/11/13", "-1")

        rental_repository.rent(rental1)
        rental_repository.rent(rental2)
        rental_repository.rent(rental3)

        rental_repository.update(1, "2021/11/11", "2021/11/14")
        assert rental_repository.get_repo()[1].get_returned_date() == "2021/11/14"

        rental_repository.update(0, "2021/11/12", "2021/11/15")
        assert rental_repository.get_repo()[0].get_returned_date() == "2021/11/15"

        rental_repository.update(2, "2021/11/13", "2021/11/16")
        assert rental_repository.get_repo()[2].get_returned_date() == "2021/11/16"

    @staticmethod
    def test_remove():
        """
        Tests the remove() function
        """
        rental_repository = RentalRepository()

        rental1 = Rental(0, 5, 10, "2021/11/14", "-1")
        rental2 = Rental(1, 10, 15, "2021/11/15", "-1")
        rental3 = Rental(2, 15, 20, "2021/11/16", "-1")

        rental_repository.rent(rental1)
        rental_repository.rent(rental2)
        rental_repository.rent(rental3)

        assert rental_repository.get_repo() == [rental1, rental2, rental3]

        rental_repository.remove(1)
        assert rental_repository.get_repo() == [rental1, rental3]

        rental_repository.remove(0)
        assert rental_repository.get_repo() == [rental3]

        rental_repository.remove(2)
        assert rental_repository.get_repo() == []
