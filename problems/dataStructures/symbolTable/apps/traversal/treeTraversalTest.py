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
	#print "Expected Answer :\n" + ansExp
	#print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	else:
		print("Passed")


def smallTests():
	content = "now is the time for all good men to come to the aid of their party"
	preResult = "Nodes in pre-order...\n3:now\n2:is\n3:for\n3:all\n3:aid\n4:come\n4:good\n3:men\n3:the\n2:of\n5:party\n4:time\n5:their\n2:to\n"
	inResult = "Nodes in in-order...\n3:aid\n3:all\n4:come\n3:for\n4:good\n2:is\n3:men\n3:now\n2:of\n5:party\n3:the\n5:their\n4:time\n2:to\n"
	postResult = "Nodes in post-order...\n3:aid\n4:come\n3:all\n4:good\n3:for\n3:men\n2:is\n5:party\n2:of\n5:their\n2:to\n4:time\n3:the\n3:now\n"
	result = preResult + inResult + postResult
	singleTest(content, result);

def runTests():
	smallTests()
	printline()



def compileCode(source):
	printline();
	command = "gcc %s -I ../../wordTree/ -I ../../words/ -I ../../trees/ \
../../wordTree/wordTreeBuilder.c ../../words/wordReader.c \
../../trees/bst/binarySearchTree.c -o exe"

	print "Compiling %s" % source
	command = command %source
	print command
	ret = os.system(command)
	if (ret != 0):
		raise Exception("Did not compile")

def cleanup():
	os.system('rm exe')

def test():
	global count
	sources = ["treeTraversal.c"]
	for source in sources:
		print
		count = 0
		compileCode(source)
		runTests()
		cleanup()


test()
