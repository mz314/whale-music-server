from xml.etree.ElementTree import *
from xml.sax.saxutils import *

class program_settings(object): #na raze bardziej struktura niz klasa
  def __init__(self):
    self.activate_enqueue=False
    pass


class settings(program_settings):
    def __init__(self,fn="./settings.xml"):
        super(program_settings,self).__init__()
        self.loadFile(fn)
        self.parse()
        
    
    def loadFile(self,fn):
        print "Loading "+fn
        f=open('./settings.xml','r')
        self.data=f.read()
        f.close()
        #print self.data
    
    def getSetting(self,name):
        return self.settings.getiterator(name)[0].text
        
    def parse(self):
        self.tree=fromstring(self.data)
        settings=self.tree.getiterator('settings')
        self.settings=settings[0]
        