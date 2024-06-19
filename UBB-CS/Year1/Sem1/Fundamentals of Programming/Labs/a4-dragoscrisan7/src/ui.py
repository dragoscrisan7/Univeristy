"""
  User interface module
"""
from functions import print_insert,print_add,tests,get_stack_len,generate_list,show_list,show_list_type,show_list_balance,show_list_bigger,show_list_smaller,show_list_equal
from functions import remove_tranz_day,remove_type,remove_tranz_multiple_days,replace,sum,max_type,filter_type,filter_type_amount,undo

def user_interface():
    print('Enter the command after the word "prompt>",type "help" for commands options ')

def help():
    print('ADD TRANZACTIONS:')
    print('add <value> <type> <description>, to add a tranzaction on the current day')
    print('insert <day> <value> <type> <description>, to add a tranzaction on the specified day')
    print('\n MODIFY TRANZACTIONS:')
    print('remove <day>, to remove all tranzactions from the specified day\n remove <start day> to <end day>, to remove all tranzactions from starting from the first specified day up to the second specified day \n remove <type>, to remove all tranzactions matching the specified type\n replace <day> <type> <description> with <value>, to change the amount of money in a tranzaction with the specified details')
    print('\n DISPLAY TRANZACTIONS HAVING DIFFERENT PROPERTIES')
    print('list, to display all tranzactions \n list <type>, to display all tranzactions that match the specified type of tranzaction')
    print('list [ < | = | > ] <value>, to display all tranzactions that respect the mathematical equation of beeing smaller, higher or equal with the specified amount of money')
    print('list balance <day>, to display the balance of the bank account up to the specified day')
    print('\n OBTAIN DIFFERENT CHARACTERISTICS OF THE TRANZACTIONS')
    print('sum <type>, to display the sum of all tranzactions matching the specified type of tranzactions')
    print('max <type> <day>, to dispaly the biggest tranzaction of the specified day')
    print('\n FILTER')
    print('filter <type>, to create another list of tranzactions containing only the tranzactions matching the specified type of tranzaction')
    print('filter <type> <value>, to create another list of tranzactions containing only the tranzactions matching the specified type of tranzaction and a smaller amount of money than specified')

tests()
Run = True
def start():
    myList = []
    generate_list(myList)
    stack_list = [myList.copy()]
    global Run
    user_interface()
    while Run == True:
        command = input("prompt> ")
        tokens = command.split(" ", maxsplit=6)
        command_word = tokens[0]
        if command_word == "close":
            Run=False
        elif command_word == 'help':
            help()
        elif command_word=='add':
            print_add(myList,tokens,stack_list)
        elif command_word=='list' and len(tokens)==1:
            stack_list_len=stack_list[get_stack_len(stack_list)]
            show_list(stack_list_len)
        elif command_word=='insert':
            print_insert(myList,tokens,stack_list)
        elif command_word=='list' and len(tokens)==2:
            a=tokens[1]
            if a != 'out' and a != 'in':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            stack_list_len = stack_list[get_stack_len(stack_list)]
            show_list_type(stack_list_len,a)
        elif command_word == 'list' and len(tokens) == 3:
            a=tokens[1]
            b = tokens[2]
            if b.isnumeric() == False or int(b) < 0:
                raise ValueError('third input must be a positive number')
            if a=='balance':
                stack_list_len = stack_list[get_stack_len(stack_list)]
                show_list_balance(stack_list_len,b)
            elif a=='>':
                stack_list_len = stack_list[get_stack_len(stack_list)]
                show_list_bigger(stack_list_len,b)
            elif a=='<':
                stack_list_len = stack_list[get_stack_len(stack_list)]
                show_list_smaller(stack_list_len,b)
            elif a=='=':
                stack_list_len = stack_list[get_stack_len(stack_list)]
                show_list_equal(stack_list_len,b)
            else:
                raise ValueError('the second input is incorrect, the correct options for the input are: balance,>,<,=')
        elif command_word == 'remove' and len(tokens)==2:
            a=tokens[1]
            if a.isnumeric()==True and int(a)>0:
                a=int(a)
                remove_tranz_day(myList,a)
                print('All tranzactions from the specified day were removed')
                aux_list = myList.copy()
                stack_list.append(aux_list)
            elif a.isalpha()==True:
                if a!='in' and a!='out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                remove_type(myList,a)
                print('All tranzactions with specified type were')
                aux_list = myList.copy()
                stack_list.append(aux_list)
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
            print('All tranzactions from the starting day to the ending day were removed')
            aux_list = myList.copy()
            stack_list.append(aux_list)
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
            aux_list = myList.copy()
            stack_list.append(aux_list)
        elif command_word == 'sum':
            if len(tokens)!=2:
                raise ValueError('there must be 2 inputs')
            a = tokens[1]
            if a != 'in' and a != 'out':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            print('the sum of all', a, 'tranzactions is', sum(myList,a))
        elif command_word == 'max':
            if len(tokens)!=3:
                raise ValueError('there must be 3 inputs')
            a = tokens[1]
            b = tokens[2]
            if a != 'in' and a != 'out':
                raise ValueError('second input must be either in or out, the type of tranzaction')
            if b.isnumeric() == False or int(b) < 0:
                raise ValueError('third input must be a positive number')
            maxx=max_type(myList,a,b)
            if maxx == 0:
                print('there are no', a, 'tranzactions in the day specified')
            else:
                print('the max', a, 'tranzaction on day', b, 'is', maxx)
        elif command_word == 'filter':
            if len(tokens)==2:
                a=tokens[1]
                if a != 'in' and a != 'out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                show_list(filter_type(myList,a))
            elif len(tokens)==3:
                a = tokens[1]
                b = tokens[2]
                if a != 'in' and a != 'out':
                    raise ValueError('second input must be either in or out, the type of tranzaction')
                if b.isnumeric() == False or int(b) < 0:
                    raise ValueError('third input must be a positive number')
                show_list(filter_type_amount(myList,a,b))
            else:
                raise ValueError('there must be 2 or 3 inputs')
        elif command_word=='undo':
            if len(stack_list)!=1:
                undo(stack_list)
                stack_list_len = stack_list[get_stack_len(stack_list)]
                myList=stack_list_len.copy()
            else:
                print('You are already at the starting point')
        else:
            raise ValueError('incorrect input')

