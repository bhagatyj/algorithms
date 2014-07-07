import pexpect
import os

count = 0

def printline():
	x = ''
	for i in range(80):
		x = x + "="
	print x

def singleTest(send, ansExp):
	global count

	child = pexpect.spawn('./p014', maxread=10000)
	child.sendline('1')
	child.expect('1')
	child.sendline(send)
	child.expect(send)

	pattern = '[0-9]{%d}' %(len(send))
	print "Expecting %s" %pattern
	child.expect(pattern)
	ansGot = child.match.group()
	printline()
	count = count + 1
	print "Test number: " + str(count)
	print "Test input : " + send
	print "Expected Answer : " + ansExp
	print "Got this Answer : " + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	#print ans


def smallDigitTests():
	singleTest('99', '99')
	singleTest('91', '99')
	singleTest('29', '33')
	singleTest('23', '33')
	singleTest('31', '33')

	singleTest('111', '111')
	singleTest('110', '111')
	singleTest('292', '292')
	singleTest('203', '212')
	singleTest('209', '212')

	singleTest('131231234', '131232131')
	singleTest('1991', '1991')
	singleTest('1981', '1991')
	singleTest('1891', '1991')

	singleTest('28994', '29092')
	singleTest('29994', '30003')


def largeDigitTest1():
	n1 = ''
	n2 = ''
	for i in range(1000):
		n1 = n1 + '1'
		n2 = n2 + '9'
	singleTest(n1, n1)
	singleTest(n2, n2)

	n3 = "2211111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
	n4 = "2211111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111122"
	singleTest(n3, n4)
	n5 = "8899999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
	n6 = "8900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000098";
	singleTest(n5, n6)
	n7 = "890000000000000000000000000000123000000000000000000000000000000000000000000000000000000000000000000098"
	n8 = "890000000000000000000000000000123000000000000000000000000000000000000321000000000000000000000000000098"
	singleTest(n7, n8)

def runTests():
	smallDigitTests()
	largeDigitTest1()

def compileP014():
	ret = os.system('gcc -g -Wall p014.c -o p014')
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm p014')

def testP014():
	compileP014()
	runTests()
	cleanup()


testP014()
