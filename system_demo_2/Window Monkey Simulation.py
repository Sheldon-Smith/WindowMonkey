# events-example0.py
# Barebones timer, mouse, and keyboard events

from tkinter import *
from math import *
import time

####################################
# customize these functions
####################################

def init(data):
    # Game Mode
    data.mode = "Menu"
    data.lenBlank = False
    data.speedBlank = False
    data.cupBlank = False
    data.space = 40
    data.subX, data.subY = 320, 300
    data.shift = 350
    data.lenText = ""
    data.speedText = ""
    data.cupText = ""
    data.fastButton = "white"
    data.coverageButton = "White"
    # Panel
    data.panelX, data.panelY = 600 ,20
    data.exitButtonColor = "white"
    data.exitFontColor = "red"
    # Robot Info
    data.width = 1200
    data.height = 1000
    data.margin = 20
    data.windowWidth= 500 #5 feet
    data.windowHeight = 600 # 6 feet
    data.distFromFround = 100
    data.seperatorHeight = 300
    data.robotLength = 63 # 1 feet
    data.robotWidth = 20
    data.robotDirection = 0
    data.cupRadius = 15
    data.robotX = data.margin + data.cupRadius + data.robotLength
    data.robotY = data.margin + data.cupRadius
    data.switching = False
    data.washedArea = []
    data.washedCircle = []
    data.maxRotateAng = 180
    data.startAng = 180
    data.isNearBorder = False
    data.pattern = "pattern1"
    data.verticalAngShift = 0
    data.initAng = 0
    data.speed= 30
    data.timer = time.time()
    data.cupOperTime = 0
    data.robotMode = "NORMAL"
    data.lenUnit = "inch"
    data.speedUnit = "degree/second"
    data.cupUnit = "second"
    data.coverage = 0
    data.start = False # deduct aportion of area when calculating coverage
