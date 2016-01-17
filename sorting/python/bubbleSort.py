#! /usr/bin/python

import logging
import utils
import sys
import sortClass
from utils import NKItem

class BubbleSort(sortClass.SortClass):
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
		if len(myList) <= 1:
			return myList;

		size = len(myList)
		for i in range(size):
			for j in range(size-1):
				if (myList[j].compareKeys(myList[j+1]) > 0):
					BubbleSort.swap(myList, j, j+1)
		return myList

if __name__ == "__main__":
	sizes = [5, 100]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		BubbleSort.basicSort(myList)
		print myList
