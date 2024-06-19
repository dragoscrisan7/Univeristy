def tester(list):
    """
    function for testing if the strings of the list respect all requirments
    :param list: the list of the string
    :return: True if they respct, False if they dont
    """
    cont = 0
    """
    counts the string of the list that we are currently at
    """
    for elem in list:
        cont += 1
        if cont % 2 == 0:
            if not "***" in elem:
                return False
        #checks if the string has 3 ***
        middle = int(len(elem))/2
        middle = int(middle)
        if elem[0]!='%' or elem[len(elem)-1]!='%' or elem[middle]!='%':
            return False
        #checks if the string has % where it should
        for c in elem:
            if c.islower():
                return False
        #checks if the string has any lowercase letters
    return True

def main():
    list=["%A%B%", "%GHGAY%***A%", "%%%"]
    if tester(list) == True:
        print("da")

main()