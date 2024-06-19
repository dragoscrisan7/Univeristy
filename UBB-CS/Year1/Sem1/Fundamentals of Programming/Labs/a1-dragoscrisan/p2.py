a=int(1)
b=int(1)
n=input("n=")
n=int(n)
c=int(a+b)
while c<n+1:
    a=b
    b=c
    c=a+b
print(c)
