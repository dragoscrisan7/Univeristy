from Music.MusicFestival import get_name, get_month, get_ticket_cost, get_artist_list

def show_list(list):
    for fest in list:
        print('Festival Name:',get_name(fest))
        print('Month:', get_month(fest))
        print('Ticket price:', get_ticket_cost(fest))
        for pula in get_artist_list(fest):
            print('Artist:', pula)
        print()

def verify_name(list, name):
    for fest in list:
        if get_name(fest) == name:
            raise ValueError('Name already exists')

def find_artist(dic, name):
    for art in get_artist_list(dic):
        if art == name:
            return True
    return False

def show_artist(list, name):
    for fest in list:
        if find_artist(fest, name):
            print('Festival Name:', get_name(fest))