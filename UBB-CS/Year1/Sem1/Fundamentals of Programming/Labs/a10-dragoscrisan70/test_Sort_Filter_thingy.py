from unittest import TestCase
from Sort_Filter_thingy import Sort, Filter, Dos


class TestSort(TestCase):
    def test_shell(self):
        sir = Dos([5, 2, 3, 4, 1])
        Sort.shell(sir, cmp=lambda a, b: a < b)
        assert sir[0] == 1
        assert sir[1] == 2
        assert sir[2] == 3
        assert sir[3] == 4
        assert sir[4] == 5


class TestFilter(TestCase):
    def test_filter(self):
        sir = Dos([5, 2, 3, 4, 1])
        Filter.filter(sir, cmp=lambda a: a % 2 == 1)
        assert sir[0] == 2
        assert sir[1] == 4
