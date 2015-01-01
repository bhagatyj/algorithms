#! /usr/bin/python
'''
Creates Heap Data structure
'''
import utils
import sys
import time

class Heap:
	'''
	This is a minHeap. It satisfies the rule that parent node's
	key value is always less than child's key value.
	'''
	def __init__(this):
		this.myList = list()
		this.myList.append("null")
		this.size = 0

	def less(this, idx1, idx2):
		'''
		Returns True if key-of-item-of-idx1 < key-of-item-of-idx2
		'''
		item1 = this.myList[idx1]
		item2 = this.myList[idx2]
		if (item1.compareKeys(item2) < 0):
			return True
		else:
			return False

	def more(this, idx1, idx2):
		'''
		Returns True if key-of-item-of-idx1 > key-of-item-of-idx2
		'''
		item1 = this.myList[idx1]
		item2 = this.myList[idx2]
		if (item1.compareKeys(item2) > 0):
			return True
		else:
			return False

	def swap(this, idx1, idx2):
		temp = this.myList[idx1]
		this.myList[idx1] = this.myList[idx2]
		this.myList[idx2] = temp

	def swim(this, index):
		while ((index > 1) and (this.less(index, index/2))):
			this.swap(index, index/2)
			index = index/2

	def sink(this, index):
		while (2*index < this.size):
			#this.printList()
			if (2*index+1 > this.size):
				# One child only.
				# Check if node is larger than child. If so, swap.
				if (this.less(2*index, index)):
					this.swap(index, 2*index)
					index = 2*index
				else:
					return
			else:
				# Find the smaller of two children.
				# If node is larger than that child, swap it.
				if this.less(2*index, 2*index+1):
					if this.less(2*index, index):
						this.swap(index, 2*index)
						index = 2*index
					else:
						return
				else:
					if this.less(2*index+1, index):
						this.swap(2*index+1, index)
						index = 2*index + 1
					else:
						return

	def insertNode(this, item):
		this.size = this.size + 1
		this.myList.append(item)
		this.swim(this.size)

	def delHead(this):
		if (this.size == 0):
			raise IndexError

		if (this.size == 1):
			this.size = 0;
			return this.myList.pop()

		head = this.myList[1]
		this.myList[1] = this.myList.pop()
		this.size -= 1
		this.sink(1)
		return head

	def __iter__(this):
		return this

	def next(this):
		if (this.size == 0):
			raise StopIteration
		return this.delHead()

	def printList(this):
		print "Size:%d List: %s" % (this.size, this.myList[1:size+1])
