class Rental:
    def __init__(self, rental_id, movie_id, client_id, rented_date, due_date, returned_date):
        self._rental_id = rental_id
        self._movie_id = movie_id
        self._client_id = client_id
        self._rented_date = rented_date
        self._due_date = due_date
        self._return_date = returned_date

    @property
    def rental_id(self):
        return self._rental_id

    @property
    def movie_id(self):
        return self._movie_id

    @property
    def client_id(self):
        return self._client_id

    @property
    def rented_date(self):
        return self._return_date

    @property
    def due_date(self):
        return self._due_date

    @property
    def returned_date(self):
        return self._return_date
