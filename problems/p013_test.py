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
	print "Expected Answer : \n" + ansExp
	print "Got this Answer : \n" + ansGot
	ansExp = ansExp + '\n'
	if (ansExp != ansGot):
		raise Exception('Test failed')
	passCount = passCount + 1



def singleTests():
	singleTest('12345+67890', ' 12345\n+67890\n------\n 80235')
	singleTest('12345+7890', ' 12345\n+ 7890\n------\n 20235')
	singleTest('12345+0', ' 12345\n+    0\n------\n 12345')
	singleTest('12345+90', ' 12345\n+   90\n------\n 12435')
	singleTest('45+67890', '    45\n+67890\n------\n 67935')

	singleTest('12345-90', ' 12345\n-   90\n------\n 12255')
	singleTest('12345-0', ' 12345\n-    0\n------\n 12345')
	singleTest('12345+890', ' 12345\n+  890\n------\n 13235')
	singleTest('12345+100', ' 12345\n+  100\n------\n 12445')
	singleTest('12345-123', ' 12345\n-  123\n------\n 12222')
	singleTest('12345-12345', ' 12345\n-12345\n------\n     0')


def runTests():
	singleTests()
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


testP013()
