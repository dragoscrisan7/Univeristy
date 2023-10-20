class SymbolTable:
    def __init__(self, size=100):
        self.size = size
        self.table = [None] * self.size

    def hash(self, key):
        # Simple hash function for demonstration purposes.
        # You can implement a more robust hash function.
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash(key)
        if self.table[index] is None:
            self.table[index] = []
        # Check if the key already exists, and if so, update its value
        for i, entry in enumerate(self.table[index]):
            if entry[0] == key:
                self.table[index][i] = (key, value)
                return
        self.table[index].append((key, value))

    def lookup(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            for entry in self.table[index]:
                if entry[0] == key:
                    return entry[1]
        return None

    def remove(self, key):
        index = self.hash(key)
        if self.table[index] is not None:
            for entry in self.table[index]:
                if entry[0] == key:
                    self.table[index].remove(entry)
                    return


# Example usage
if __name__ == "__main__":
    st = SymbolTable()

    st.insert("variable1", 42)
    st.insert("variable2", 55)
    st.insert("variable1", 99)  # Update an existing key

    print(st.lookup("variable1"))  # Output: 99
    print(st.lookup("variable3"))  # Output: None

    st.remove("variable2")
    print(st.lookup("variable2"))  # Output: None
