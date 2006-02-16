#!/usr/bin/python
import Tkinter
import math
import tkFont

top = 0
canvas = 0
groups = []
colors = [(0,127,0), (20,14,135), (255,255,255)]

def DisplayCloseup(event):
   ob = canvas.find_closest(event.x, event.y, halo=5)
   tagList = canvas.gettags(ob)
#   print "Clicked: ", tagList[0]
         

def ReverseColor(i):
   c = colors[i]
   color = (255-c[0], 255-c[1], 255-c[2])
   for val in color:
      if val > 110 and val < 144:
         return "#FFFFFF"

   return "#%02x%02x%02x" % (color[0], color[1], color[2])

def GetColor(c, numGroups):
   global colors
   loop = 0
   
   while numGroups > len(colors) and loop < 65536:
      loop += 1
      newColors = []
      for i in range(0, len(colors)-1):
         oldColor = colors[i]
         oldColor2 = colors[i+1]
         newColors += [oldColor]
         newColors += [((oldColor[0] + oldColor2[0])/2, (oldColor[1] + oldColor2[1])/2, (oldColor[2] + oldColor2[2])/2)]
      oldColor = colors[len(colors)-1]
      oldColor2 = colors[0]
      newColors += [oldColor]
      newColors += [((oldColor[0] + oldColor2[0])/2, (oldColor[1] + oldColor2[1])/2, (oldColor[2] + oldColor2[2])/2)]
      colors = newColors   
 
   if loop >= 65536:
#      print "ERROR:  Ran out of colors!\n"
      return "#FFFFFF"
 
   color = colors[c] 
   return "#%02x%02x%02x" % (color[0], color[1], color[2])

def DrawSmallGroup():
   f = tkFont.Font(family='sans', size=24)
   numGroups = len(groups)
   if numGroups == 1:
      canvas.create_oval(200,150,600,550, fill="#0000FF", tag=groups[0])
      canvas.create_text(400,350, text=groups[0], font=f, fill = ReverseColor(0), tag=groups[0])
   else:
      canvas.create_oval(200,150,600,550, fill=GetColor(0,2), tag=groups[0])
      canvas.create_arc(200,150,600,550, fill=GetColor(1,2), tag=groups[1])
      canvas.create_text(300,350, text=groups[0], font=f, fill = ReverseColor(0), tag=groups[0])
      canvas.create_text(500,250, text=groups[1], font=f, fill = ReverseColor(1), tag=groups[1])

def DrawGroups():
   numGroups = len(groups)
   if numGroups < 3:
      DrawSmallGroup()
      return 

#   if numGroups > 16:
#      print 'Too many groups to render easily.  Break into pieces.'

   i = 0
   for g in groups:
      angle2 = ((2.0*math.pi)/float(numGroups))*float(i+1)
      angle = ((2.0*math.pi)/float(numGroups))*float(i)
      xoffset = -int(200.0 * math.cos(angle))
      yoffset = int(200.0 * math.sin(angle))
      xoffset2 = -int(200.0 * math.cos(angle2))
      yoffset2 = int(200.0 * math.sin(angle2))
      canvas.create_polygon(400,350, 400 + xoffset, 350 + yoffset, 400 + xoffset2, 350+yoffset2, 400,350, fill = GetColor(i, numGroups), tag=groups[i])
      canvas.create_line(400,350, 400 + xoffset, 350 + yoffset, width=2, tag=groups[i])
      if i+1<numGroups:
         canvas.create_line(400,350, 400 + xoffset2, 350 + yoffset2, width=2, tag=groups[i+1])
      else:
         canvas.create_line(400,350, 400 + xoffset2, 350 + yoffset2, width=2, tag=groups[0])
      canvas.create_text((400 + (xoffset2 + xoffset)/3), (350 + (yoffset2 + yoffset)/3), text=groups[i], fill=ReverseColor(i), tag=groups[i])
      i = i + 1
   
def SetupScreen():
   global top
   global canvas
   global groups
   top = Tkinter.Tk()
   top.title("ITVal Firewall Class Viewer")
   frame = Tkinter.Frame(top)
   frame.pack(side=Tkinter.LEFT)
   canvas = Tkinter.Canvas(frame, bg="#000000")
   canvas.configure(width=800, height=800)
   canvas.pack(side=Tkinter.TOP)
   canvas.bind('<Button-1>', DisplayCloseup)
   DrawGroups()
   Tkinter.mainloop()

def AddGroup(g):
   global groups
   groups += [g]

#AddGroup('[0-126].*.*.*\n[128-255].*.*.*\n127.[1-255].*.*\n127.0.[1-255].*\n127.0.0.0\n127.0.0.[2-255]')
AddGroup('127.0.0.1')
AddGroup(1)
AddGroup(2)
AddGroup(3)
AddGroup(4)
AddGroup(5)
AddGroup(6)
AddGroup(7)

SetupScreen()
