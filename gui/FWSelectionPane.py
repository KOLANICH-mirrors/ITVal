import Tkinter
import tkFileDialog


class FWSelectionPane:
   def SetResults(self):
      fname = self.filterEntry.get()
      nname = self.NATEntry.get()
      tname = self.TopEntry.get()
      if fname == None or fname == "":
         fname = "NOFILTER"
      if nname == None or nname == "":
         nname = "NONAT"
      if tname == None or tname == "":
         tname = "NOTOP"
      self.results = (fname, nname, tname)
      self.top.destroy()

   def ClearResults(self):
      self.results = ("","")
      self.top.destroy()

   def __init__(self):
      self.results = ["NOFILTER","NONAT", "NOTOP"]
      self.top = Tkinter.Tk()
      self.frame1 = Tkinter.Frame(self.top)
      self.frame2 = Tkinter.Frame(self.top)
      self.frame3 = Tkinter.Frame(self.top)
      self.frame4 = Tkinter.Frame(self.top)

      filterLabel = Tkinter.Label(self.frame1, text='Filter File:')
      filterLabel.pack(side=Tkinter.LEFT)
      self.filterEntry = Tkinter.Entry(self.frame1)
      self.filterEntry.pack(side=Tkinter.LEFT)
      filterBrowse = Tkinter.Button(self.frame1, text="Browse", command=self.BrowseFilters)
      filterBrowse.pack(side=Tkinter.LEFT)
      self.frame1.pack(side=Tkinter.TOP)
      
      NATLabel = Tkinter.Label(self.frame2, text='NAT File:')
      NATLabel.pack(side=Tkinter.LEFT)
      self.NATEntry = Tkinter.Entry(self.frame2)
      self.NATEntry.pack(side=Tkinter.LEFT)
      NATBrowse = Tkinter.Button(self.frame2, text="Browse", command=self.BrowseNATs)
      NATBrowse.pack(side=Tkinter.LEFT)
      self.frame2.pack(side=Tkinter.TOP)
      
      TopLabel = Tkinter.Label(self.frame3, text='Topology File:')
      TopLabel.pack(side=Tkinter.LEFT)
      self.TopEntry = Tkinter.Entry(self.frame3)
      self.TopEntry.pack(side=Tkinter.LEFT)
      TopBrowse = Tkinter.Button(self.frame3, text="Browse", command=self.BrowseTops)
      TopBrowse.pack(side=Tkinter.LEFT)
      self.frame3.pack(side=Tkinter.TOP)

      OK = Tkinter.Button(self.frame4,text="OK", command=self.SetResults)
      OK.pack(side=Tkinter.LEFT)
      CANCEL = Tkinter.Button(self.frame4,text="Cancel", command=self.ClearResults)
      CANCEL.pack(side=Tkinter.LEFT)
      self.frame4.pack(side=Tkinter.TOP)

   def pack(self, **options):
      self.frame.pack(options)

   def destroy(self):
      self.filterLabel.destroy()
      self.NATLabel.destroy()
      self.topLabel.destroy()
      self.filterEntry.destroy()
      self.NATEntry.destroy()
      self.TopEntry.destroy()
      self.filterBrowse.destroy()
      self.NATBrowse.destroy()
      self.TopBrowse.destroy()
      self.frame.destroy()

   def BrowseFilters(self):
      fname = tkFileDialog.askopenfilename()
      self.filterEntry.insert(0, fname)

   def BrowseNATs(self):
      fname = tkFileDialog.askopenfilename()
      self.NATEntry.insert(0, fname)

   def BrowseTops(self):
      fname = tkFileDialog.askopenfilename()
      self.TopEntry.insert(0, fname)

def GetResults():
   f = FWSelectionPane()
   f.top.wait_window()
   return f.results
