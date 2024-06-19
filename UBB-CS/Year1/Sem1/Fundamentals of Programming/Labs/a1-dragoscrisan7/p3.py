sq_number=int(1)
sq_position=int(0)
n=input("n=")
n=int(n)
cont=int(0)
ok=1
def prime(n):
    d=int(2)
    if n==1 or n==2:
        return 1
    while d<n:
        if n%d==0:
            return 0
        d=d+1
    return 1
while sq_position<n and ok==1:
    if prime(sq_number)==1:
        sq_position=sq_position+1
        if sq_position==n:
            ok=0
            print(sq_number)
    else:
        diviser=int(2)
        copy=int(sq_number)
        while diviser<sq_number+1:
            if sq_number%diviser==0:
                while sq_number%diviser==0:
                    sq_number= sq_number / diviser
                sq_position=sq_position+1
                if sq_position==n:
                    ok=0
                    print(diviser)
            diviser=diviser+1
        sq_number=copy
    sq_number=sq_number+1


