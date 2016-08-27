import turtle
import math
def line(t, x1, y1, x2, y2):
    t.up()
    t.goto(x1, y1)
    t.down()
    t.goto(x2, y2)
    t.up()

class Ant:
    def __init__( self, t, x, y ):
        self.x = x * 1.0
        self.y = y * 1.0

    def setFriend( self, other ):
        self.friend = other

    def distanceFromFriend( self ):
        xDist = self.friend.x - self.x 
        yDist = self.friend.y - self.y
        distance = math.sqrt( xDist*xDist + yDist*yDist )
        return distance

    def stepTowardsFriend( self ):
        distance = self.distanceFromFriend()
        newX = self.x + (1.0/100) * (self.friend.x - self.x)
        newY = self.y + (1.0/100) * (self.friend.y - self.y)
        line( t, self.x, self.y, newX, newY)
        self.x = newX
        self.y = newY
        
if __name__ == "__main__":
    t = turtle.Turtle()
    side = 200
    a = Ant(t, 0, 0 )
    b = Ant(t, side, 0 )
    c = Ant(t, side, side )
    d = Ant(t, 0, side )
    a.setFriend(b)
    b.setFriend(c)
    c.setFriend(d)
    d.setFriend(a)
    while a.distanceFromFriend() > 1:
        a.stepTowardsFriend()
        b.stepTowardsFriend()
        c.stepTowardsFriend()
        d.stepTowardsFriend()
    name = raw_input("Enter : ")
    
