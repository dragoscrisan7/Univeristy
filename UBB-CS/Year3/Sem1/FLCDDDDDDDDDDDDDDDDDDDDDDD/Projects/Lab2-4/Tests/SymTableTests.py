from Utils.SymbolTable import SymbolTable


def SymTableTests():
    symbol_table_tests = SymbolTable(size=77)
    pos = (-1, -1)
    pos2 = (-1, -1)
    pos3 = (-1, -1)
    try:
        pos = symbol_table_tests.add('apple', 'fruit')
        print(f"apple {pos}")
        print(f"banana {symbol_table_tests.add('banana')}")
        print(f"cherry {symbol_table_tests.add('cherry')}")
        print(f"date {symbol_table_tests.add('date')}")
        print(f"elderberry {symbol_table_tests.add('elderberry')}")

        print(f"2 {symbol_table_tests.add(2)}")
        print(f"5 {symbol_table_tests.add(5)}")
        pos2 = symbol_table_tests.add(50)
        print(f"50 {pos2}")
        print(f"30 {symbol_table_tests.add(30)}")
        print(f"111 {symbol_table_tests.add(111)}")
        print(f"77 {symbol_table_tests.add(77)}")
        print(f"95 {symbol_table_tests.add(95)}")

        print(f"str1 {symbol_table_tests.add('str1')}")
        print(f"str2 {symbol_table_tests.add('str2')}")
        print(f"str3 {symbol_table_tests.add('str3')}")
        print(f"str4 {symbol_table_tests.add('str4')}")
        pos3 = symbol_table_tests.add("str5")
        print(f"str5 {pos3}")

        print(f"apple {symbol_table_tests.add('apple')}")
    except Exception as e:
        print(e)

    print(symbol_table_tests)

    try:
        assert symbol_table_tests.has("apple") == pos, f"apple does not have position {pos}"
        assert symbol_table_tests.get_position(50) == pos2, f"50 does not have position {pos2}"
        assert symbol_table_tests.get_psition("str5") == pos3, f"str5 does not have position {pos3}"
        assert symbol_table_tests.has("aaaa") == (-1, -1), "aaaa exists in the table"
        assert symbol_table_tests.get_position(95) == (2, 2), "95 does not have position (2, 2)"
    except AssertionError as e:
        print(e)

    try:
        print(f"77 {symbol_table_tests.get_position(77)}")
        assert symbol_table_tests.get_position(77) == (2, 2), "77 does not have position (2, 2)"
    except AssertionError as e:
        print(e)

    try:
        print(f"elderberry {symbol_table_tests.has('elderberry')}")
        assert symbol_table_tests.has('elderberry') == pos, f"elderberry does not have position {pos}"
    except AssertionError as e:
        print(e)
