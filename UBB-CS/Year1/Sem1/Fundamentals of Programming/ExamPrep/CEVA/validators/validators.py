
class Validator:
    def validate_coordonate(self, data):
        data = data.strip()
        if len(data) != 5:
            raise ValueError
        try:
            parts = data.split(" ")
            if not (1<= int(parts[0]) <= 6 and 1<= int(parts[1]) <=6):
                raise ValueError
            if not parts[2] in ('XxOo'):
                raise ValueError
        except:
            raise ValueError