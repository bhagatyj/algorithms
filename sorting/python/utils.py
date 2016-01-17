#! /usr/bin/python
import random
import time
import string

def createInputArray(size=1000):
	newArray = []
	for i in range(size):
		newArray.append(NKItem())
	return newArray

def mean(inputArray):
	total = 0
	for x in inputArray:
		total += x.key.value
	return (total/len(inputArray))

class Name(object):

	def __init__(this, length=6):
		charList = list()
		for _ in range(length):
			charList.append(random.choice(string.ascii_lowercase))
		this.value = ''.join(charList)

class Number(object):

	def __init__(this, max=1000):
		this.value = random.randint(1, max)

class NKItem(object):

	def __init__(this):
		this.field1 = Number(1000)
		this.field2 = Name(6)

	def getField1(this):
		return this.field1.value

	def compareKeys(this, other, key=getField1):
		if (this.getField1() > other.getField1()):
			return 1
		if (this.getField1() < other.getField1()):
			return -1
		return 0

	def __str__(this):
		return "key:%s field1:%s" %(this.field1.value, this.field2.value)

	def __repr__(this):
		return "%s" %(this.field1.value)


if __name__ == "__main__":
	a = NKItem()
	b = NKItem()
	a.printItem()
	b.printItem()

# print Functions etc.