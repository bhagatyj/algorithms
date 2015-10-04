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
	# print "Expected Answer :\n" + ansExp
	# print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	else:
		print("Passed")


def smallDigitTests():
	singleTest('4\n34\n2\n45\n', '2\n4\n34\n45\n')
	singleTest('4\n34\n\n2\n45\n', '4\n2\n34\n45\n')

	qn = ""
	ans = ""
	count = 256
	for i in range(count):
		qn = qn + ("%d\n" %(count-1-i))
		ans = ans + ("%d\n" %i)
	singleTest(qn, ans)

def runTests():
	smallDigitTests()
	printline()


def compileCode(source):
	printline();
	print "Compiling %s" % source
	ret = os.system('gcc -g -Wall %s priorityQMain.c -o exe' %source )
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def test():
	global count
	sources = ["priorityQ_Impl1.c"]
	for source in sources:
		print
		count = 0
		compileCode(source)
		runTests()
		cleanup()


test()
