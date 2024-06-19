"""
  Program functionalities module
"""


class Bank_account:
    """
    the class containing all the information about a tranzaction, meaning the day, money, type and description of it
    """
    def __init__(self, day, money, type, description):
        """

        :param day: must be a positive number
        :param money: must be a positive number
        :param type: must be a string, either the word 'in' or 'out',meaning the type of tranzaction
        :param description: must be a string
        """
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


def class_tupple(a):
    return (a.day, a.money, a.type, a.description)


def transform(myList):
    """
    transforms the list of classes into a tuple so it can be verified in tests
    :param myList:
    :return:
    """
    list = []
    for a in range(0,len(myList)):
        list.append(class_tupple(myList[a]))
    return list


def generate_list(myList):
    """
    function that creates the first 10 elements of the list
    the list is a list of classes, each one representing a tranzaction
    :param myList:
    :return:
    """
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


def get_stack_len(stack_tranzactions_list):
    """
    delete the last list of tranzactions
    :param stack_tranzactions_list:
    :return:
    """
    if not stack_tranzactions_list:
        return 0
    return len(stack_tranzactions_list) - 1


def show_list(myList):
    """
    display all objects in the classes stored in the list
    :param myList:
    :return:
    """
    for a in range(0,len(myList)):
        print(myList[a].day,' ',myList[a].money,' ',myList[a].type,' ',myList[a].description)


def show_list_type(myList,a):
    """
    display all objects in the classes stored in the list where the type matches the param 'a'
    :param myList:
    :param a: must be 'in' or 'out'
    :return:
    """
    for b in range(0,len(myList)):
        if myList[b].type==a:
            print(myList[b].day, ' ', myList[b].money, ' ', myList[b].type, ' ', myList[b].description)


def show_list_balance(myList,day):
    """
    displays all objects in the classes stored in the list where the day matches the param 'a'
    :param myList:
    :param day: must be positive number
    :return:
    """
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
    """
    display all objects in the classes stored in the list where the amount of money from the tranzaction is higher than param 'nr'
    :param myList:
    :param nr: must be positive number
    :return:
    """
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)>int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions more expensive than the number given')


def show_list_smaller(myList,nr):
    """
    display all objects in the classes stored in the list where the amount of money from the tranzaction is smaller than param 'nr'
    :param myList:
    :param nr:
    :return:
    """
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)<int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions less expensive than the number given')


def show_list_equal(myList,nr):
    """
    display all objects in the classes stored in the list where the amount of money from the tranzaction is equal than param 'nr'
    :param myList:
    :param nr:
    :return:
    """
    contor=0
    for a in range(0,len(myList)):
        if int(myList[a].money)==int(nr):
            contor=contor+1
            print(myList[a].day, ' ', myList[a].money, ' ', myList[a].type, ' ', myList[a].description)
    if contor==0:
        print('There are no tranzactions as expensive than the number given')


def add_tranz(myList,day,a,b,c):
    """
    adds a new tranzaction to the list, on the current day
    :param myList:
    :param day: must be positive number, the current day
    :param a: must be positive number, the money amount
    :param b: must be string, 'in' or 'out'
    :param c: must be string, the description of the tranzaction
    :return:
    """
    myList.append(Bank_account(day,a,b,c))


def print_add(myList,tokens,stack_list):
    current_day = 8
    if len(tokens) != 4:
        raise ValueError('there must be 4 inputs')
    a = tokens[1]
    b = tokens[2]
    c = tokens[3]
    if a.isnumeric() == False or int(a) < 0:
        raise ValueError('second input must be a positive number')
    if b != 'out' and b != 'in':
        raise ValueError('third input must be either in or out, the type of tranzaction')
    if c.isalpha() == False:
        raise ValueError('description must contain words describing the tranzaction')
    add_tranz(myList, current_day, a, b, c)
    print('tranzaction added succesfully')
    aux_list = myList.copy()
    stack_list.append(aux_list)


def insert_tranz(myList,day,a,b,c):
    """
    adds a tranzaction to the list, on the day specified
    :param myList:
    :param day: must be positive number, the current day
    :param a: must be positive number, the money amount
    :param b: must be string, 'in' or 'out'
    :param c: must be string, the description of the tranzaction
    :return:
    """
    myList.append(Bank_account(day, a, b, c))


def print_insert(myList,tokens,stack_list):
    if len(tokens) != 5:
        raise ValueError('there must be 5 inputs')
    a = tokens[1]
    b = tokens[2]
    c = tokens[3]
    d = tokens[4]
    if a.isnumeric() == False or int(a) < 0:
        raise ValueError('second input must be a positive number')
    if b.isnumeric() == False or int(b) < 0:
        raise ValueError('third input must be a positive number')
    if c != 'out' and c != 'in':
        raise ValueError('forth input must be either in or out, the type of tranzaction')
    if d.isalpha() == False:
        raise ValueError('description must contain words describing the tranzaction')
    insert_tranz(myList, a, b, c, d)
    print('tranzaction inserted succesfully')
    aux_list = myList.copy()
    stack_list.append(aux_list)


def remove_tranz_day(myList,day):
    """
    removing all tranzactions from the specified day from the list
    :param myList:
    :param day: must be positive number, the specified day
    :return:
    """
    a=0
    if len(myList)==0:
        raise ValueError('List no longer has objects to be removed')
    while a<len(myList):
        if int(myList[a].day)==day:
            del myList[a]
            a=a-1
        a=a+1


