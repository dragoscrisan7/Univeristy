"""
  Write non-UI functions below
"""

# Todo DE PUS ASSERTURI(TESTERE)
# Todo UNDO
class Bank_account:
    def __init__(self, day, money, type, description):
        self.day = day
        self.money= money
        self.type = type
        self.description = description

    def get_day(self):
        return self._day
    def set_day(self,x):
        self._day = x
    def del_day(self):
        del self._day

    def get_money(self):
        return self._money
    def set_money(self,x):
        self._money = x
    def del_money(self):
        del self._money

    def get_type(self):
        return self._type
    def set_type(self,x):
        self._type = x
    def del_type(self):
        del self._type

    def get_description(self):
        return self._description
    def set_description(self,x):
        self._description = x
    def del_description(self):
        del self._description

    day = property(get_day,set_day,del_day)
    money = property(get_money, set_money, del_money)
    type = property(get_type, set_type, del_type)
    description = property(get_description, set_description, del_description)


def generate_list(myList):
    myList.append(Bank_account(1, 25, 'out', 'pasta'))
    myList.append(Bank_account(2, 1000, 'in', 'salary'))
    myList.append(Bank_account(2, 50, 'out', 'groceries'))
    myList.append(Bank_account(3, 30, 'out', 'movie tickets'))
    myList.append(Bank_account(4, 150, 'out', 'headphones'))
    myList.append(Bank_account(4, 30, 'out', 'pizza'))
    myList.append(Bank_account(4, 70, 'out', 'phone case'))
    myList.append(Bank_account(5, 40, 'out', 'drinks'))
    myList.append(Bank_account(6, 500, 'out', 'painting'))
    myList.append(Bank_account(7, 375, 'out', 'fuel'))

def show_list(myList):
    for a in range(0,len(myList)):
        print(myList[a].day,' ',myList[a].money,' ',myList[a].type,' ',myList[a].description)

def show_list_type(myList,a):
    for b in range(0,len(myList)):
        if myList[b].type==a:
            print(myList[b].day, ' ', myList[b].money, ' ', myList[b].type, ' ', myList[b].description)

def show_list_balance(myList,day):
    sum=0
    dif=0
    for a in range(0,len(myList)):
        if int(myList[a].day)<=int(day):
            if myList[a].type=='in':
                sum=sum+int(myList[a].money)
            else:
                dif=dif-int(myList[a].money)
    result=sum+dif
    print('The balance of the account at the end of day ',day,' is ',result)

def show_list_bigger(myList,nr):
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)>int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions more expensive than the number given')

def show_list_smaller(myList,nr):
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)<int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions less expensive than the number given')

def show_list_equal(myList,nr):
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)==int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions as expensive than the number given')

def add_tranz(myList,day,a,b,c):
    myList.append(Bank_account(day,a,b,c))
    print('tranzaction added succesfully')

def insert_tranz(myList,day,a,b,c):
    myList.append(Bank_account(day, a, b, c))
    print('tranzaction inserted succesfully')

def remove_tranz_day(myList,day):
    contor=0
    a=0
    while a<len(myList):
        if int(myList[a].day)==day:
            del myList[a]
            contor=contor+1
            a=a-1
        a=a+1
    if contor==0:
        print('There are no tranzactions in the day you specified')

def remove_type(myList,type):
    a=0
    while a<len(myList):
        if myList[a].type==type:
            myList.pop(a)
            a=a-1
        a=a+1

def remove_tranz_multiple_days(myList,start,end):
    a=0
    while a<len(myList):
        if int(myList[a].day)>=start and int(myList[a].day)<=end:
            myList.pop(a)
            a=a-1
        a=a+1

def replace(myList,day,type,description,money):
    money=int(money)
    for a in range(0,len(myList)):
        if int(myList[a].day)==int(day) and myList[a].type==type and myList[a].description==description:
            myList[a].money=money

def sum(myList,type):
    sum=0
    for a in range(0,len(myList)):
        if myList[a].type==type:
            sum=sum+int(myList[a].money)
    print('the sum of all ',type,' tranzactions is ',sum)

def max_type(myList,type,day):
    day=int(day)
    maxx=0
    for a in range(0,len(myList)):
        if int(myList[a].day)==day and int(myList[a].money)>maxx and myList[a].type==type:
            maxx=int(myList[a].money)
    if maxx==0:
        print('there are no',type,'tranzactions in the day specified')
    else:
        print('the max',type,'tranzaction on day',day,'is',maxx)

def filter_type(myList,type):
    propList = []
    a=0
    while a < len(myList):
        if myList[a].type==type:
            propList.append(Bank_account(myList[a].day,myList[a].money,myList[a].type,myList[a].description))
        a = a + 1
    show_list(propList)

def filter_type_amount(myList,type,amount):
    propList = []
    a=0
    while a < len(myList):
        if myList[a].type==type and int(myList[a].money)<int(amount):
            propList.append(Bank_account(myList[a].day,myList[a].money,myList[a].type,myList[a].description))
        a = a + 1
    show_list(propList)

