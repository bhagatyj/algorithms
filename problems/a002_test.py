#  Input:
#  N
#  U:p,q
#  U:x,y
#  .....
#  U:a,b
#  C:a,y
#  Output:
#  TRUE/FALSE


import os
from subprocess import Popen, PIPE
import time

count = 0

def printline():
	x = ''
	for i in range(80):
		x = x + "="
	print x

def singleTest(qn, ansExp):
	global count

	child = Popen("./exe", stdin=PIPE, stdout=PIPE)
	child.stdin.write(qn)
	child.stdin.close()
	#print "Waiting for read"
	#time.sleep(1)
	ansGot =  child.stdout.read()

	printline()
	count = count + 1
	print "Test number: " + str(count)
	print "Test input : \n" + qn
	print "Expected Answer :\n" + ansExp
	print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')


def smallDigitTests():
	singleTest('Hello\nHow\nAre\nYou?\n', 'You?\nAre\nHow\nHello\n')

def runTests():
	smallDigitTests()


def compileCode():
	ret = os.system('gcc -g -Wall a002.c -o exe')
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def testP014():
	compileCode()
	runTests()
	cleanup()


testP014()
