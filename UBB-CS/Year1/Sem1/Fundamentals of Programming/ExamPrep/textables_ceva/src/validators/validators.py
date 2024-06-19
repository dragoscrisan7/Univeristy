
class Validator:

    def validate_coord(self, coord):
        try:
            if len(coord)!=2:
                raise ValueError
            if not coord[0] in 'ABCDEFG':
                raise ValueError
            if not int(coord[1]) in range(1,8):
                raise ValueError
        except:
            raise ValueError