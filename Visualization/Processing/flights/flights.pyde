table = None


width = 1000
height = 1000

def setup():
    global table
    table = loadTable("flights.csv", "header")
    size(width, height)
    noLoop()
    noStroke()
    
def draw():
    global table
    background(255, 255, 255)
    for row in table.rows():
        from_x = map(row.getFloat('from_long'), -180, 180, 0, width) 
        from_y = map(row.getFloat('from_lat'), -90, 90, height/2, 0) 
        to_x = map(row.getFloat('to_long'), -180, 180, 0, width) 
        to_y = map(row.getFloat('to_lat'), -90, 90, height, height/2) 
        r = 3
        if dist(from_x, from_y, mouseX, mouseY) < 15:
            fill(255, 0, 0, 20)
        else:
            fill(0, 0, 255, 5)
        ellipse(from_x, from_y, r, r)
        ellipse(to_x, to_y, r, r)

def mouseMoved():
    redraw()
