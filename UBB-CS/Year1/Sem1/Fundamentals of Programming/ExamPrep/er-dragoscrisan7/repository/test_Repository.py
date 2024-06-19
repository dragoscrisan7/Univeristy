from unittest import TestCase
from repository.Repository import repository


class Testrepository(TestCase):
    repo = repository()

    def test_get_list(self):
        pass

    def test_add(self):
        coord = [1, 1, 'o']
        self.repo.add(coord)
        lista = self.repo.get_list()
        self.assertEqual(lista[1][1], 'o')

    def test_get_symbol(self):
        symbol = self.repo.get_symbol()
        self.assertEqual(symbol, 'o')

    def test_check_adjacent(self):
        coord = [2, 1, 'x']
        self.repo.add(coord)
        coord = [1, 2, 'x']
        self.repo.add(coord)
        x = self.repo.check_adjacent(coord)
        self.assertEqual(x, -1)
        coord = [2, 2, 'x']
        x = self.repo.check_adjacent(coord)
        self.assertEqual(x, 2)

    def test_check_win(self):
        x = self.repo.check_win()
        self.assertEqual(x, 0)

    def test_all(self):
        self.test_add()
        self.test_get_symbol()
        self.test_check_adjacent()
        self.test_check_win()
