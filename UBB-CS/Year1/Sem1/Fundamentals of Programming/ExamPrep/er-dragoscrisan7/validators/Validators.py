class validators:
    def vali_coord(self, cmd):
        coord = cmd.strip()
        if len(coord) != 5:
            raise ValueError
        try:
            parts = coord.split(",")
            if not (1 <= int(parts[0]) <= 6 and 1 <= int(parts[1]) <= 6):
                raise ValueError
            if not parts[2] in 'XxOo':
                raise ValueError
        except:
            raise ValueError
