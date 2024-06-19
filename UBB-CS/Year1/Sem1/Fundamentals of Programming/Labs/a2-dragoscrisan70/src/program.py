#
# Write the implementation for A2 in this file
#

# UI section

# (write all functions that have input or print statements here).

# Ideally, this section should not contain any calculations relevant to program functionalities

#print('Hello A2')

# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!

#Property 7 : The difference between the modulus of consecutive numbers is a prime number.
#Property 10 : Sum of its elements is 10+10i


import math


def print_menu():
    print(' 1 - to read a complex number')
    print(' 2 - to write the list of complex numbers')
    print(' 3 - to display the longest sequence that respects the seventh property')
    print(' 4 - to display the longest sequence that respects the tenth property')
    print(' 5 to exit')

def create_number(real,imaginary):
    return{'real':real,'imaginary':imaginary}

def read_number(myList):
    x=int(input('Real part is: '))
    y=int(input('Imaginary part is: '))
    myList.append(create_number(x, y))
    print('Number added to the list')

def generate_number():
    return [create_number(-2,-3),create_number(4,4),create_number(6,6),create_number(3,-4),create_number(3,-1),
            create_number(1,-2),create_number(9,12),create_number(2,6),create_number(8,4),create_number(2,6)]


def show_list(myList):
    for a in range(0, len(myList)):
        if myList[a]['imaginary']<0:
            print(myList[a]['real'], myList[a]['imaginary'], 'i')
        elif myList[a]['imaginary']==0:
            print(myList[a]['real'])
        else:
            print(myList[a]['real'], ' + ', myList[a]['imaginary'], 'i')

def is_prime(x):
    if x!=int(x):
        return False
    if x<2:
        return False
    if x==2:
        return True
    if x%2==0:
        return False
    d=int(2)
    while d*d<=x:
        if x%d==0:
            return False
        d=d+1
    return True

def modulus(x):
    if x<0:
        return -x
    else:
        return x


def modulus_complex(x,myList):
    y=myList[x]['real']
    z=myList[x]['imaginary']
    x= y*y+z*z
    x= math.sqrt(x)
    x=int(x)
    return x

def Property7(myList):
    maxseq = 0
    cca = 0
    ccb = 0
    a=0
    while a<len(myList) - 1:
        if is_prime(modulus(modulus_complex(a,myList)-modulus_complex(a+1,myList))):
            ca = a
            cb = a
            seqleng = 1
            a = a+1
            while a<=len(myList)-2 and is_prime(modulus(modulus_complex(a,myList)-modulus_complex(a+1,myList))):
                seqleng = seqleng +1
                cb=a
                a=a+1
            if seqleng > maxseq:
                maxseq = seqleng
                cca = ca
                ccb = cb
            a=cb+1
        else:
            a=a+1
    if maxseq == 0:
        print('there are no numbers that respect the property')
    else:
        print('The longest sequence is ')
        if maxseq == 1:
            print(myList[cca]['real'], '+', myList[cca]['imaginary'], 'i ;')
        else:
            for c in range(cca,ccb+1):
                print(myList[c]['real'], '+', myList[c]['imaginary'], 'i ;')
def property10(myList):
    maxseq = 0
    fa=0
    fb=0
    for a in range(0, len(myList) - 1):
        if myList[a]['real']+myList[a + 1]['real']==10 and myList[a]['imaginary']+myList[a + 1]['imaginary']==10:
            ia = a
            ib = a
            seqleng = 1
            if a<len(myList)-2:
                while a+1<len(myList) and myList[a]['real']+myList[a + 1]['real']==10 and myList[a]['imaginary']+myList[a + 1]['imaginary']==10:
                    seqleng = seqleng +1
                    ib = a
                    a = a+1
            if maxseq<seqleng:
                maxseq=seqleng
                fa=ia
                fb=ib
            seqleng=0
    if maxseq==0:
        print('there are no numbers that respect the property')
    else:
        print('the longest sequence that respects the property is: ')
        for c in range(fa,fb+2):
            print(myList[c]['real'], '+', myList[c]['imaginary'], 'i ;')


def start():
    myList = []
    myList = generate_number()
    while True:
        print_menu()
        option=int(input(' Option: '))
        if option==1:
            read_number(myList)
        elif option==2:
            show_list(myList)
        elif option==5:
            return
        elif option==3:
            Property7(myList)
        elif option==4:
            property10(myList)
start()