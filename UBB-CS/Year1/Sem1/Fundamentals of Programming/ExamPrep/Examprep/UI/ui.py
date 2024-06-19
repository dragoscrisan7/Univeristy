class Ui:
    def __init__(self, city_serv):
        self.city_serv = city_serv

    def menu(self):
        self.city_serv.advisor_text(2000)
        while self.city_serv.year_check:
            acres_bought_sold = input("Acres to buy/sell(+/-) -> ")
            while not self.city_serv.check_acres_bought:
                print("Incorect input")
                acres_bought_sold = input("Acres to buy/sell(+/-) -> ")

            food = input("Units to be fed to population -> ")
            acres_planted = input("Acres to plant -> ")

            self.city_serv.advisor_text(food)
