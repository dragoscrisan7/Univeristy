n=input("enter n: ")
s=int(n)+1
ok=1
a=1
while ok==1:
    d=int(2)
    a=1
    while d<s/2+1 and a==1:
        if s%d==0:
            a=0
        d=d+1
    if a==1:
        ok=0
        print(s)
    s=s+1



