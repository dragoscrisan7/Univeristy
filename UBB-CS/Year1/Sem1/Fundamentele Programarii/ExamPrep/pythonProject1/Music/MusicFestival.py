def add_music_festival():
    name = input('Festival name:')
    if not name.isalnum():
        raise ValueError('Name must be a word')
    month = input('Month:')
    if not month.isnumeric():
        raise ValueError('Month must be a number')
    month = int(month)
    if month<1 or month>12:
        raise ValueError('Incorrect Month')
    ticket_cost = input('Ticket Cost:')
    if not ticket_cost.isnumeric():
        raise ValueError('Ticket Cost must be a number')
    if month<0:
        raise ValueError('Ticket Cost must be a positive number')
    number = input('Number of artists that perform:')
    if not number.isnumeric():
        raise ValueError('Number must be a number')
    number = int(number)
    if number<0:
        raise ValueError('Number must be a positive number')
    artist_list = []
    for a in range(0,number):
        artist = input('Write artist:')
        artist_list.append(artist)
    return {'Name': name, 'Month': month, 'Ticket_cost':ticket_cost, 'Artist_list': artist_list}

def get_name(Dic):
    return Dic['Name']

def get_month(Dic):
    return Dic['Month']

def get_ticket_cost(Dic):
    return Dic['Ticket_cost']

def get_artist_list(Dic):
    return Dic['Artist_list']
