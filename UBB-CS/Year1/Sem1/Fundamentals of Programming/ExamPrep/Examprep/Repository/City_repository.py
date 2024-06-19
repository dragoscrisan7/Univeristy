from Domain.City_Data import city_data
from random import randint


class city_repository:
    def __init__(self):
        self.__city_data = city_data(1, 100, 1000, 20, 3, 1, 1000)

    def advisor(self, grain):
        return "In year " + self.__city_data.year + ", " + self.fed_grain() + \
               "people starved. \n City population is " + self.__city_data.population + "\n City owns " + \
               self.__city_data.acres + " acres of land. \n Harvest was " + self.__city_data.harvest + \
               " units per acre. \n Rats ate" + self.__city_data.rats + " units. \n Land price is " + \
               self.__city_data.land_price + " units per acre. \n \n Grain stocks are " + \
               self.return_grain() + " units."

    def new_year(self):
        self.__city_data.year += self.__city_data.year + 1
        self.add_population()

    def check_acres(self, param):
        if param < 0:
            if param < self.__city_data.acres:
                return False
        elif param*self.__city_data.land_price > self.return_grain():
            return False

        self.__city_data.acres = self.__city_data.acres + param
        self.__city_data.
        return True

    def return_grain(self):
        return self.__city_data.acres_planted*self.__city_data.harvest

    def fed_grain(self):
        fed_people = self.return_grain()/20

        if fed_people >= self.__city_data.population:
            return 0
        else:
            return self.__city_data.population - fed_people

    def add_population(self):
        ppl = self.__city_data.population
        if self.fed_grain() == 0:
            ppl_add = randint(0, 10)
            self.__city_data.population = ppl + ppl_add
        else:
            self.__city_data.population = ppl - self.fed_grain()

    def year_check(self):
        if self.__city_data.year <= 5:
            return True

        return False
