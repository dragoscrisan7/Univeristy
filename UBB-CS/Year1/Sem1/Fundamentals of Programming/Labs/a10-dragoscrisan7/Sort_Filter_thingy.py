class Sort:
    def __init__(self):
        pass

    @staticmethod
    def shell(arr, cmp=lambda a, b: True):
        n = len(arr)
        gap = n // 2
        while gap > 0:

            for i in range(gap, n):

                temp = arr[i]
                j = i

                while j >= gap and cmp(temp, arr[j - gap]):
                    arr[j] = arr[j - gap]
                    j -= gap
                arr[j] = temp
            gap //= 2


class Filter:
    def __init__(self):
        pass

    @staticmethod
    def filter(arr, cmp=lambda a: True):
        n = len(arr)
        i = 0
        while i < n:
            if cmp(arr[i]):
                del(arr[i])
                n -= 1
                i -= 1
            i += 1


class Dos:
    def __init__(self, lista):
        self.lista = lista
        self.index = 0
        self.len = len(self.lista)

    def get_repo(self):
        return self.lista

    def __iter__(self):
        self.index = 0
        return self

    def __next__(self):
        if self.index >= self.len:
            raise StopIteration
        current = self.index
        self.index += 1
        return self.lista[current]

    def __getitem__(self, item):
        if 0 <= item <= len(self.lista):
            return self.lista[item]
        else:
            raise Exception("Not a valid position")

    def __setitem__(self, key, value):
        if 0 <= key <= len(self.lista):
            self.lista[key] = value
        else:
            raise Exception("Not a valid position")

    def __delitem__(self, item):
        for element in self.lista:
            if element == item:
                self.lista.remove(element)
                return

    def __len__(self):
        return len(self.lista)

    def __str__(self):
        ls = ""
        for a in self.lista:
            ls += f"{a} "
        return ls

    def add(self, item):
        self.lista.append(item)


nums = Dos([5, 10, 134, 0, 23, 5, 7])
for num in nums:
    print(num)

Sort.shell(nums, cmp=lambda a, b: a < b)
for num in nums:
    print(num)

Filter.filter(nums, cmp=lambda a: a % 2 == 1)

for num in nums:
    print(num)