def remove_type(myList,type):
    """
    removing all tranzactions with the specified type from the list
    :param myList:
    :param type: must be string, 'in' or 'out'
    :return:
    """
    a=0
    assert len(myList) != 0, 'List no longer has objects to be removed'
    while a<len(myList):
        if myList[a].type==type:
            myList.pop(a)
            a=a-1
        a=a+1


def remove_tranz_multiple_days(myList,start,end):
    """
    removing all tranzactions from day 'start' to day 'end' and all the days inbetween from the list
    :param myList:
    :param start: must be positive number, the starting day
    :param end: must be positive number, higher than start, the ending day
    :return:
    """
    a=0
    assert len(myList) != 0, 'List no longer has objects to be removed'
    assert start<end,'Starting day must be a smaller number than ending day'
    while a<len(myList):
        if int(myList[a].day)>=start and int(myList[a].day)<=end:
            myList.pop(a)
            a=a-1
        a=a+1


def replace(myList,day,type,description,money):
    """
    replaces the amount of money in a tranzaction where the day, type and description matches the specified variables
    :param myList:
    :param day: must be positive number
    :param type: must be string, 'in' or 'out'
    :param description: must be string, the description of the tranzaction
    :param money: must be positive number, the money amount
    :return:
    """
    contor=0
    money=int(money)
    for a in range(0,len(myList)):
        if int(myList[a].day)==int(day) and myList[a].type==type and myList[a].description==description:
            myList[a].money=money
            contor=1
    if contor == 0:
        raise ValueError('The tranzaction stated was not found')


def sum(myList,type):
    """
    adds all sums of money in all tranzactions where the type matches the specified type
    :param myList:
    :param type: must be string, 'in' or 'out'
    :return:
    """
    sum=0
    for a in range(0,len(myList)):
        if myList[a].type==type:
            sum=sum+int(myList[a].money)
    return sum

def max_type(myList,type,day):
    """
    displays the biggest tranzaction from the specified day with the specified type:'in' or 'out'
    :param myList:
    :param type: must be string, 'in' or 'out'
    :param day: must be positive number, the specified day
    :return:
    """
    day=int(day)
    maxx=0
    for a in range(0,len(myList)):
        if int(myList[a].day)==day and int(myList[a].money)>maxx and myList[a].type==type:
            maxx=int(myList[a].money)
    return maxx

def filter_type(myList,type):
    """
    creates a list made out of all tranzactions with the specified type
    :param myList:
    :param type: must be string, 'in' or 'out'
    :return:
    """
    propList = []
    a=0
    while a < len(myList):
        if myList[a].type==type:
            propList.append(Bank_account(myList[a].day,myList[a].money,myList[a].type,myList[a].description))
        a = a + 1
    return propList

def filter_type_amount(myList,type,amount):
    """
    creates a list made out of all tranzactions with the specified type that have lower amounts of money than the specified amount
    :param myList:
    :param type: must be string, 'in' or 'out'
    :param amount: must be positive number, the money amount
    :return:
    """
    propList = []
    a=0
    while a < len(myList):
        if myList[a].type==type and int(myList[a].money)<int(amount):
            propList.append(Bank_account(myList[a].day,myList[a].money,myList[a].type,myList[a].description))
        a = a + 1
    return propList

def undo(stack_tranzactions_list):
    if stack_tranzactions_list:
        stack_tranzactions_list.pop()
    else:
        print("Nothing to undo!")
        print()

def test_add(testList):
    add_tranz(testList,8,100,'out','pizza')
    assert transform(testList)==[(8,100,'out','pizza')]

def test_insert(testList):
    insert_tranz(testList,9,1000,'in','salary')
    assert transform(testList)==[(8,100,'out','pizza'),(9,1000,'in','salary')]

def test_remove_day(testList):
    remove_tranz_day(testList,8)
    assert transform(testList)==[(9,1000,'in','salary')]

def test_remove_type(testList):
    add_tranz(testList, 9, 100, 'out', 'pizza')
    add_tranz(testList, 10, 100, 'out', 'pizza')
    remove_type(testList,'out')
    assert transform(testList)==[(9,1000,'in','salary')]

def test_remove_multiple_days(testList):
    add_tranz(testList, 4, 100, 'out', 'pizza')
    add_tranz(testList, 5, 100, 'out', 'pizza')
    add_tranz(testList, 6, 100, 'out', 'pizza')
    remove_tranz_multiple_days(testList,4,6)
    assert transform(testList)==[(9,1000,'in','salary')]

def test_replace(testList):
    replace(testList,4,'out','pasta',55)
    assert transform(testList) == [(9, 1000, 'in', 'salary'),(4, 100, 'out', 'pizza'),(4, 55, 'out', 'pasta')]

def test_sum(testList):
    add_tranz(testList, 4, 100, 'out', 'pizza')
    add_tranz(testList, 4, 50, 'out', 'pasta')
    assert sum(testList,'out')==150

def test_max(testList):
    assert max_type(testList,'out',4)==100

def test_filter_type(testList):
    assert transform(filter_type(testList,'in'))==[(9, 1000, 'in', 'salary')]

def test_filter_type_amount(testList):
    assert transform(filter_type_amount(testList,'out',56))==[(4, 55, 'out', 'pasta')]

def tests():
    testList = []
    test_add(testList)
    test_insert(testList)
    test_remove_day(testList)
    test_remove_type(testList)
    test_sum(testList)
    test_max(testList)
    test_replace(testList)
    test_filter_type(testList)
    test_filter_type_amount(testList)



