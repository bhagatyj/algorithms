#! /usr/bin/python

import utils
import sys
import logging
import sortClass
import time
import math

class InplaceMidPivotQuickSort (sortClass.SortClass):


	@staticmethod
	def conquer(myList, start, end):
		'''
		Partitions the list into two (re-arranges inplace)
		Recursively calls itself for the two lists.
		'''
		if (start < end):
			splitPoint = InplaceMidPivotQuickSort.divide(myList, start, end);
			InplaceMidPivotQuickSort.conquer(myList, start, splitPoint-1);
			InplaceMidPivotQuickSort.conquer(myList, splitPoint+1, end);
		return myList

	@staticmethod
	def swap(myList, idx1, idx2):
		temp = myList[idx1]
		myList[idx1] = myList[idx2]
		myList[idx2] = temp

	@staticmethod
	def divide(myList, start, end):
		midPoint = int(math.floor((start + end) /2.0))
		logging.debug("I will be sorting this list %s start:%d end:%d midPoint:%d", \
			myList[start:end+1], start, end, midPoint)
		pivot = myList[midPoint]
		myList.pop(midPoint)
		delim = start
		for index in range(start, end):
			logging.debug("Compare %s and %s" %(myList[index], pivot))
			if (myList[index].compareKeys(pivot) < 0):
				InplaceMidPivotQuickSort.swap(myList, delim, index)
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
		return InplaceMidPivotQuickSort.conquer(myList, 0, len(myList)-1)


if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [500]
	for size in sizes:
		myList = utils.createInputArray(size)
		print myList
		InplaceMidPivotQuickSort.basicSort(myList)
		print myList