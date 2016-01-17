import urllib, os, time

class UrlReader:
    def __init__(self, url):
        self.index = 0
        response = urllib.urlopen(url).readlines()
        self.wordset = set()
        for line in response:
            self.wordset.update(line.split())
        self.words = list(self.wordset)
        self.words.sort()
        print len(self.words)

    def __iter__(self):
        self.index = 0
        return self

    def next(self):
        if self.index > len(self.words)-1:
            raise StopIteration
        word = self.words[self.index]
        self.index += 1
        return word

class FileReader:
    def __init__(self, fileName):
        self.fileName = fileName
        with open(self.fileName) as f:
            self.contents = f.read()

    def __iter__(self):
        return self

    def next(self):
        for word in self.contents:
            print word
            yield word
        raise StopIteration

    def readWords(self):
        with open(self.fileName) as f:
            line = f.readline()
            if not line:
                return
        for word in self.contents:
            yield word




if __name__  == "__main__":
    #r = Reader("http://www.gutenberg.org/cache/epub/35/pg35.txt")
    #for newWord in r:
        #print newWord
    dataDir = os.getcwd() + '/data/'
    count = 0
    for filename in os.listdir(dataDir):
        r = FileReader(dataDir+filename)
        x = r.readWords()
        for i in range(20):
            print next(x)
        print next(x)
        for word in r:
            print count, word
            count += 1
            time.sleep(1)
    print count
