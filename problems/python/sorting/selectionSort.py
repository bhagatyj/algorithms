#! /usr/bin/python

import utils
import sys
import sortClass

class SelectionSort(sortClass.SortClass):
	@staticmethod
	def swap(myList, x, y):
		temp = myList[x]
		myList[x] = myList[y]
		myList[y] = temp

	@staticmethod
	def basicSort(myList):

		# If the length is one or zero
		# Nothing more to do.
		# List is already sorted.
		size = len(myList)
		if size <= 1:
			return myList;

		# Run through each position and select the right element to
		# place in that position.
		for position in range(size):
			minValue = myList[position]
			minPosition = position
			for idx in range(position, size):
				if (myList[idx].compareKeys(myList[position]) < 0):
					minValue = myList[idx]
					minPosition = idx
			SelectionSort.swap(myList, position, minPosition)
		return myList
		#end

if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [5, 100]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		SelectionSort.basicSort(myList)
		print myList