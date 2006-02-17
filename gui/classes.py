#!/usr/bin/python
import Tkinter
import math
import tkFont
import socket

def processAddress(a):
   newStr = ""
   pieces = a.split('.')
   for piece in pieces:
      if piece=="0-255":
         newStr += '*'
      else:
         ranges = piece.split('-')
         if len(ranges) == 1 or ranges[0] == ranges[1]:
            newStr += ranges[0]
         else:
            newStr += ranges[0] + '-' + ranges[1]
      newStr += '.'
   newStr = newStr[0:-1]

   if newStr.find('-') == -1 and newStr.find('*') == -1:
      try:
         newStr = socket.gethostbyaddr(newStr)[0]
      except:
         pass
   
   return newStr
   

class CloseUpWindow:
   def __init__(self,name, groups):
      self.top = Tkinter.Toplevel()
      self.top.title(name)
      self.listbox = Tkinter.Listbox(self.top)
      self.listbox.pack(side=Tkinter.LEFT, fill=Tkinter.BOTH, expand=1)
      self.scroll = Tkinter.Scrollbar(self.top)
      self.listbox.config(yscrollcommand=self.scroll.set)
      self.scroll.config(command=self.listbox.yview)
      self.scroll.pack(side=Tkinter.LEFT, fill=Tkinter.Y)
      for g in groups:
         self.listbox.insert(Tkinter.END, processAddress(g))

class EQClassDisplay:
   def __init__(self):
      self.groups = {}
      self.colors = [(0,127,0), (20,14,135), (255,255,255)]
      self.top = Tkinter.Toplevel()
      self.top.title("ITVal Firewall Class Viewer")
      frame = Tkinter.Frame(self.top)
      frame.pack(side=Tkinter.LEFT)
      self.canvas = Tkinter.Canvas(frame, bg="#000000")
      self.canvas.configure(width=800, height=800)
      self.canvas.pack(side=Tkinter.TOP)
      self.canvas.bind('<Button-1>', self.DisplayCloseup)
      self.DrawGroups()

   def DisplayCloseup(self, event):
      ob = self.canvas.find_closest(event.x, event.y, halo=5)
      tagList = self.canvas.gettags(ob)
      for g in tagList:
         if self.groups.has_key(g):
            win = CloseUpWindow(g, self.groups[g])

   def ReverseColor(self, i):
      c = self.colors[i]
      color = (255-c[0], 255-c[1], 255-c[2])
      for val in color:
         if val > 110 and val < 144:
            return "#FFFFFF"

      return "#%02x%02x%02x" % (color[0], color[1], color[2])

   def GetColor(self,c, numGroups):
      loop = 0
   
      while numGroups > len(self.colors) and loop < 65536:
         loop += 1
         newColors = []
         for i in range(0, len(self.colors)-1):
            oldColor = self.colors[i]
            oldColor2 = self.colors[i+1]
            newColors += [oldColor]
            newColors += [((oldColor[0] + oldColor2[0])/2, (oldColor[1] + oldColor2[1])/2, (oldColor[2] + oldColor2[2])/2)]
         oldColor = self.colors[len(self.colors)-1]
         oldColor2 = self.colors[0]
         newColors += [oldColor]
         newColors += [((oldColor[0] + oldColor2[0])/2, (oldColor[1] + oldColor2[1])/2, (oldColor[2] + oldColor2[2])/2)]
         self.colors = newColors   
    
      if loop >= 65536:
         print "ERROR:  Ran out of colors!\n"
         return "#FFFFFF"
 
      color = self.colors[c] 
      return "#%02x%02x%02x" % (color[0], color[1], color[2])

   def DrawSmallGroup(self):
      f = tkFont.Font(family='sans', size=24)
      keys = self.groups.keys()
      numGroups = len(keys)
      if numGroups == 0:
         return
      if numGroups == 1:
         self.canvas.create_oval(200,150,600,550, fill="#0000FF", tag=keys[0])
         self.canvas.create_text(400,350, text=keys[0], font=f, fill = self.ReverseColor(0), tag=keys[0])
      else:
         self.canvas.create_oval(200,150,600,550, fill=self.GetColor(0,2), tag=keys[0])
         self.canvas.create_arc(200,150,600,550, fill=self.GetColor(1,2), tag=keys[1])
         self.canvas.create_text(300,350, text=keys[0], font=f, fill = self.ReverseColor(0), tag=keys[0])
         self.canvas.create_text(500,250, text=keys[1], font=f, fill = self.ReverseColor(1), tag=keys[1])
   
   def DrawGroups(self):
      keys = self.groups.keys()
      numGroups = len(keys)
      if numGroups < 3:
         self.DrawSmallGroup()
         return 
   
      i = 0
      for g in keys:
         angle2 = ((2.0*math.pi)/float(numGroups))*float(i+1)
         angle = ((2.0*math.pi)/float(numGroups))*float(i)
         xoffset = -int(200.0 * math.cos(angle))
         yoffset = int(200.0 * math.sin(angle))
         xoffset2 = -int(200.0 * math.cos(angle2))
         yoffset2 = int(200.0 * math.sin(angle2))
         self.canvas.create_polygon(400,350, 400 + xoffset, 350 + yoffset, 400 + xoffset2, 350+yoffset2, 400,350, fill = self.GetColor(i, numGroups), tag=keys[i])
         self.canvas.create_line(400,350, 400 + xoffset, 350 + yoffset, width=2, tag=keys[i])
         if i+1<numGroups:
            self.canvas.create_line(400,350, 400 + xoffset2, 350 + yoffset2, width=2, tag=keys[i+1])
         else:
            self.canvas.create_line(400,350, 400 + xoffset2, 350 + yoffset2, width=2, tag=keys[0])
         self.canvas.create_text((400 + (xoffset2 + xoffset)/3), (350 + (yoffset2 + yoffset)/3), text=keys[i], fill=self.ReverseColor(i), tag=keys[i])
         i = i + 1
   
   def AddGroup(self,name, addys):
      self.groups[name] = addys
