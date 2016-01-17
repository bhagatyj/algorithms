#! /usr/bin/python
import random
import time
import sys

class SortClass:
	def __init__(this):
		this.averageSortTime = 0
		this.averageUnsortTime = 0

	def setTime(this, uTime, sTime):
		this.unsortedTime = uTime
		this.sortedTime = sTime

	def sortList(this, myList):
		return this.basicSort(myList)
