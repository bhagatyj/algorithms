# Contains a dictionary of words.
# Which can be retrieved by giving the frequency of letters in them
from word import Word
import reader
import time
import itertools

class Dictionary:
    def __init__(self):
        self.words = dict()

    def addWord(self, newWord):
        word = Word(newWord)
        key = word.key
        #print "Adding word ", w, "at key ", key
        if key in self.words.keys():
            if word in self.words[key]:
                pass
                # increase the frequency for the word
            else:
                self.words[key].append(word)
        else:
            self.words[key] = [word]

    def findWord(self, characters):
        foundWord = None
        for listLen in range(len(list(characters)), 7, -1):
            for combo in itertools.combinations(characters, listLen):
                searchWord = "".join(combo)
                letters = list(combo)
                letters.sort()
                key = "".join(letters)
                #print "Searching for", key
                if key in self.words:
                    foundWord = self.words[key][0].word
        return foundWord

if __name__ == "__main__":
    d = Dictionary()
    print time.clock()
    r = reader.UrlReader("http://www.gutenberg.org/cache/epub/35/pg35.txt")
    for newWord in r:
        d.addWord(newWord)
    print time.clock()
    print time.clock()
    print d.findWord(list("ansuddendly"))
    print time.clock()
    print d.words.items()

