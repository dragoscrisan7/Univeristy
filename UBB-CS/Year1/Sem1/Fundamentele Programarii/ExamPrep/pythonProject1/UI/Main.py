from Music.MusicFestival import add_music_festival,get_name
from Services.Functions import show_list,verify_name,show_artist

def Main():
    print('1.Add a festival')
    print('2.Show list of festivals')
    print('3.Show list of festivals based on one artist')
    print('4.Close')

def Start():
    Music_festivals = []
    fest = {}
    while True:
        Main()
        a = input('Your opotion:')
        if a == '1':
            fest = add_music_festival()
            verify_name(Music_festivals, get_name(fest))
            Music_festivals.append(fest)
        elif a == '2':
            show_list(Music_festivals)
        elif a == '3':
            artist = input('Artist Name:')
            show_artist(Music_festivals,artist)
        elif a == '4':
            return
        else:
            raise ValueError('Incorrect opotion')




Start()