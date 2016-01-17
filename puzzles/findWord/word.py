# Implements the word class.

class Word:
    def __init__(self, word):
        self.word = word
        self.letters = [x.lower() for x in list(self.word)]
        self.letters.sort()
        self.key = "".join(self.letters)
        self.frequency = 0

    def __str__(self):
        return self.word

    def __repr__(self):
        return self.word
