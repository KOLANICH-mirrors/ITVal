#!/usr/bin/python
import Tkinter
import math
import tkFont
import sys
import ScrolledFWList
import FWSelectionPane

# Use a queue for message synchronation....

top = 0

inFile = 0
outFile = 0

if len(sys.argv)>2:
   outFile = open(sys.argv[2],'w')
   inFile = open(sys.argv[1],'r')
#   print "Reading from: ", inFile
#   print "Writing to: ", outFile
else:
   print "Pipe interface not opened"

def ReadString():
   global inFile
   if inFile != 0:
      print 'GUI Awaiting Read:'
      str = inFile.readline()
      print 'GUI Read:', str
      return str[0:-1]
   return 0

def WriteString(str):
   global outFile
   if outFile != 0:
      outFile.write(str)
      outFile.flush()
      return 1
   return 0

def ReadList():
   l = []
   str = ReadString()
   if str != 'BeginList':
      return None
   str = ReadString()
   while str != 'EndList':
      l += [str] 
      str = ReadString()
   return l 

def WriteList(l):
   WriteString("BeginList\n")
   for item in l:
      WriteString(str(item)+"\n")
   WriteString("EndList\n")

def addFilter():
   global list
   results = FWSelectionPane.GetResults()
   list.add(results)

def getClasses():
   global list
   WriteString("Get Classes\n")
   str = ReadString()
   if str != "Send Filter Names":
      print 'Error: unexpected reply to Get Classes\n'
   WriteList(list.filters)
   str = ReadString()
   if str != "Send NAT Names":
      print 'Error: unexpected reply to Get Classes\n'
   WriteList(list.nats)

def closeWindow():
   global top
   WriteString("QUIT\n")
   top.destroy()
   sys.exit(0)

def SetupScreen():
   global top
   global groups
   global statusBar
   global list
   top = Tkinter.Tk()
   top.title("ITVal Firewall Class Viewer")
   top.protocol('WM_DESTROY_WINDOW', closeWindow)
   topMenu = Tkinter.Menu(tearoff=0)
   fileMenu = Tkinter.Menu(tearoff=0)
   topMenu.add_cascade(label = "File", underline = 0, menu=fileMenu)
   fileMenu.add_command(label='Add Firewall', underline = 5, command = addFilter)
   fileMenu.add_command(label='Generate Classes', underline = 0, command = getClasses)
   fileMenu.add_command(label='Quit', underline = 0, command = closeWindow)
   list = ScrolledFWList.ScrolledFWList(top)
   list.pack()
   statusBar = Tkinter.Label(top,text='No Firewalls Selected', relief=Tkinter.SUNKEN)
   statusBar.pack(side=Tkinter.TOP, fill=Tkinter.X, expand=1)
   top.config(menu=topMenu)
   Tkinter.mainloop()

SetupScreen()
