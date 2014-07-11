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
	# print "Test input : \n" + qn
	#print "Expected Answer :\n" + ansExp
	#print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	else:
		print("Passed")


def smallDigitTests():
	singleTest('Hello\nHow\nAre\nYou?\n', 'You?\nAre\nHow\nHello\n')
	qn = ""
	ans = ""
	for i in range(256):
		qn = qn + "x\n"
		ans = ans + "x\n"
	singleTest(qn, ans)
	qn = ""
	ans = ""
	count = 256
	for i in range(count):
		qn = qn + ("%d\n" %i)
		ans = ans + ("%d\n" %(count-1-i))
	singleTest(qn, ans)

def runTests():
	smallDigitTests()
	printline()


def compileCode(source):
	print "Compiling %s" % source
	ret = os.system('gcc -g -Wall %s -o exe' %source)
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def testP014():
	#sources = ["stringStack_ll.c", "stringStack.c"]
	sources = ["stringStack_llar.c"]
	for source in sources:
		compileCode(source)
		runTests()
		cleanup()


testP014()
