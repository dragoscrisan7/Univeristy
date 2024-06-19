def f(l):
    if (l == None):
        raise ValueError()
    for e in l:
        if e % 2 == 1:
            return True
    return False
"""
primeste un sir si verifica daca exista cel putin un element impar in sir si returneaza True, in caz contrar
returneaza false iar in cazul in care lista este goala da raise la Value error
"""

def fTest():
    k = None
    try:
        f(k)
        assert False
    except ValueError:
        assert True
    l = []
    l.append(2)
    l.append(8)
    l.append(6)
    l.append(4)
    assert not f(l)
    l.append(3)
    assert f(l)

for a in range(1,10):
    print(a)