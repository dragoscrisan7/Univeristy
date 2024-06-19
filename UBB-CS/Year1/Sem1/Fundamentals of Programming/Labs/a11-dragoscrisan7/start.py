from Repository.Board_Repository import Board_Repo
from Services.Board_Services import Board_Services
from ui.Ui import UI


def main():
    board_repo = Board_Repo()
    board_serv = Board_Services(board_repo)
    player_ai = int(input("For player vs player press 1, for player vs ai press 2: "))
    menu = UI(board_serv)
    menu.display_game(player_ai)


if __name__ == "__main__":
    main()
