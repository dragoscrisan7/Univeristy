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


class IterableDataStructure:
    def __init__(self, lista):
        self.main_list = lista

    def get_list(self):
        return self.main_list

    def __getitem__(self, list_position):
        if 0 <= list_position <= len(self.main_list):
            return self.main_list[list_position]
        else:
            raise Exception("Not a valid position")

    def __setitem__(self, list_position, item):
        if 0 <= list_position <= len(self.main_list):
            self.main_list[list_position] = item
        else:
            raise Exception("Not a valid position")

    def __delitem__(self, item):
        for element in self.main_list:
            if element == item:
                self.main_list.remove(element)
                return

    def __len__(self):
        return len(self.main_list)

    def __str__(self):
        ls = ""
        for a in self.main_list:
            ls += f"{a} "
        return ls

    def append(self, item):
        self.main_list.append(item)

    def add(self, item):
        self.main_list.append(item)
