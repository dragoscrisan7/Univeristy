from Controller.Hangman_controller import controller
from Repository.Hangman_repository import repository
from Validator.Hangman_validator import validator
from UI.Hangman_ui import ui

filename = "readme.txt"
repo = repository(filename)
vali = validator()
ctrl = controller(repo, vali)
uI = ui(ctrl)


def main():
    uI.run()


if __name__ == "__main__":
    main()
