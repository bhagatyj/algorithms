import os
from subprocess import Popen, PIPE
import pexpect

count = 0

def printline():
	x = ''
	for i in range(80):
		x = x + "="
	print x

def singleTest(qn, ansExp):
	global count

	child = Popen("./p015", stdin=PIPE, stdout=PIPE)
	child.stdin.write('1\n')
	child.stdin.write(qn + '\n')
	#print "Waiting for read"
	ansGot =  child.stdout.read()

	printline()
	count = count + 1
	print "Test number: " + str(count)
	print "Test input : " + qn
	print "Expected Answer : " + ansExp
	print "Got this Answer : " + ansGot
	ansExp = ansExp + '\n'
	if (ansExp != ansGot):
		raise Exception('Test failed')


def smallDigitTests():
	singleTest('(a+(b*c))', 'abc*+')
	singleTest('((a+b)*(z+x))', 'ab+zx+*')
	singleTest('((a+t)*((b+(a+c))^(c+d)))', 'at+bac++cd+^*')



def largeDigitTest1():
	pass

def runTests():
	smallDigitTests()


def compileP014():
	ret = os.system('gcc -g -Wall p015.c -o p015')
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm p015')

def testP014():
	compileP014()
	runTests()
	cleanup()


testP014()
