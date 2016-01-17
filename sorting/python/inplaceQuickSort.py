#! /usr/bin/python

import utils
import sys
import logging
import sortClass

class InplaceQuickSort (sortClass.SortClass):


	@staticmethod
	def conquer(myList, start, end):
		'''
		Partitions the list into two (re-arranges inplace)
		Recursively calls itself for the two lists.
		'''
		if (start < end):
			splitPoint = InplaceQuickSort.divide(myList, start, end);
			InplaceQuickSort.conquer(myList, start, splitPoint-1);
			InplaceQuickSort.conquer(myList, splitPoint+1, end);
		return myList

	@staticmethod
	def divide(myList, start, end):
		pivot = myList[start]
		left = start + 1
		right = end
		done = False

		logging.debug("I will be sorting this list %s", myList[start:end+1])
		while (not done):
			sleft = left
			sright = right

			# Move left as much right as you can
			while ((left <= right) and (myList[left].compareKeys(pivot) <= 0)):
				left = left + 1;
			logging.debug("left moved from %d to %d" % (sleft,left))

			# Move right as much left as you can
			'''
			Note: The comparison "myList[right] > pivot" can be changed to
			"myList[right] >= pivot". The program will still complete
			sorting after all recursions are done.
			'''
			while ((right >= left) and (myList[right].compareKeys(pivot) > 0)):
				right = right -1;
			logging.debug("right moved from %d to %d" %(sright, right))

			# We are done if right is left of left
			if (right < left):
				done = True;
			else:
				# We are stuck at a place where left and right elements
				# have to be swapped so that they can move further. 
				# Perform the swap.
				logging.debug("Swapping [%d] and [%d]" %(left, right))
				temp = myList[left]
				myList[left] = myList[right]
				myList[right] = temp
			# Now that we have swapped, go back and continue moving the
			# left and right indices

		# The left side of the list contains elements less than pivot.
		# The right side of the list contains elements more than pivot.
		# Time to move the pivot.
		# Elements to the right-of-right are all greater than the pivot.
		# Right is currently pointing to an element that is <= pivot.
		# So, swap the pivot with right.
		logging.debug( "Pivot-Swap. Swapping [%d] and [%d]" \
			%(start, right))
		temp = myList[start]
		myList[start] = myList[right]
		myList[right] = temp

		logging.debug("I am done with sorting the list %d %s", right, \
			myList[start:end+1])
		return right

	@staticmethod
	def basicSort(myList):
		# logging.basicConfig(format='%(asctime)s %(message)s', 
		# 	datefmt='%m/%d/%Y %I:%M:%S %p', 
		# 	level = logging.DEBUG)
			#filename = "output.log")
		return InplaceQuickSort.conquer(myList, 0, len(myList)-1)
