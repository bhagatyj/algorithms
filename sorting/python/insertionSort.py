#! /usr/bin/python

import utils
import sys
import sortClass

class InsertionSort(sortClass.SortClass):
	@staticmethod
	def findSlot(myList, value, max):
		for i in range(max):
			if (value < myList[i]):
				return i
		return max-1

	@staticmethod
	def basicSort(myList):
		# If the length is one or zero
		# Nothing more to do.
		# List is already sorted.
		size = len(myList)
		if size <= 1:
			return myList;
		for i in range(1,size):
			if (myList[i].compareKeys(myList[i-1]) < 0):
				value = myList.pop(i)
				slot = InsertionSort.findSlot(myList, value, i)
				myList.insert(slot, value)
		return myList
		#end



if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [5, 100]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		InsertionSort.basicSort(myList)
		print myList