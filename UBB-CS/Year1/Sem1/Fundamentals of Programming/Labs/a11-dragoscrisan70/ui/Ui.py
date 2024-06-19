import pygame
import sys
import math


class UI:
    def __init__(self, board_serv):
        self.__board_serv = board_serv

    def display_game(self, player_ai):
        background = (255, 255, 255)
        turn = 0
        game_won = False
        self.__board_serv.print_board()

        pygame.init()

        square_size = 75
        width = 7 * square_size
        height = (6 + 1) * square_size
        size = (width, height)
        radius = int(square_size / 2 - 5)

        screen = pygame.display.set_mode(size)

        screen.fill(background)
        pygame.display.update()

        self.__board_serv.draw_board()

        pygame.display.update()

        myfont = pygame.font.SysFont("monospace", 75)
        if player_ai == 1:
            while not game_won:
                black = (0, 0, 0)
                red = (255, 0, 0)
                yellow = (255, 255, 0)
                gray = (127, 127, 127)
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        sys.exit()

                    if event.type == pygame.MOUSEMOTION:
                        pygame.draw.rect(screen, black, (0, 0, width, square_size))
                        posx = event.pos[0]
                        if turn == 0:
                            pygame.draw.circle(screen, red, (posx, int(square_size / 2)), radius)
                        else:
                            pygame.draw.circle(screen, yellow, (posx, int(square_size / 2)), radius)
                    pygame.display.update()

                    if event.type == pygame.MOUSEBUTTONDOWN:
                        pygame.draw.rect(screen, black, (0, 0, width, square_size))
                        # print(event.pos)
                        # Ask for Player 1 Input
                        if turn == 0:
                            posx = event.pos[0]
                            col = int(math.floor(posx / square_size))

                            if self.__board_serv.check_full_column(col):
                                turn -= 1
                            else:
                                self.__board_serv.set_on_valid_poz(0, col, 1)
                                if self.__board_serv.check_full():
                                    label = myfont.render("No one wins, you both suck!", True, gray)
                                    screen.blit(label, (40, 10))
                                    game_won = True
                                if self.__board_serv.check_winning_move(1):
                                    label = myfont.render("Player 1 wins!!", True, red)
                                    screen.blit(label, (40, 10))
                                    game_won = True
                        # # Ask for Player 2 Input
                        else:
                            posx = event.pos[0]
                            col = int(math.floor(posx / square_size))

                            if self.__board_serv.check_full_column(col):
                                turn -= 1
                            else:
                                self.__board_serv.set_on_valid_poz(0, col, 2)
                                if self.__board_serv.check_full():
                                    label = myfont.render("No one wins, you both suck!", True, gray)
                                    screen.blit(label, (40, 10))
                                    game_won = True
                                if self.__board_serv.check_winning_move(2):
                                    label = myfont.render("Player 2 wins!!", True, yellow)
                                    screen.blit(label, (40, 10))
                                    game_won = True

                        self.__board_serv.print_board()
                        self.__board_serv.draw_board()

                        turn += 1
                        turn = turn % 2

                        if game_won:
                            pygame.time.wait(3000)
        elif player_ai == 2:
            while not game_won:
                black = (0, 0, 0)
                red = (255, 0, 0)
                yellow = (255, 255, 0)
                gray = (127, 127, 127)
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        sys.exit()

                    if event.type == pygame.MOUSEMOTION:
                        pygame.draw.rect(screen, black, (0, 0, width, square_size))
                        posx = event.pos[0]
                        if turn == 0:
                            pygame.draw.circle(screen, red, (posx, int(square_size / 2)), radius)

                    pygame.display.update()

                    if event.type == pygame.MOUSEBUTTONDOWN:
                        pygame.draw.rect(screen, black, (0, 0, width, square_size))
                        # print(event.pos)
                        # Ask for Player 1 Input
                        if turn == 0:
                            posx = event.pos[0]
                            col = int(math.floor(posx / square_size))

                            if self.__board_serv.check_full_column(col):
                                turn -= 1
                            else:
                                self.__board_serv.set_on_valid_poz(0, col, 1)
                                if self.__board_serv.check_full():
                                    label = myfont.render("No one wins, you both suck!", True, gray)
                                    screen.blit(label, (40, 10))
                                    game_won = True
                                if self.__board_serv.check_winning_move(1):
                                    label = myfont.render("Player 1 wins!!", True, red)
                                    screen.blit(label, (40, 10))
                                    game_won = True

                            turn += 1
                            turn = turn % 2

                            self.__board_serv.print_board()
                            self.__board_serv.draw_board()
                        # # Ask for Player 2 Input

                if turn == 1:
                    col = self.__board_serv.ai()
                    if self.__board_serv.check_full_column(col):
                        turn -= 1
                    else:
                        self.__board_serv.set_on_valid_poz(0, col, 2)
                        if self.__board_serv.check_full():
                            label = myfont.render("No one wins, you both suck!", True, gray)
                            screen.blit(label, (40, 10))
                            game_won = True
                        if self.__board_serv.check_winning_move(2):
                            label = myfont.render("Player 2 wins!!", True, yellow)
                            screen.blit(label, (40, 10))
                            game_won = True

                    turn += 1
                    turn = turn % 2

                    self.__board_serv.print_board()
                    self.__board_serv.draw_board()

                if game_won:
                    pygame.time.wait(3000)
