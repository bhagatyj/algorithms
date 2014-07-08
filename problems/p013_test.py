from subprocess import Popen, PIPE
import os

count = 0
passCount = 0
def printline():
	x = ''
	for i in range(80):
		x = x + "="
	print x


def singleTest(qn, ansExp):
	global count, passCount

	child = Popen("./p013", stdin=PIPE, stdout=PIPE)
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
	passCount = passCount + 1



def smallDigitTests():
	singleTest('12345+67890', ' 12345\n+67890\n------\n 80235')


def runTests():
	smallDigitTests()
	largeDigitTest1()
	printline()
	print "Tests: %d\nPass: %d" %(count, passCount)
	printline()

def compileP013():
	ret = os.system('gcc -g -Wall p013.c -o p013')
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm p013')

def testP013():
	compileP013()
	runTests()
	cleanup()


testP014()
