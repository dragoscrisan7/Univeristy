class city_services:
    def __init__(self, city_repository):
        self.city_repo = city_repository

    def year_check(self):
        if self.city_repo.year_check:
            return True

        return False

    def new_year(self):
        self.city_repo.new_year()

    def check_acres_bought(self, acres):
        if not acres.isalpha():
            return False
        if not self.city_repo.check_acres(int(acres)):
            return False

        return True


    def advisor_text(self, grain):
        print(self.city_repo.advisor(grain))
