#! /usr/bin/python

import logging
import utils
import sys
import sortClass
from utils import NKItem
import bubbleSort

class OptBubbleSort(bubbleSort.BubbleSort):

	@staticmethod
	def basicSort(myList):
		# If the length is one or zero
		# Nothing more to do.
		# List is already sorted.
		if len(myList) <= 1:
			return myList;

		size = len(myList)
		lastSwapped = size-1;
		for i in range(size):
			for j in range(size-1):
				if (myList[j].compareKeys(myList[j+1]) > 0):
					OptBubbleSort.swap(myList, j, j+1)
					lastSwapped = j
		return myList
