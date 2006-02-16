import Tkinter

class ScrolledFWList:
   def __init__(self, parent):
      self.filters = []
      self.nats = []
      self.tops = []
      self.widgets = []
      self.panel = Tkinter.Frame(parent)
      self.canvas = Tkinter.Canvas(self.panel)
      self.scrollbar = Tkinter.Scrollbar(self.panel)
      self.canvas.config(yscrollcommand=self.scrollbar.set)
      self.scrollbar.config(command=self.canvas.yview)
      self.canvas.config(scrollregion=self.canvas.bbox(Tkinter.ALL))

      self.canvas.pack(side=Tkinter.LEFT, expand=1)
      self.scrollbar.pack(side=Tkinter.LEFT, expand=1, fill=Tkinter.Y)

      self.panel.bind('<Expose>', self.draw)
      
   def pack(self, **options):
      self.panel.pack(options)

   def draw(self, event):
      for w in self.widgets:
         w.destroy()

      self.widgets = []
      i = 0
      for e in self.filters:
         n = self.nats[i]
         t = self.tops[i]
         w = FWWidget(self.canvas,e, n, t)
         w.pack(side=Tkinter.TOP)
         self.widgets += [w]
         i = i + 1

   def add(self, tup):
      (filter, NAT, Top) = tup
      self.filters += [filter]
      self.nats += [NAT]
      self.tops += [Top]
      self.draw("")

class FWWidget:
   def __init__(self, parent, filter, NAT, Top):
      self.frame = Tkinter.Frame(parent)
      self.filterLabel = Tkinter.Label(self.frame, text='Filter Filename:')
      self.filterLabel.pack(side=Tkinter.TOP)
      self.filterEntry = Tkinter.Entry(self.frame)
      self.filterEntry.insert(0,filter)
      self.filterEntry.config(state=Tkinter.DISABLED)
      self.filterEntry.pack(side=Tkinter.TOP)
      self.NATLabel = Tkinter.Label(self.frame, text='NAT Filename:')
      self.NATLabel.pack(side=Tkinter.TOP)
      self.NATEntry = Tkinter.Entry(self.frame)
      self.NATEntry.insert(0,NAT)
      self.NATEntry.config(state=Tkinter.DISABLED)
      self.NATEntry.pack(side=Tkinter.TOP)

      self.TopLabel = Tkinter.Label(self.frame, text='Topology Filename:')
      self.TopLabel.pack(side=Tkinter.TOP)
      self.TopEntry = Tkinter.Entry(self.frame)
      self.TopEntry.insert(0,Top)
      self.TopEntry.config(state=Tkinter.DISABLED)
      self.TopEntry.pack(side=Tkinter.TOP)

   def pack(self, **options):
      self.frame.pack(options)

   def destroy(self):
      self.filterLabel.destroy()
      self.NATLabel.destroy()
      self.TopLabel.destroy()
      self.filterEntry.destroy()
      self.NATEntry.destroy()
      self.TopEntry.destroy()
      self.frame.destroy()
