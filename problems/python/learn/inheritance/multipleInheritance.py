class myList(object):
    def __init__(self):
        self.list = list()

    def add(self, x):
        print "myList::add", x
        self.list.append(x)
        print "Added successfully\n"

    def printItems(self):
        for i in self.list:
            print i,
        print

class myFloatList(myList):
    def __init__(self):
        super(myFloatList, self).__init__()

    def add(self, x):
        print "myFloatList::add", x
        if isinstance(x, float):
            print x, " is a float"
            super(myFloatList, self).add(x)
        else:
            print "Not a float"


class myPositiveList(myList):
    def __init__(self):
        super(myPositiveList, self).__init__()

    def add(self, x):
        print "myPositiveList::add", x
        if (x > 0):
            super(myPositiveList, self).add(x)
        else:
            print "Not +ve"

    def addBypass(self, x):
        super(myPositiveList, self).add(x)

class myPositiveFloatList( myPositiveList, myFloatList ):
    pass

class myFloatPositiveList( myFloatList, myPositiveList):
    pass

if __name__ == "__main__":
    pf = myPositiveFloatList()
    # Diamond inheritance is a tricky problem.
    # The add method is implemented in both parent classes of the
    # diamond structure. The grandparent add will be invoked only
    # if both parents call the super.
    # This ensures that only positive floats get added to the list
    pf.add(2.3456) # will get added
    pf.add(2) # will not get added
    pf.add(-0.3) # will not get added
    pf.add(0) # will not get added
    pf.add(3.45) # will get added

    # The bypass add is implemented in only one parent. Hence it is
    # enough if just that implementation invokes super and the base
    # add will get invoked.
    pf.addBypass(45) # will get added - implemented only in the +ve class

    pf.printItems()

    print myPositiveFloatList.__mro__
    print myFloatPositiveList.__mro__
    # The MRO defines the order and resolution for methods. It depends
    # on the order specified in the inheritance
