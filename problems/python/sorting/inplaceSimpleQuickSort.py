#! /usr/bin/python

import utils
import sys
import logging
import sortClass

class InplaceSimpleQuickSort (sortClass.SortClass):
	@staticmethod
	def conquer(myList, start, end):
		'''
		Partitions the list into two (re-arranges inplace)
		Recursively calls itself for the two lists.
		'''
		if (start < end):
			splitPoint = InplaceSimpleQuickSort.divide(myList, start, end);
			InplaceSimpleQuickSort.conquer(myList, start, splitPoint-1);
			InplaceSimpleQuickSort.conquer(myList, splitPoint+1, end);
		return myList

	@staticmethod
	def swap(myList, idx1, idx2):
		logging.debug("Perform swap %d,%d" %(idx1, idx2))
		temp = myList[idx1]
		myList[idx1] = myList[idx2]
		myList[idx2] = temp

	@staticmethod
	def divide(myList, start, end):
		logging.debug("I will be sorting this list %s", myList[start:end+1])
		pivot = myList[start]
		myList.pop(start)
		delim = start
		for index in range(start, end):
			logging.debug("Compare %s and %s" %(myList[index], pivot))
			if (myList[index].compareKeys(pivot) < 0):
				InplaceSimpleQuickSort.swap(myList, delim, index)
				delim += 1
		logging.debug("Completed Loop")
		myList.insert(delim, pivot)
		logging.debug("I have pivoted this list %s with pivot %s delim:%d" \
			%(myList[start:end+1], pivot, delim))
		return delim

	@staticmethod
	def basicSort(myList):
		#logging.basicConfig(format='%(asctime)s %(message)s', 
			#datefmt='%m/%d/%Y %I:%M:%S %p', 
			#level = logging.DEBUG)
			#filename = "output.log")
		return InplaceSimpleQuickSort.conquer(myList, 0, len(myList)-1)

if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [1000]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		InplaceSimpleQuickSort.basicSort(myList)
		print myList