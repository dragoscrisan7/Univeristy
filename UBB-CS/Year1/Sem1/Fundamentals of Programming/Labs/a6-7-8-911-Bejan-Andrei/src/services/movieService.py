class MovieService:

    def __init__(self, movie_repo):
        self.__repo = movie_repo

    def initiate_movies(self):
        self.__repo.initiate_movies()

    def add_movie(self, movie):
        self.__repo.add_entity(movie)

    def remove_movie(self, _id):
        self.__repo.remove_entity(_id)

    def update_movie(self, _id, title, genre, description):
        self.__repo.update_entity(_id, title, genre, description)

    def display_movies(self):
        movies = self.__repo.display_movies()
        return movies

    def get_movies(self):
        movies = self.__repo.get_movies()
        return movies