"""
  Write the command-driven UI below
"""


Run = True
def start():
    current_day=8
    myList = []
    generate_list(myList)
    global Run
    while Run == True:
        command = input("prompt> ")
        tokens = command.split(" ", maxsplit=6)
        command_word = tokens[0]
        if command_word == "close":
            Run=False
        elif command_word=='add':
            if len(tokens)!=4:
                raise ValueError('there must be 4 inputs')
            a=tokens[1]
            b=tokens[2]
            c=tokens[3]
            if a.isnumeric()==False or int(a)<0:
                raise ValueError('second input must be a positive number')
            if b!='out' and b!='in':
                raise ValueError('third input must be either in or out, the type of tranzaction')
            if c.isalpha()==False:
                raise ValueError('description must contain words describing the tranzaction')
            add_tranz(myList,current_day,a,b,c)
        elif command_word=='list' and len(tokens)==1:
            show_list(myList)
        elif command_word=='insert':
            if len(tokens)!=5:
                raise ValueError('there must be 5 inputs')
            a=tokens[1]
            b=tokens[2]
            c=tokens[3]
            d=tokens[4]
            if a.isnumeric()==False or int(a)<0:
                raise ValueError('second input must be a positive number')
            if b.isnumeric()==False or int(b)<0:
                raise ValueError('third input must be a positive number')
            if c!='out' and c!='in':
                raise ValueError('forth input must be either in or out, the type of tranzaction')
            if d.isalpha()==False:
                raise ValueError('description must contain words describing the tranzaction')
            insert_tranz(myList,a,b,c,d)
        elif command_word=='list' and len(tokens)==2:
            a=tokens[1]
            if a != 'out' and a != 'in':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            show_list_type(myList,a)
        elif command_word == 'list' and len(tokens) == 3:
            a=tokens[1]
            b = tokens[2]
            if b.isnumeric() == False or int(b) < 0:
                raise ValueError('third input must be a positive number')
            if a=='balance':
                show_list_balance(myList,b)
            elif a=='>':
                show_list_bigger(myList,b)
            elif a=='<':
                show_list_smaller(myList,b)
            elif a=='=':
                show_list_equal(myList,b)
            else:
                raise ValueError('the second input is incorrect, the correct options for the input are: balance,>,<,=')
        elif command_word == 'remove' and len(tokens)==2:
            a=tokens[1]
            if a.isnumeric()==True and int(a)>0:
                a=int(a)
                remove_tranz_day(myList,a)
            elif a.isalpha()==True:
                if a!='in' and a!='out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                remove_type(myList,a)
            else:
                raise ValueError('second input is incorrect, the correct options for the input are either a positive number or:in/out')
        elif command_word == 'remove' and len(tokens)==4:
            a = tokens[1]
            b = tokens[2]
            c = tokens[3]
            if a.isnumeric()==False or int(a)<0:
                raise ValueError('second input must be a positive number')
            if b!='to':
                raise ValueError('third input must be the word "to" ')
            if c.isnumeric() == False or int(c) < 0:
                raise ValueError('forth input must be a positive number')
            a=int(a)
            c=int(c)
            remove_tranz_multiple_days(myList,a,c)
        elif command_word == 'replace':
            if len(tokens)!=6:
                raise ValueError('there must be 6 inputs')
            a = tokens[1]
            b = tokens[2]
            c = tokens[3]
            d = tokens[4]
            e = tokens[5]
            if a.isnumeric()==False or int(a)<0:
                raise ValueError('second input must be a positive number')
            if b != 'in' and b != 'out':
                raise ValueError('third input must be either in or out, the type of tranzaction')
            if c.isalpha()==False:
                raise ValueError('forth input must be a string, the description of the tranzaction')
            if d!='with':
                raise ValueError('incorrect input, fifth input must be the word with')
            if e.isnumeric()==False or int(e)<0:
                raise ValueError('sixth input must be a number, representing the value of the tranzaction')
            replace(myList,a,b,c,e)
        elif command_word == 'sum':
            if len(tokens)!=2:
                raise ValueError('there must be 2 inputs')
            a = tokens[1]
            if a != 'in' and a != 'out':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            sum(myList,a)
        elif command_word == 'max':
            if len(tokens)!=3:
                raise ValueError('there must be 3 inputs')
            a = tokens[1]
            b = tokens[2]
            if a != 'in' and a != 'out':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            if b.isnumeric() == False or int(b) < 0:
                raise ValueError('third input must be a positive number')
            max_type(myList,a,b)
        elif command_word == 'filter':
            if len(tokens)==2:
                a=tokens[1]
                if a != 'in' and a != 'out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                filter_type(myList,a)
            elif len(tokens)==3:
                a = tokens[1]
                b = tokens[2]
                if a != 'in' and a != 'out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                if b.isnumeric() == False or int(b) < 0:
                    raise ValueError('third input must be a positive number')
                filter_type_amount(myList,a,b)
            else:
                raise ValueError('there must be 2 or 3 inputs')
        else:
            raise ValueError('incorrect input')

start()