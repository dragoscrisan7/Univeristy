from repository.Repository import repository
from services.Service import service
from validators.Validators import validators
from ui.UI import ui
from repository.test_Repository import Testrepository

testing = Testrepository()
repo = repository()
vali = validators()
srv = service(repo, vali)
ui = ui(srv)


def main():
    testing.test_all()
    ui.run()


if __name__ == '__main__':
    main()
