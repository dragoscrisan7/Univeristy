from src.domain.Client import Client
from src.repository.Exceptions import RepositoryException

from random import randint


class ClientRepository:
    """
    A class for the client repository
    """
    def __init__(self):
        """
        Constructor for the ClientRepository class
        """
        self.__repo = []

    def initial_load(self):
        """
        Preloads the repository with 20 randomly generated items
        """
        names = ["Liam", "Noah", "Oliver", "Elijah", "William", "James", "Benjamin",
                 "Lucas", "Henry", "Alexander", "Mason", "Michael", "Ethan", "Daniel",
                 "Jacob", "Logan", "Jackson", "Levi", "Sebastian", "Mateo", "Jack", "Owen",
                 "Theodore", "Aiden", "Samuel", "Joseph", "John", "David", "Wyatt", "Matthew",
                 "Luke", "Asher", "Carter", "Julian", "Grayson", "Leo", "Jayden", "Gabriel",
                 "Isaac", "Lincoln", "Anthony", "Hudson", "Dylan", "Ezra", "Thomas", "Charles",
                 "Christopher", "Jaxon", "Maverick", "Josiah", "Isaiah", "Andrew", "Elias", "Joshua",
                 "Nathan", "Caleb", "Ryan", "Adrian", "Miles", "Eli", "Nolan", "Christian", "Aaron",
                 "Cameron", "Ezekiel", "Colton", "Luca", "Landon", "Hunter", "Jonathan", "Santiago",
                 "Axel", "Easton", "Cooper", "Jeremiah", "Angel", "Roman", "Connor", "Jameson", "Robert",
                 "Greyson", "Jordan", "Ian", "Carson", "Jaxson", "Leonardo", "Nicholas", "Dominic", "Austin",
                 "Everett", "Brooks", "Xavier", "Kai", "Jose", "Parker", "Adam", "Jace", "Wesley", "Kayden",
                 "Silas", "Bennett", "Declan", "Waylon", "Weston", "Evan", "Emmett", "Micah", "Ryder", "Beau",
                 "Damian", "Brayden", "Gael", "Rowan", "Harrison", "Bryson", "Sawyer", "Amir", "Kingston",
                 "Jason", "Giovanni", "Vincent", "Ayden", "Chase", "Myles", "Diego", "Nathaniel", "Legend", "Jonah",
                 "River", "Tyler", "Cole", "Braxton", "George", "Milo", "Zachary", "Ashton", "Luis",
                 "Jasper", "Kaiden", "Adriel", "Gavin", "Bentley", "Calvin", "Zion", "Juan",
                 "Maxwell", "Max", "Ryker", "Carlos", "Emmanuel", "Jayce", "Lorenzo", "Ivan",
                 "Jude", "August", "Kevin", "Malachi", "Elliott", "Rhett", "Archer", "Karter",
                 "Arthur", "Luka", "Elliot", "Thiago", "Brandon", "Camden", "Justin", "Jesus",
                 "Maddox", "King", "Theo", "Enzo", "Matteo", "Emiliano", "Dean", "Hayden", "Finn",
                 "Brody", "Antonio", "Abel", "Alex", "Tristan", "Graham", "Zayden", "Judah",
                 "Xander", "Miguel", "Atlas", "Messiah", "Barrett", "Tucker", "Timothy", "Alan", "Edward",
                 "Leon", "Dawson", "Eric", "Ace", "Victor", "Abraham", "Nicolas", "Jesse", "Charlie",
                 "Patrick", "Walker", "Joel", "Richard", "Beckett", "Blake", "Alejandro", "Avery", "Grant",
                 "Peter", "Oscar", "Matias", "Amari", "Lukas", "Andres", "Arlo", "Colt", "Adonis", "Kyrie",
                 "Steven", "Felix", "Preston", "Marcus", "Holden", "Emilio", "Remington", "Jeremy", "Kaleb",
                 "Brantley", "Bryce", "Mark", "Knox", "Israel", "Phoenix", "Kobe", "Nash", "Griffin", "Caden",
                 "Kenneth", "Kyler", "Hayes", "Jax", "Rafael", "Beckham", "Javier", "Maximus", "Simon", "Paul",
                 "Omar", "Kaden", "Kash", "Lane", "Bryan", "Riley", "Zane", "Louis", "Aidan", "Paxton",
                 "Maximiliano", "Karson", "Cash", "Cayden", "Emerson", "Tobias", "Ronan", "Brian", "Dallas",
                 "Bradley", "Jorge", "Walter", "Josue", "Khalil", "Damien", "Jett", "Kairo", "Zander", "Andre",
                 "Cohen", "Crew", "Hendrix", "Colin", "Chance", "Malakai", "Clayton", "Daxton", "Malcolm",
                 "Lennox", "Martin", "Jaden", "Kayson", "Bodhi", "Francisco", "Cody", "Erick", "Kameron",
                 "Atticus", "Dante", "Jensen", "Cruz", "Finley", "Brady", "Joaquin", "Anderson", "Gunner",
                 "Muhammad", "Zayn", "Derek", "Raymond", "Kyle", "Angelo", "Reid", "Spencer", "Nico", "Jaylen",
                 "Jake", "Prince", "Manuel", "Ali", "Gideon", "Stephen", "Ellis", "Orion", "Rylan", "Eduardo",
                 "Mario", "Rory", "Cristian", "Odin", "Tanner", "Julius", "Callum", "Sean", "Kane", "Ricardo",
                 "Travis", "Wade", "Warren", "Fernando", "Titus", "Leonel", "Edwin", "Cairo", "Corbin",
                 "Dakota", "Ismael", "Colson", "Killian", "Major", "Tate", "Gianni", "Elian", "Remy", "Lawson",
                 "Niko", "Nasir", "Kade", "Armani", "Ezequiel", "Marshall", "Hector", "Desmond", "Kason",
                 "Garrett", "Jared", "Cyrus", "Russell", "Cesar", "Tyson", "Malik", "Donovan", "Jaxton", "Cade",
                 "Romeo", "Nehemiah", "Sergio", "Iker", "Caiden", "Jay", "Pablo", "Devin", "Jeffrey", "Otto",
                 "Kamari", "Ronin", "Johnny", "Clark", "Ari", "Marco", "Edgar", "Bowen", "Jaiden", "Grady",
                 "Zayne", "Sullivan", "Jayceon", "Sterling", "Andy", "Conor", "Raiden", "Royal", "Royce",
                 "Solomon", "Trevor", "Winston", "Emanuel", "Finnegan", "Pedro", "Luciano", "Harvey",
                 "Franklin", "Noel", "Troy", "Princeton", "Johnathan", "Erik", "Fabian", "Oakley", "Rhys",
                 "Porter", "Hugo", "Frank", "Damon", "Kendrick", "Mathias", "Milan", "Peyton", "Wilder",
                 "Callan", "Gregory", "Seth", "Matthias", "Briggs", "Ibrahim", "Roberto", "Conner", "Quinn",
                 "Kashton", "Sage", "Santino", "Kolton", "Alijah", "Dominick", "Zyaire", "Apollo", "Kylo",
                 "Reed", "Philip", "Kian", "Shawn", "Kaison", "Leonidas", "Ayaan", "Lucca", "Memphis", "Ford",
                 "Baylor", "Kyson", "Uriel", "Allen", "Collin", "Ruben", "Archie", "Dalton", "Esteban", "Adan",
                 "Forrest", "Alonzo", "Isaias", "Leland", "Jase", "Dax", "Kasen", "Gage", "Kamden", "Marcos",
                 "Jamison", "Francis", "Hank", "Alexis", "Tripp", "Frederick", "Jonas", "Stetson", "Cassius",
                 "Izaiah", "Eden", "Maximilian", "Rocco", "Tatum", "Keegan", "Aziel", "Moses", "Bruce", "Lewis",
                 "Braylen", "Omari", "Mack", "Augustus", "Enrique", "Armando", "Pierce", "Moises", "Asa", "Shane",
                 "Emmitt", "Soren", "Dorian", "Keanu", "Zaiden", "Raphael", "Deacon", "Abdiel", "Kieran", "Phillip",
                 "Ryland", "Zachariah", "Casey", "Zaire", "Albert", "Baker", "Corey", "Kylan", "Denver", "Gunnar",
                 "Jayson", "Drew", "Callen", "Jasiah", "Drake", "Kannon", "Braylon", "Sonny", "Bo", "Moshe",
                 "Huxley", "Quentin", "Rowen", "Santana", "Cannon", "Kenzo", "Wells", "Julio", "Nikolai",
                 "Conrad", "Jalen", "Makai", "Benson", "Derrick", "Gerardo", "Davis", "Abram", "Mohamed",
                 "Ronald", "Raul", "Arjun", "Dexter", "Kaysen", "Jaime", "Scott", "Lawrence", "Ariel", "Skyler",
                 "Danny", "Roland", "Chandler", "Yusuf", "Samson", "Case", "Zain", "Roy", "Rodrigo", "Sutton",
                 "Boone", "Saint", "Saul", "Jaziel", "Hezekiah", "Alec", "Arturo", "Jamari", "Jaxtyn", "Julien",
                 "Koa", "Reece", "Landen", "Koda", "Darius", "Sylas", "Ares", "Kyree", "Boston", "Keith", "Taylor",
                 "Johan", "Edison", "Sincere", "Watson", "Jerry", "Nikolas", "Quincy", "Shepherd", "Brycen",
                 "Marvin", "Dariel", "Axton", "Donald", "Bodie", "Finnley", "Onyx", "Rayan", "Raylan", "Brixton",
                 "Colby", "Shiloh", "Valentino", "Layton", "Trenton", "Landyn", "Alessandro", "Ahmad", "Gustavo",
                 "Ledger", "Ridge", "Ander", "Ahmed", "Kingsley", "Issac", "Mauricio", "Tony", "Leonard", "Mohammed",
                 "Uriah", "Duke", "Kareem", "Lucian", "Marcelo", "Aarav", "Leandro", "Reign", "Clay", "Kohen",
                 "Dennis", "Samir", "Ermias", "Otis", "Emir", "Nixon", "Ty", "Sam", "Fletcher", "Wilson", "Dustin",
                 "Hamza", "Bryant", "Flynn", "Lionel", "Mohammad", "Cason", "Jamir", "Aden", "Dakari", "Justice",
                 "Dillon", "Layne", "Zaid", "Alden", "Nelson", "Devon", "Titan", "Chris", "Khari", "Zeke", "Noe",
                 "Alberto", "Roger", "Brock", "Rex", "Quinton", "Alvin", "Cullen", "Azariah", "Harlan", "Kellan",
                 "Lennon", "Marcel", "Keaton", "Morgan", "Ricky", "Trey", "Karsyn", "Langston", "Miller", "Chaim",
                 "Salvador", "Amias", "Tadeo", "Curtis", "Lachlan", "Amos", "Anakin", "Krew", "Tomas", "Jefferson",
                 "Yosef", "Bruno", "Korbin", "Augustine", "Cayson", "Mathew", "Vihaan", "Jamie", "Clyde", "Brendan",
                 "Jagger", "Carmelo", "Harry", "Nathanael", "Mitchell", "Darren", "Ray", "Jedidiah", "Jimmy",
                 "Lochlan", "Bellamy", "Eddie", "Rayden", "Reese", "Stanley", "Joe", "Houston", "Douglas",
                 "Vincenzo", "Casen", "Emery", "Joziah", "Leighton", "Marcellus", "Atreus", "Aron", "Hugh",
                 "Musa", "Tommy", "Alfredo", "Junior", "Neil", "Westley", "Banks", "Eliel", "Melvin", "Maximo",
                 "Briar", "Colten", "Lance", "Nova", "Trace", "Axl", "Ramon", "Vicente", "Brennan", "Caspian",
                 "Remi", "Deandre", "Legacy", "Lee", "Valentin", "Ben", "Louie", "Westin", "Wayne", "Benicio",
                 "Grey", "Zayd", "Gatlin", "Mekhi", "Orlando", "Bjorn", "Harley", "Alonso", "Rio", "Aldo", "Byron",
                 "Eliseo", "Ernesto", "Talon", "Thaddeus", "Brecken", "Kace", "Kellen", "Enoch", "Kiaan",
                 "Lian", "Creed", "Rohan", "Callahan", "Jaxxon", "Ocean", "Crosby", "Dash", "Gary", "Mylo", "Ira",
                 "Magnus", "Salem", "Abdullah", "Kye", "Tru", "Forest", "Jon", "Misael", "Madden", "Braden", "Carl",
                 "Hassan", "Emory", "Kristian", "Alaric", "Ambrose", "Dario", "Allan", "Bode", "Boden", "Juelz",
                 "Kristopher", "Genesis", "Idris", "Ameer", "Anders", "Darian", "Kase", "Aryan", "Dane", "Guillermo",
                 "Elisha", "Jakobe", "Thatcher", "Eugene", "Ishaan", "Larry", "Wesson", "Yehuda", "Alvaro", "Bobby",
                 "Bronson", "Dilan", "Kole", "Kyro", "Tristen", "Blaze", "Brayan", "Jadiel", "Kamryn", "Demetrius",
                 "Maurice", "Arian", "Kabir", "Rocky", "Rudy", "Randy", "Rodney", "Yousef", "Felipe", "Robin", "Aydin",
                 "Dior", "Kaiser", "Van", "Brodie", "London", "Eithan", "Stefan", "Ulises", "Camilo", "Branson",
                 "Jakari", "Judson", "Yahir", "Zavier", "Damari", "Jakob", "Jaxx", "Bentlee", "Cain", "Niklaus",
                 "Rey", "Zahir", "Aries", "Blaine", "Kyng", "Castiel", "Henrik", "Joey", "Khalid", "Bear", "Graysen",
                 "Jair", "Kylen", "Darwin", "Alfred", "Ayan", "Kenji", "Zakai", "Avi", "Cory", "Fisher", "Jacoby",
                 "Osiris", "Harlem", "Jamal", "Santos", "Wallace", "Brett", "Fox", "Leif", "Maison", "Reuben", "Adler",
                 "Zev", "Calum", "Kelvin", "Zechariah", "Bridger", "Mccoy", "Seven", "Shepard", "Azrael", "Leroy",
                 "Terry", "Harold", "Mac", "Mordechai", "Ahmir", "Cal", "Franco", "Trent", "Blaise", "Coen", "Dominik",
                 "Marley", "Davion", "Jeremias", "Riggs", "Jones", "Will", "Damir", "Dangelo", "Canaan", "Dion",
                 "Jabari", "Landry", "Salvatore", "Kody", "Hakeem", "Truett", "Gerald", "Lyric", "Gordon", "Jovanni",
                 "Kamdyn", "Alistair", "Cillian", "Foster", "Terrance", "Murphy", "Zyair", "Cedric", "Rome", "Abner",
                 "Colter", "Dayton", "Jad", "Xzavier", "Rene", "Vance", "Duncan", "Frankie", "Bishop", "Davian",
                 "Everest", "Heath", "Jaxen", "Marlon", "Maxton", "Reginald", "Harris", "Jericho", "Keenan", "Korbyn",
                 "Wes", "Eliezer", "Jeffery", "Kalel", "Kylian", "Turner", "Willie", "Rogelio", "Ephraim"]

        for iterator in range(20):
            self.__repo.append(Client(iterator, names[randint(0, len(names) - 1)] + " " +
                                      names[randint(0, len(names) - 1)]))

    def get_repo(self):
        """
        :return: the clients repository list
        """
        return self.__repo

    def add(self, new_client):
        """
        Adds a new client to the repository
        :param new_client: the new client
        :type: an object belonging to the Client class
        """
        for client in self.__repo:
            if client.get_client_id() == new_client.get_client_id():
                raise RepositoryException("This ID already exists")

        self.__repo.append(new_client)

    def remove(self, client_id):
        """
        Removes a client from the repository
        :param client_id: the ID of the client
        :type: integer, positive number
        """
        for client in self.__repo:
            if client.get_client_id() == client_id:
                self.__repo.remove(client)
                return None

        raise RepositoryException("There is no client with the given ID!")

    def update(self, client_id, new_name):
        """
        Modifies client name
        :param client_id: the ID of the client that should be updated
        :type: integer, positive number
        :param new_name: the new name of the client
        :type: string, text
        """
        for client in self.__repo:
            if client.get_client_id() == client_id:
                client.set_name(new_name)
                return None

        raise RepositoryException("There is no client with the given ID!")

    def list(self):
        """
        :return: a string representation of the repository
        """
        value = ""
        for client in self.__repo:
            value += (str(client) + "\n")

        return value.rstrip()

    def search(self, choice, data):
        """
        searches for the clients that match the criteria
        :param choice: the type of search
        :type: integer, positive, from 1 to 3
        :param data: the criteria
        :type: string, text, the name
        """
        clients_to_print = "" if len(self.__repo) > 0 else "The list of books is empty."
        if choice == 1:
            for client in self.__repo:
                if int(client.get_client_id()) == int(data):
                    clients_to_print += (str(client) + "\n")
            if len(clients_to_print) == 0:
                return RepositoryException("There is no client with the given ID!")
            else:
                return clients_to_print.rstrip()
        elif choice == 2:
            for client in self.__repo:
                if client.get_name().find(data) != -1:
                    clients_to_print += (str(client) + "\n")
            if len(clients_to_print) == 0:
                return RepositoryException("There is no client with the given name!")
            else:
                return clients_to_print.rstrip()

    def get_all_entities(self):
        """
        :return: a list of the entire repo, necessary for tests
        """
        return list(self.__repo)