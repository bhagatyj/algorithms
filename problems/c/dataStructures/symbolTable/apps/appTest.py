import os
from subprocess import Popen


def printline():
	x = ''
	for i in range(80):
		x = x + "*"
	print x


def test():
	os.chdir('./traversal')
	ret = os.system('python ./treeTraversalTest.py')
	os.chdir('..')
	os.chdir('./frequencyCounter')
	ret += os.system('python ./frequencyCounterTest.py')
	os.chdir('..')
	os.chdir('./longestWord')
	ret += os.system('python ./longestWordTest.py')
	os.chdir('..')
	print
	printline()
	if (not ret):
		print "All Tests passed"
	else:
		print "Test Failed"
	printline()
test()
