def gen(n):
    yield 1
    yield 2
    for i in range(n):
        yield i*i
    for i in range(n):
        yield i*2

s = 0
for i in gen(10):
    print(i)
    s += i
print(s)