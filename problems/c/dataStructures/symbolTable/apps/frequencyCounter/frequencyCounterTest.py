import os
from subprocess import Popen, PIPE
import time
import urllib

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


def smallTests():
	content = "now is the time for all good men to come to the aid of their party"
	singleTest(content, "the is present 2 times\n");

def largeTest(url, count):
	filename = url.split("/")[-1]
	if ( not os.path.isfile(filename)):
		testfile = urllib.URLopener()
		testfile.retrieve(url, filename)
	f = open(filename, 'r');
	content = f.read()
	result = 'the is present %d times\n' %count
	singleTest(content, result)

def largeTests():
	urlTheCount = dict()
	urlTheCount["http://www.gutenberg.org/cache/epub/8190/pg8190.txt"] = 1590
	urlTheCount["http://www.gutenberg.org/cache/epub/10554/pg10554.txt"] = 3326
	for url in urlTheCount:
		largeTest(url, urlTheCount[url]) 

def runTests():
	smallTests()
	largeTests()
	printline()



def compileCode(source):
	printline();
	command = "gcc %s -I ../../wordTree/ -I ../../words/ -I ../../trees/ \
../../wordTree/wordTreeBuilder.c ../../words/wordReader.c \
../../trees/bst/binarySearchTree.c -o exe"

	print "Compiling %s" % source
	command = command %source
	ret = os.system(command)
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
