#!/usr/bin/python
import Tkinter
import math
import tkFont
import sys
import ScrolledFWList
import FWSelectionPane
import classes
import tkMessageBox

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
      str = inFile.readline()
      if str == None:
         return 0
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
   if str != 'Begin List':
      return None
   str = ReadString()
   while str != 'End List':
      l += [str] 
      str = ReadString()
   return l 

def WriteList(l):
   WriteString("Begin List\n")
   for item in l:
      WriteString(str(item)+"\n")
   WriteString("End List\n")

def addFilter():
   global list
   results = FWSelectionPane.GetResults()
   if results != None:
      list.add(results)

def getClasses():
   global list
   myClasses = {}
   if len(list.filters) == 0:
      return None
   if len(list.nats) == 0:
      return None
   if len(list.tops) == 0:
      return None

   WriteString("Get Classes\n")
   str = ReadString()
   if str != "Send Filter Names":
      print 'Error: unexpected reply to Get Classes at Send Filter\n'
      return None
      
   WriteList(list.filters)
   str = ReadString()
   if str != "Send NAT Names":
      if tkMessageBox.askokcancel(message='Filter file not found') == 0:
         return None
      return None
         
   WriteList(list.nats)

   str = ReadString()
   if str != "Send Topology Names":
      if tkMessageBox.askokcancel(message='NAT file not found') == 0:
         return None
      return None
   
   WriteList(list.tops)

   str = ReadString()
   if str != "Begin Classes":
      if tkMessageBox.askokcancel(message='Topology file not found: ' + str) == 0:
         return None
      return None

   name = ReadString() # Read Name
   while name != "End Classes":
      myClasses[name] = []
      str = ReadString()
      if str != "Begin Addresses":
         print 'Error: unexpected reply to Get Classes at Begin Addresses\n'
      addy = ReadString()

      while addy != 'End Addresses':
         myClasses[name] += [addy]
         addy = ReadString()

      name = ReadString() # Read Name
      
   return myClasses

def showClasses():
   eqClasses = getClasses()
   if eqClasses == None:
      tkMessageBox.askokcancel(message='File not found or no file specified.')
      return
   win = classes.EQClassDisplay()
   for t in eqClasses.keys():
      win.AddGroup(t, eqClasses[t])
   win.DrawGroups()
 

def closeWindow():
   global top
   try:
      WriteString("QUIT\n")
   except:
      pass
   try:
      top.destroy()
   except:
      pass
   sys.exit(0)

def SetupScreen():
   global top
   global groups
   global statusBar
   global list
   top = Tkinter.Tk()
   top.title("ITVal Firewall Class Viewer")
   top.protocol('WM_DELETE_WINDOW', closeWindow)
   topMenu = Tkinter.Menu(tearoff=0)
   fileMenu = Tkinter.Menu(tearoff=0)
   topMenu.add_cascade(label = "File", underline = 0, menu=fileMenu)
   fileMenu.add_command(label='Add Firewall', underline = 0, command = addFilter)
   fileMenu.add_command(label='Generate Classes', underline = 0, command = showClasses)
   fileMenu.add_command(label='Quit', underline = 0, command = closeWindow)
   list = ScrolledFWList.ScrolledFWList(top)
   list.pack()
   statusBar = Tkinter.Label(top,text='No Firewalls Selected', relief=Tkinter.SUNKEN)
   statusBar.pack(side=Tkinter.TOP, fill=Tkinter.X, expand=1)
   top.config(menu=topMenu)
   Tkinter.mainloop()

SetupScreen()
