from src.service.service import Service
from src.repository.repository import Repository
from src.ui.ui import Interface
from src.validators.validators import Validator

repo = Repository()
validator = Validator()
service = Service(repo, validator)
ui = Interface(service)

def main():
    ui.run()

if __name__ == '__main__':
    main()

