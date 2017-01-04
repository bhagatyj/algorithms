import random

"""
Problem Definition:
    Get the m largest numbers in a huge list of N numbers.
    Assumption: m << N
    m is much smaller than N.

Solution:
    Pick the first m numbers and make a small list.
    Keep the small list sorted.
    Walk through the big list and keep comparing the lowest value
    in the small list. If you find a value that is larger, swap that
    with the smallest value in the small list. Sort the small list.
    Continue walking..

Disadvantages:
    Worst performance in an already sorted list. As each new element
    that you pick as you walk through the big list is guaranteed to
    be larger than the small list. 
"""


def getMaxN( input, n ):
    maxN = input[0:n]
    count = len(input)
    i = n
    while ( i < count ):
        maxN.sort()
        if ( input[i] > maxN[0] ):
            maxN[0] = input[i]
            maxN.sort()
        i = i + 1
    return maxN


def test():
    maxNum = 1000
    maxShuffle = 200
    numberList = list( range(1, maxNum) )
    i = 0
    while i < maxShuffle:
        i = i + 1
        index = random.choice( range( 0, maxNum-1 ) )
        tmp = numberList[index]
        numberList[index] = numberList[0]
        numberList[0] = tmp

    maxN = getMaxN( numberList, 5)
    print maxN

if __name__ == "__main__":
    test()

