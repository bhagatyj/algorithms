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
	# print "Got this Answer :\n" + ansGot
	if (ansExp != ansGot):
		raise Exception('Test failed')
	else:
		print("Passed")


def smallTests():
	content = "now is the time for all good men to come to the aid of their party"
	preResult = """Nodes in pre-order...
now                     :3
is                      :2
for                     :3
all                     :3
aid                     :3
come                    :4
good                    :4
men                     :3
the                     :3
of                      :2
party                   :5
time                    :4
their                   :5
to                      :2\n"""
	inResult = """Nodes in in-order...
aid                     :3
all                     :3
come                    :4
for                     :3
good                    :4
is                      :2
men                     :3
now                     :3
of                      :2
party                   :5
the                     :3
their                   :5
time                    :4
to                      :2\n"""
	postResult = """Nodes in post-order...
aid                     :3
come                    :4
all                     :3
good                    :4
for                     :3
men                     :3
is                      :2
party                   :5
of                      :2
their                   :5
to                      :2
time                    :4
the                     :3
now                     :3\n"""
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
