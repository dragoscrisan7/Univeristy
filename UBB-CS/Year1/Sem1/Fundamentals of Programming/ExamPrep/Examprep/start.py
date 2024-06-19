from Repository.City_repository import city_repository
from Services.City_services import city_services
from UI.ui import Ui


def main():
    city_repo = city_repository()
    city_serv = city_services(city_repo)

    menu = Ui(city_serv)


if __name__ == "__main__":
    main()
