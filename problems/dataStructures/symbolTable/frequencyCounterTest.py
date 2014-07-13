import os
from subprocess import Popen, PIPE
import time
import urllib2

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
	print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	else:
		print("Passed")


def smallTests():
	content = "now is the time for all good men to come to the aid of their party"
	singleTest(content, "the is present 2 times\n");

def largeTests():
	content = urllib2.urlopen("http://www.gutenberg.org/cache/epub/8190/pg8190.txt").read()
	singleTest(content, 'the is present 1590 times\n')

	content = urllib2.urlopen("http://www.gutenberg.org/cache/epub/10554/pg10554.txt").read()
	singleTest(content, 'the is present 3326 times\n')

def runTests():
	smallTests()
	largeTests()
	printline()


def compileCode(source):
	printline();
	print "Compiling %s" % source
	ret = os.system('gcc -g -Wall %s binarySerachTree.c wordReader.c -o exe' %source )
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def test():
	global count
	sources = ["frequencyCounter.c"]
	for source in sources:
		print
		count = 0
		compileCode(source)
		runTests()
		cleanup()


test()
