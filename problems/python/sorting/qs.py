#! /usr/bin/python
# quick sort
import time
def partition(myList, start, end):
    print "Called. start:%d end:%d List:" %(start, end)
    print myList[start:end+1]
    pivot = myList[start]
    left = start+1
    # Start outside the area to be partitioned
    right = end
    done = False
    while not done:
        sleft = left
        sright = right
        while left <= right and myList[left] <= pivot:
            left = left + 1
        #print "left moved from %d to %d" % (sleft,left)
        while myList[right] > pivot and right >= left:
            right = right -1
        #print "right moved from %d to %d" %(sright, right)
        if right < left:
            done= True
        else:
            # swap places
            temp=myList[left]
            myList[left]=myList[right]
            myList[right]=temp
    # swap start with myList[right]
    temp=myList[start]
    myList[start]=myList[right]
    myList[right]=temp
    print "Result of my sort pivot-position:%d List:" %right
    print myList[start:end+1]
    return right


def quicksort(myList, start, end):
    if start < end:
        # partition the list
        split = partition(myList, start, end)
        # sort both halves
        print "start:%d split:%d end:%d" %(start, split, end)
        quicksort(myList, start, split-1)
        quicksort(myList, split+1, end)
    return myList



def main():
    myList = [6, 2, 6, 1, 5245, 1, 2, 45, 23, 423, 4214, 412, 3, 6]
    #[7,2,5,1,29,1,6,4,19,11]
    #myList = [1,2,1,2]
    sortedList = quicksort(myList,0,len(myList)-1)
    print(sortedList)

main()
