import os
from subprocess import Popen


def cleanup():
	os.system('rm exe')

def test():
	os.chdir('./traversal')
	ret = os.system('python ./treeTraversalTest.py')
	os.chdir('..')
	os.chdir('./frequencyCounter')
	ret += os.system('python ./frequencyCounterTest.py')
	os.chdir('..')
	print ret
test()
