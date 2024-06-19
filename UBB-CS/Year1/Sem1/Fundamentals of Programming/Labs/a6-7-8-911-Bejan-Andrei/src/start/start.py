from src.ui.ui import Ui
from src.repository.repository import MovieRepository
from src.repository.repository import ClientRepository
from src.repository.repository import RentalRepository
from src.services.movieService import MovieService
from src.services.clientService import ClientService
from src.services.rentalService import RentalService


movie_repo = MovieRepository()
client_repo = ClientRepository()
rental_repo = RentalRepository()

movie_service = MovieService(movie_repo)
client_service = ClientService(client_repo)
rental_service = RentalService(rental_repo)

ui = Ui(movie_service, client_service, rental_service)

ui.start()
