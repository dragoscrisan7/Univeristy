class HashTable:
    def __init__(self, size=100):
        self.size = size
        self.table = [None] * self.size

    def hash(self, key):
        if isinstance(key, int):
            return key % self.size
        elif isinstance(key, str):
            return sum(ord(char) for char in key) % self.size
        else:
            raise ValueError("Unsupported key type")

    def getSize(self):
        return self.size

    def getHashValue(self, key):
        return self.hash(key)

    def add(self, key):
        index = self.hash(key)
        if self.table[index] is None:
            self.table[index] = []
        for i, entry in enumerate(self.table[index]):
            if entry[0] == key:
                return (index, i)
        self.table[index].append((key, None))
        return (index, len(self.table[index]) - 1)

    def contains(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            for entry in self.table[index]:
                if entry[0] == key:
                    return True
        return False

    def getPosition(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            for i, entry in enumerate(self.table[index]):
                if entry[0] == key:
                    return (index, i)
        return (-1, -1)

    def __str__(self):
        return str(self.table)


class SymbolTable:
    def __init__(self, size=100):
        self.identifier_table = HashTable(size)
        self.int_constant_table = HashTable(size)
        self.string_constant_table = HashTable(size)

    def addIdentifier(self, name):
        return self.identifier_table.add(name)

    def addIntConstant(self, constant):
        return self.int_constant_table.add(constant)

    def addStringConstant(self, constant):
        return self.string_constant_table.add(constant)

    def hasIdentifier(self, name):
        return self.identifier_table.contains(name)

    def hasIntConstant(self, constant):
        return self.int_constant_table.contains(constant)

    def hasStringConstant(self, constant):
        return self.string_constant_table.contains(constant)

    def getPositionIdentifier(self, name):
        return self.identifier_table.getPosition(name)

    def getPositionIntConstant(self, constant):
        return self.int_constant_table.getPosition(constant)

    def getPositionStringConstant(self, constant):
        return self.string_constant_table.getPosition(constant)

    # def __str__(self):
    #     return f"Identifiers: {self.identifier_table}\nInt Constants: {self.int_constant_table}\nString Constants: {self.string_constant_table}"

    def __str__(self):
        output = []
        for table in [self.identifier_table, self.int_constant_table, self.string_constant_table]:
            entries = []
            for entry in table.table:
                if entry is not None:
                    entries.append(entry)
            output.append(entries)
        return f"Identifiers: {output[0]}\nInt Constants: {output[1]}\nString Constants: {output[2]}"

if __name__ == "__main__":
    symbol_table = SymbolTable(size=77)
    p1 = (-1, -1)
    p2 = (-1, -1)
    p3 = (-1, -1)
    try:
        p1 = symbol_table.addIdentifier("apple")
        print("\n")
        print(f"apple {p1}")
        print(f"banana {symbol_table.addIdentifier('banana')}")
        print(f"cherry {symbol_table.addIdentifier('cherry')}")
        print(f"date {symbol_table.addIdentifier('date')}")
        print(f"elderberry {symbol_table.addIdentifier('elderberry')}")

        print(f"2 {symbol_table.addIntConstant(2)}")
        print(f"5 {symbol_table.addIntConstant(5)}")
        p2 = symbol_table.addIntConstant(50)
        print(f"50 {p2}")
        print(f"30 {symbol_table.addIntConstant(30)}")
        print(f"111 {symbol_table.addIntConstant(111)}")
        print(f"77 {symbol_table.addIntConstant(77)}")
        print(f"95 {symbol_table.addIntConstant(95)}")

        print(f"str1 {symbol_table.addStringConstant('str1')}")
        print(f"str2 {symbol_table.addStringConstant('str2')}")
        print(f"str3 {symbol_table.addStringConstant('str3')}")
        print(f"str4 {symbol_table.addStringConstant('str4')}")
        p3 = symbol_table.addStringConstant("str5")
        print(f"str5 {p3}")

        print(f"apple {symbol_table.addIdentifier('apple')}")
    except Exception as e:
        print(e)

    print(symbol_table)

    try:
        assert symbol_table.getPositionIdentifier("apple") == p1, f"apple does not have position {p1}"
        assert symbol_table.getPositionIntConstant(50) == p2, f"50 does not have position {p2}"
        assert symbol_table.getPositionStringConstant("str5") == p3, f"str5 does not have position {p3}"
        assert symbol_table.getPositionIdentifier("aaaa") == (-1, -1), "aaaa exists in the table"
        assert symbol_table.getPositionIntConstant(95) == (2, 2), "95 does not have position (2, 2)"
    except AssertionError as e:
        print(e)

    try:
        print(f"77 {symbol_table.getPositionIntConstant(77)}")
        assert symbol_table.getPositionIntConstant(77) == (2, 2), "77 does not have position (2, 2)"
    except AssertionError as e:
        print(e)

    try:
        print(f"elderberry {symbol_table.getPositionIdentifier('elderberry')}")
        assert symbol_table.getPositionIdentifier('elderberry') == p1, f"elderberry does not have position {p1}"
    except AssertionError as e:
        print(e)

    try:
        print(f"22 {symbol_table.getPositionIntConstant(22)}")
        assert symbol_table.getPositionIntConstant(22) == p2, f"22 does not have position {p2}"
    except AssertionError as e:
        print(e)

    try:
        print(f"grape {symbol_table.getPositionStringConstant('grape')}")
        assert symbol_table.getPositionStringConstant('grape') == p3, f"grape does not have position {p3}"
    except AssertionError as e:
        print(e)
