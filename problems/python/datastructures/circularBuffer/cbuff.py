
class CircularBuffer:
    def __init__(self, size):
        self.buffer = [None] *size
        self.tail = 0
        self.head = 0
        self.size = size
        self.count = 0

    def incrIndex(self, index):
        return ( index + 1) % self.size

    def isFull(self):
        if ( self.incrIndex( self.head ) == self.tail ):
            return True
        else:
            return False

    def isEmpty(self):
        if ( self.head == self.tail ):
            return True
        else:
            return False

    def enqueue(self, item):
        if self.isFull():
            return
        else:
            self.buffer[self.head] = item
            self.head = self.incrIndex(self.head)
            return

    def dequeue(self):
        if self.isEmpty():
            return None
        else:
            item = self.buffer[self.tail]
            self.tail = self.incrIndex(self.tail)
            return item

if __name__ == '__main__':
    cb = CircularBuffer(4)
    for i in range(4):
        cb.enqueue(i)
    for i in range(4):
        print cb.dequeue()
 