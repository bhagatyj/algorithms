import urllib

class Reader:
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

if __name__  == "__main__":
    r = Reader("http://www.gutenberg.org/cache/epub/35/pg35.txt")
    #for newWord in r:
        #print newWord
