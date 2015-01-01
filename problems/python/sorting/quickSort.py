#! /usr/bin/python

import utils
import sys
import logging
import sortClass

class QuickSort (sortClass.SortClass):
	@staticmethod
	def basicSort(myList):
		# If the length is one or zero
		# Nothing more to do.
		# List is already sorted.
		size = len(myList)
		if size <= 1:
			return myList;

		# Simplest implementation generally choses first element
		# as pivot (not efficient for pre-sorted lists)
		# Choose mid point as pivot (helps in pre-sorted lists)
		# Note: Python 3 returns float on integer division.
		# Would cause a problem if size is odd.
		median = size/2 
		pivot = myList.pop(median);

		# No conservation of space/memory.
		# Create two lists
		# listLessEqual -> holds elements that are <= pivot
		# listMore -> holds elements that are > pivot
		listLessEqual = []
		listMore = []

		# Go through the main list and copy elements
		# over to the other two lists.
		for x in myList:
			if (x.compareKeys(pivot) != 1):
				listLessEqual.append(x);
			else:
				listMore.append(x);

		# Recursively sort the other two lists
		listLessEqual = QuickSort.basicSort(listLessEqual);
		listMore = QuickSort.basicSort(listMore);

		# Combine the three lists. 
		'''
		Common mistake. It is important to add back the pivot element.
		'''
		listLessEqual.append(pivot)
		final = listLessEqual + listMore;
		return final
		#end

if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [5,100]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		myList = QuickSort.inplaceQuickSort(myList)
		print myList