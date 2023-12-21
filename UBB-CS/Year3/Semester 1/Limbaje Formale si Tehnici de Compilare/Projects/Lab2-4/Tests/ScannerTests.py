from Utils.Scanner import Scanner
from Utils.SymbolTable import SymbolTable


def ScannerTests():
    symbol_table = SymbolTable(size=77)

    output_fip_file = "output_fip.txt"
    output_symbol_table_file = "output_symbol_table.txt"

    scanner = Scanner(symbol_table)
    scanner.buffering_from_file("Utils/CodeBeingRead")
    print("FIP Table:")
    for code, position in scanner.get_fip_table():
        print(f"{code} {position}")

    print(symbol_table.__str__())

    scanner.write_tables_to_files(output_fip_file, output_symbol_table_file)