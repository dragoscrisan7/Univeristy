class city_data:

    def __init__(self, year, population, acres, land_price, harvest, rats, acres_planted):
        self.__year = year
        self.__population = population
        self.__acres = acres
        self.__land_price = land_price
        self.__harvest = harvest
        self.__rats = rats
        self.acres_planted = acres_planted

    @property
    def acres_planted(self):
        return self.__acres_planted

    @acres_planted.setter
    def acres_planted(self, new):
        self.__acres_planted = new

    @property
    def year(self):
        return self.__year

    @year.setter
    def year(self, new):
        self.__year = new

    @property
    def population(self):
        return self.__population

    @population.setter
    def population(self, new):
        self.__population = new

    @property
    def acres(self):
        return self.__acres

    @acres.setter
    def acres(self, new):
        self.__acres = new

    @property
    def land_price(self):
        return self.__land_price

    @land_price.setter
    def land_price(self, new):
        self.__land_price = new

    @property
    def harvest(self):
        return self.__harvest

    @harvest.setter
    def harvest(self, new):
        self.__harvest = new

    @property
    def rats(self):
        return self.__rats

    @rats.setter
    def rats(self, new):
        self.__rats = new

    def __str__(self):
        return "(year:" + self.__year + ", population:" + self.__population + ", acres:" + self.__acres + \
               ", land_price:" + self.__land_price + ", harvest:" + self.__harvest + ", rats:" + self.__rats + \
               ", acres_planted:" + self.__acres_planted + ")"
