from service.service import Service
from repository.repository import Repository
from ui.ui import Interface
from validators.validators import Validator

repo = Repository()
validator = Validator()
service = Service(repo, validator)
ui = Interface(service)

def main():
    ui.run()

if __name__ == '__main__':
    main()

