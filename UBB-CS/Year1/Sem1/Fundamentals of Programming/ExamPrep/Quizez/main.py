from Repository.Quiz_repository import quiz_repository
from Services.Quiz_services import quiz_services
from Validators.Validator import validator
from Interface.UI import ui
from random import randint

repo = quiz_repository("Master_Questions.txt")
vali = validator()
srv = quiz_services(repo, vali)
uI = ui(srv)


def main():
    uI.run()


if __name__ == "__main__":
    main()
