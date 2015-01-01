#! /usr/bin/python

import utils
import sys
import time
import sortClass
import heap

class HeapSort(sortClass.SortClass):
	def __init__(this, myList):
		this.addList(myList)

	def __init__(this):
		pass

	def addList(this, myList):
		this.myHeap = heap.Heap()
		for x in myList:
			this.myHeap.insertNode(x)
		this.sortedList = list()

	def sortList(this, myList):
		this.addList(myList)
		for x in this.myHeap:
			this.sortedList.append(x)
		return this.sortedList

if __name__ == "__main__":
	sys.setrecursionlimit(10000)
	sizes = [5,1000]
	for size in sizes:
		myList = utils.createInputArray(size)
		h = Heap()
		for x in myList:
			h.insertNode(x)
		sortedList = list()
		for x in h:
			sortedList.append(x)
		print sortedList


