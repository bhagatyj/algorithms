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
	content = "I wonder how many housewives who may read this little book have ever dried sweet corn for winter use."
	singleTest(content, "housewives:  10\n");

def largeTest(url, result):
	filename = url.split("/")[-1]
	if ( not os.path.isfile(filename)):
		testfile = urllib.URLopener()
		testfile.retrieve(url, filename)
	f = open(filename, 'r');
	content = f.read()
	singleTest(content, result)

def largeTests():
	urlTheCount = dict()
	urlTheCount["http://www.gutenberg.org/cache/epub/8190/pg8190.txt"] = "Idiopsychological:  17\n"
	urlTheCount["http://www.gutenberg.org/cache/epub/10554/pg10554.txt"] = "misunderstandings:  17\n"
	urlTheCount["http://www.gutenberg.org/cache/epub/8178/pg8178.txt"] = "unenthusiastically:  18\n"
	for url in urlTheCount:
		print url
		largeTest(url, urlTheCount[url]) 



def runTests():
	smallTests()
	largeTests()
	printline()


def compileCode(source):
	printline();
	print "Compiling %s" % source
	ret = os.system('gcc %s -I ../../wordTree/ -I ../../words/ -I ../../trees/ \
../../wordTree/wordTreeBuilder.c ../../words/wordReader.c \
../../trees/bst/binarySearchTree.c -o exe' %source )
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def test():
	global count
	sources = ["longestWord.c"]
	for source in sources:
		print
		count = 0
		compileCode(source)
		runTests()
		cleanup()


test()