def mousePressed(event, data):
    space = data.space
    x, y = event.x, event.y
    subX, subY = data.subX, data.subY
    shift = data.shift
    if data.mode == "Simulate" or data.mode == "End":
        if event.x >= data.panelX+10*space and event.y >= data.panelY+15*space and\
        event.x <= data.panelX+data.margin+10*space+80 and event.y <= data.panelY+data.margin+15*space+50:
            init(data)
            data.mode = "Menu"
    elif data.mode == "Menu":
        if x > 500 and y > subY+6*space and x < 730 and y < subY+50+6*space:
            if data.lenText.isdigit():
                data.robotLength = int(data.lenText//12)-2*data.cupRadius if int(data.lenText) >40 else 63
            if data.speedText.isdigit():
                data.speed = int(data.speedText)//10 if int(data.speedText) > 50 else 15
            if data.cupText.isdigit():
                data.cupOperTime = int(data.cupText)*1000
            if data.fastButton == "cyan":
                data.robotMode = "FAST"
            else:
                data.robotMode = "NORMAL"
            data.timer = time.time()
            data.mode = "Simulate"
        if x > subX+shift and y > subY and x < subX+300+shift and y < subY+35:
            data.lenBlank = True
            data.speedBlank = False
            data.cupBlank = False
        if x > subX+shift and y > subY+space and x < subX+300+shift and y < subY+35+space:
            data.lenBlank = False
            data.speedBlank = True
            data.cupBlank = False
        if x > subX+shift and y > subY+2*space and x < subX+300+shift and y < subY+35+2*space:
            data.lenBlank = False
            data.speedBlank = False
            data.cupBlank = True
            
        if x > subX+shift and y > subY+3*space and x < subX+150+shift and y < subY+35+3*space:
            data.fastButton = "cyan"
            data.coverageButton = "white"
        if x > subX+shift+155 and y > subY+3*space and x < subX+300+shift and y <subY+35+3*space:
            data.fastButton = "white"
            data.coverageButton = "cyan"

def keyPressed(event, data):
    # use event.char and event.keysym
    if data.mode == "Menu":
        if event.keysym.isdigit():
            if data.lenBlank and len(data.lenText)<3:
                data.lenText += event.keysym
            if data.speedBlank and len(data.speedText)<3:
                data.speedText += event.keysym
            if data.cupBlank and len(data.cupText)<2:
                data.cupText += event.keysym
                
        if event.keysym == "BackSpace":
            if data.lenBlank:
                data.lenText = data.lenText[:-1]
            if data.speedBlank:
                data.speedText = data.speedText[:-1]
            if data.cupBlank:
                data.cupText = data.cupText[:-1]

def timerFired(data):
    if data.mode == "Simulate":
        hardCodeMotion(data)
        data.totalTime = time.time()-data.timer
    elif data.mode == "End":
        pass
def hardCodeMotion(data):
    if data.robotY + data.robotLength + data.cupRadius >=\
       data.margin + data.windowHeight:
           data.mode = "End"
           
    if data.pattern == "pattern1":
        switchCup(data)
        rotate(data)
        if isNearBorder(data) and not data.isNearBorder:
            data.isNearborder = True
            data.pattern = "pattern1_1"
            data.switching = True
            switchCup(data)
            # faster
            if data.fastButton == "cyan":
                data.pattern = "pattern2"
            else:
            # more coverage
                data.pattern = "pattern3_1"
            
    if data.pattern == "pattern2":
        rotate(data)
        if data.robotDirection > 90:
            data.switching = True
            switchCup(data)
            data.pattern = "pattern3"
            data.isNearBorder = False
    
    # faster
    if data.pattern == "pattern3":
        rotate(data)
        if data.robotDirection > 0:
            data.switching = True
            switchCup(data)
            data.pattern = "pattern4"
            
    # more coverage
    if data.pattern == "pattern3_1":
        rotate(data)
        if data.robotDirection > 0:
            data.switching = True
            switchCup(data)
            data.pattern = "pattern4"
            
    if data.pattern == "pattern4":
        rotate(data)
        if data.robotDirection+data.verticalAngShift == 360:
            saveWashedCircle(data)
        if data.robotDirection+data.verticalAngShift > 540:
            data.switching = True
            switchCup(data)
        if isNearBorder360(data):
            data.pattern = "pattern4_5"
            data.switching = True
            switchCup(data)
            
    if data.pattern == "pattern4_5":
        reverseRotate(data)
        if data.robotDirection <90:
            saveWashedArea(data)
            # fasrer
            if data.fastButton == "cyan":
                data.pattern = "pattern4_5_2"
            else:
            # more coverage
                data.pattern = "pattern4_5_2_1"
            data.switching = True
            switchCup(data)
    # faster
    if data.pattern == "pattern4_5_2":
        reverseRotate(data)
        if data.robotDirection < -270:
            saveReverseWashedArea(data)
            data.pattern = "pattern4_5_3"
            data.switching = True
            switchCup(data)
            
    # more coverage        
    if data.pattern == "pattern4_5_2_1":
        reverseRotate(data)
        if data.robotDirection < 90:
            data.pattern = "pattern4_5_3_1"
            data.switching = True
            switchCup(data)
    # faster
    if data.pattern == "pattern4_5_3": 
        reverseRotate(data)
        if data.robotDirection < -180:
            saveReverseWashedArea(data)
            data.pattern = "pattern5"
            data.switching = True
            switchCup(data)
    # more coverage
    if data.pattern == "pattern4_5_3_1": 
        reverseRotate(data)
        if data.robotDirection < -180:
            data.pattern = "pattern5"
            data.switching = True
            switchCup(data)
            
    if data.pattern == "pattern5":
        if isNearBorder360(data):
            data.startAng = 180
            data.robotDirection = 0
            data.verticalAngShift = 0
            data.maxRotateAng = 180
            data.initAng = 0
            data.pattern = "pattern1"
        else:
            reverseRotate(data)
            if data.robotDirection+data.verticalAngShift == -360:
                saveWashedCircle(data)
            if data.robotDirection < -540:
                data.switching = True
                switchCup(data)
                
def partialInit(data):
    data.startAng = 180
    data.robotDirection = 0
    data.verticalAngShift = 0
    data.maxRotateAng = 180
    data.initAng = 0
    
def isNearBorder(data):
    # 90 CANNOT BE SPARED SINCE WE NEED THAT ADDITIONAL 90 DEGREE ROTATE
    if data.robotX + data.robotLength > data.windowWidth and\
    data.robotDirection > 90:
        return True
    return False
    
def isNearBorder360(data):
    if data.robotX - data.robotLength < data.margin or\
       data.robotX + data.robotLength > data.windowWidth:
        return True
    return False
        
def rotate(data):
    if data.pattern == "pattern1":
        if data.robotDirection+data.verticalAngShift < data.maxRotateAng:
            data.robotDirection += data.speed
        else:
            data.switching = True
            saveWashedArea(data)
    else:
        if data.robotDirection+data.verticalAngShift <= data.maxRotateAng:
            data.robotDirection += data.speed
        else:
            data.switching = True
            saveWashedArea(data)
            
def reverseRotate(data):
    if data.robotDirection+data.verticalAngShift >= data.maxRotateAng:
        data.robotDirection -= data.speed
    else:
        data.switching = True
        saveWashedArea(data)
        
def saveWashedArea(data):
    l = data.robotLength
    x,y = data.robotX, data.robotY
    if data.maxRotateAng < 360:
        data.washedArea += [(x-l,y-l,x+l,y+l, data.initAng-180, data.maxRotateAng)]
    else:
        pass
        
def saveReverseWashedArea(data):
    l = data.robotLength
    x,y = data.robotX, data.robotY
    if data.maxRotateAng < 360:
        data.washedArea += [(x-l,y-l,x+l,y+l, data.initAng+data.maxRotateAng, -data.maxRotateAng)]
    else:
        pass
        
def saveWashedCircle(data):
    l = data.robotLength
    x,y = data.robotX, data.robotY
    data.washedCircle += [(x-l,y-l,x+l,y+l)]
    
def changeDirection(data):
    l = data.robotLength
    x,y = data.robotX, data.robotY
    data.washedArea += [(x-l,y-l,x+l,y+l, data.initAng-180, data.robotDirection-data.speed)]
    data.startAng = 90
    data.robotY += data.robotLength
    data.robotDirection = -90
    data.verticalAngShift = 90
    
def calCoverage(data):
    circleArea = pi*((data.robotLength + data.cupRadius)**2-data.cupRadius**2)
    if data.pattern == "pattern1":
        data.coverage += circleArea//4
    elif data.pattern == data.pattern == "pattern4":
        if data.robotMode == "FAST":
            data.coverage += circleArea//2.5
        else:
            data.coverage += circleArea//4
            data.start = False
    elif data.pattern == "pattern5":
        if data.robotMode == "FAST":
            data.coverage += circleArea//2.5
        else:
            if not data.start:
                data.coverage -= circleArea//3
                data.start = True
            data.coverage += circleArea//4
            
def switchCup(data, second = False):
    
    if data.switching:
        if data.pattern == "pattern1":
            # normal 180 degrees
            data.robotX, data.robotY = data.robotX + data.robotLength, data.robotY
            data.robotDirection = 0
        
        elif data.pattern == "pattern1_1":
            changeDirection(data)
            data.initAng = -90
            
        elif data.pattern ==  "pattern2":
            saveWashedArea(data)
            data.startAng = 90
            data.robotY += data.robotLength
            data.robotDirection = -90
            data.verticalAngShift = 90
            data.maxRotateAng = 90
        ## faster
        elif data.pattern == "pattern3_1":
            data.startAng = 0
            data.robotX -= data.robotLength
            data.robotDirection = 180
            data.verticalAngShift = -180
            data.maxRotateAng = 540
            
        ## more coverage(need to skip pattern 2)
        elif data.pattern == "pattern3":
            saveWashedArea(data)
            data.startAng = 0
            data.robotX -= data.robotLength
            data.robotDirection = 180
            data.verticalAngShift = -180
            data.maxRotateAng = 540
            
        elif data.pattern == "pattern4":
            saveWashedArea(data)
            data.startAng = 0
            data.robotX -= data.robotLength
            data.robotDirection = 180
            pass
            
        elif data.pattern == "pattern4_5":
                data.initAng = 180
                data.maxRotateAng = -90
        # faster
        elif data.pattern == "pattern4_5_2":
            data.initAng = 90#The initial angle of robot ang
            data.startAng = 90
            data.robotY += data.robotLength
            data.robotDirection = -90
            data.verticalAngShift = 90
            data.maxRotateAng = -180
        # more coverage
        elif data.pattern == "pattern4_5_2_1":
            data.initAng = 180#The initial angle of robot ang
            data.startAng = 180
            data.robotY += data.robotLength
            data.robotDirection = 0
            data.verticalAngShift = 0
            data.maxRotateAng = -90
        
        # faster
        elif data.pattern == "pattern4_5_3":
            data.startAng = 90
            data.robotY += data.robotLength
            data.robotDirection = -90
            data.verticalAngShift = 90
            data.maxRotateAng = -90
            
        # more coverage
        elif data.pattern == "pattern4_5_3_1":
            data.startAng = 90
            data.robotDirection = -90
            data.verticalAngShift = 90
            data.maxRotateAng = -90
            
        elif data.pattern == "pattern5":
            data.robotX += data.robotLength
            data.startAng = 180
            data.robotDirection = 0
            data.verticalAngShift = 0
            data.maxRotateAng = -540
            
        calCoverage(data)
        data.root.after(data.cupOperTime)
        data.switching = False
    

def redrawAll(canvas, data):
    # draw in canvas
    if data.mode == "Simulate" or data.mode == "End":
        margin = data.margin
        groundPos = data.windowHeight+margin + data.distFromFround + margin
        canvas.create_rectangle(margin, margin, data.windowWidth+margin, data.windowHeight+margin, fill = "gray", width = 2)
        canvas.create_rectangle(margin, data.windowHeight+margin, data.windowWidth+margin, data.windowHeight+margin + data.distFromFround, width = 2)
        canvas.create_line(margin, groundPos - data.seperatorHeight, margin + data.windowWidth, groundPos - data.seperatorHeight, width=5)
        drawRobot(canvas,data)
        drawPanel(canvas, data)
    elif data.mode == "Menu":
        drawMenu(canvas, data)
        if data.lenBlank:
            canvas.create_line(data.subX+data.shift+5, data.subY, data.subX+data.shift+5, data.subY+35, fill="black")
        if data.speedBlank:
            canvas.create_line(data.subX+data.shift+5, data.subY+data.space, data.subX+data.shift+5, data.subY+data.space+35, fill="black")
        if data.cupBlank:
            canvas.create_line(data.subX+data.shift+5, data.subY+2*data.space, data.subX+data.shift+5, data.subY+2*data.space+35, fill="black")
        
def drawMenu(canvas, data):
    space = data.space
    titleX, titleY = 230,100
    subX, subY = data.subX, data.subY
    shift = data.shift
    canvas.create_text(titleX,titleY,
     text="Simulation Program", font=("Helvetica", 84), fill="black", anchor=NW)
    canvas.create_text(subX, subY,
     text="Length: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(subX, subY+space,
     text="Speed: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(subX, subY+2*space,
     text="Cup Operation Time: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_rectangle(subX+shift, subY, subX+300+shift, subY+35,  fill="white", width=2)
    canvas.create_text(subX+shift+10, subY, text = data.lenText,font=("Helvetica", 24), anchor = NW)
    canvas.create_text(subX+shift+10+300, subY, text = data.lenUnit,font=("Helvetica", 24), anchor = NW)
    canvas.create_rectangle(subX+shift, subY+space, subX+300+shift, subY+35+space,  fill="white", width=2)
    canvas.create_text(subX+shift+10, subY+space, text = data.speedText,font=("Helvetica", 24), anchor = NW)
    canvas.create_text(subX+shift+10+300, subY+space, text = data.speedUnit,font=("Helvetica", 24), anchor = NW)
    canvas.create_rectangle(subX+shift, subY+2*space, subX+300+shift, subY+35+2*space,  fill="white", width=2)
    canvas.create_text(subX+shift+10, subY+2*space, text = data.cupText,font=("Helvetica", 24), anchor = NW)
    canvas.create_text(subX+shift+10+300, subY+2*space, text = data.cupUnit,font=("Helvetica", 24), anchor = NW)
    canvas.create_text(subX, subY+3*space,
     text="Mode: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_rectangle(subX+shift, subY+3*space, subX+150+shift, subY+35+3*space,  fill=data.fastButton, width=2)
    canvas.create_text(subX+shift+45, subY+3*space+5, text = "FAST", font=("Helvetica", 24), anchor=NW)
    canvas.create_rectangle(subX+shift+155, subY+3*space, subX+300+shift, subY+35+3*space,  fill=data.coverageButton, width=2)
    canvas.create_text(subX+shift+175, subY+3*space+5, text = "NORMAL", font=("Helvetica", 24), anchor=NW)
    canvas.create_rectangle(450+50, subY+6*space, 450+280, subY+50+6*space, fill="gray", width=1)
    canvas.create_text(450+50+50, subY+6*space+5,
     text="Simulate!", font=("Helvetica", 32), fill="white", anchor=NW)
     
def drawPanel(canvas, data):
    space = data.space
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin,
     text="Length: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+ 200, data.panelY+data.margin,
     text=str((data.robotLength+2*data.cupRadius)*12//100), font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+300, data.panelY+data.margin,
     text=data.lenUnit, font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin+space,
     text="Speed: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+ 200, data.panelY+data.margin+space,
     text=str(data.speed*10), font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+300, data.panelY+data.margin+space,
     text=data.speedUnit, font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin+3*space,
     text="Coverage: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+ 200, data.panelY+data.margin+3*space,
     text=str("%.2f"%(data.coverage/(500*6))), font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+300, data.panelY+data.margin+3*space,
     text="%", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin+4*space,
     text="Mode: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+ 200, data.panelY+data.margin+4*space,
     text=data.robotMode, font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin+2*space,
    text="Cup Time: ", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+200, data.panelY+data.margin+2*space,
    text=str((data.cupOperTime)//1000), font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+300, data.panelY+data.margin+2*space,
    text="second", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin, data.panelY+data.margin+15*space,
     text="Timer: ", font=("Helvetica", 32), fill="black", anchor=NW)
    if data.mode == "Simulate":
        canvas.create_text(data.panelX+data.margin+120, data.panelY+data.margin+15*space,
        text=str("%.2f"%(time.time()-data.timer)), font=("Helvetica", 32), fill="black", anchor=NW)
    else:
        canvas.create_text(data.panelX+data.margin+120, data.panelY+data.margin+15*space,
        text=str(data.totalTime)[:6], font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_text(data.panelX+data.margin+300, data.panelY+data.margin+15*space,
     text="s", font=("Helvetica", 32), fill="black", anchor=NW)
    canvas.create_rectangle(data.panelX+10*space, data.panelY+15*space, data.panelX+data.margin+10*space+80, data.panelY+data.margin+15*space+50,  fill=data.exitButtonColor, width=5)
    canvas.create_text(data.panelX+data.margin+10*space, data.panelY+data.margin+15*space,
     text="Exit", font=("Helvetica", 32), fill=data.exitFontColor, anchor=NW)
    
def drawRobot(canvas, data):
    r = data.cupRadius
    (x, y) = (data.robotX, data.robotY)
    l = data.robotLength
    w = data.robotWidth
    direction = pi/180*(data.robotDirection+180) # (degree)
    for area in data.washedArea:
        canvas.create_arc(area[0],area[1],area[2],area[3],start=area[4],extent=area[5],fill = "white", style=PIESLICE,outline="")
    for c in data.washedCircle:
        canvas.create_oval(c[0],c[1],c[2],c[3],fill="white",width=0)
    canvas.create_arc(x-l,y-l,x+l,y+l,start=data.startAng,extent=data.robotDirection+data.verticalAngShift,fill = "white", style=PIESLICE,outline="")
    ##Seperator##
    groundPos = data.windowHeight+data.margin + data.distFromFround + data.margin
    canvas.create_line(data.margin, groundPos - data.seperatorHeight, data.margin + data.windowWidth, groundPos - data.seperatorHeight, width=5)
    ###
    canvas.create_oval(x-r, y-r, x+r, y+r, fill="blue")
    canvas.create_oval(x+l*cos(direction)-r, y-l*sin(direction)-r, x+l*cos(direction)+r, y-l*sin(direction)+r, fill="blue")
    canvas.create_line(x,y,x+l*cos(direction),y-l*sin(direction), width = w, fill="gold")


####################################
# use the run function as-is
####################################

def run(width=300, height=300):
    def redrawAllWrapper(canvas, data):
        canvas.delete(ALL)
        canvas.create_rectangle(0, 0, data.width, data.height,
                                fill='white', width=0)
        redrawAll(canvas, data)
        canvas.update()    

    def mousePressedWrapper(event, canvas, data):
        mousePressed(event, data)
        redrawAllWrapper(canvas, data)

    def keyPressedWrapper(event, canvas, data):
        keyPressed(event, data)
        redrawAllWrapper(canvas, data)

    def timerFiredWrapper(canvas, data):
        timerFired(data)
        redrawAllWrapper(canvas, data)
        # pause, then call timerFired again
        canvas.after(data.timerDelay, timerFiredWrapper, canvas, data)
    # Set up data and call init
    class Struct(object): pass
    data = Struct()
    data.width = width
    data.height = height
    data.timerDelay = 100 # milliseconds
    init(data)
    # create the root and the canvas
    root = Tk()
    data.root = root
    canvas = Canvas(root, width=data.width, height=data.height)
    canvas.pack()
    # set up events
    root.bind("<Button-1>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    root.bind("<Key>", lambda event:
                            keyPressedWrapper(event, canvas, data))
    timerFiredWrapper(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    ("bye!")

run(400, 200)