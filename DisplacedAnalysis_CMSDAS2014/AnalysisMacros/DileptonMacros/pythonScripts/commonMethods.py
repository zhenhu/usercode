from array import array
from ROOT import TColor, TLatex, gStyle

def set_palette(ncontours=999):
    """Set a color palette from a given RGB list
    stops, red, green and blue should all be lists of the same length
    see set_decent_colors for an example"""

    stops = [0.00, 0.34, 0.61, 0.84, 1.00]
    red   = [0.00, 0.00, 0.87, 1.00, 0.51]
    green = [0.00, 0.81, 1.00, 0.20, 0.00]
    blue  = [0.51, 1.00, 0.12, 0.00, 0.00]

    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)

    npoints = len(s)
    TColor.CreateGradientColorTable(npoints, s, r, g, b, ncontours)
    gStyle.SetNumberContours(ncontours)
    pass

def addChannelLatex(channel, x=0.2, y=0.75 ): 
  channelLatex = TLatex()
  channelLatex.SetNDC()
  if channel is '2muTrack':
      channelLatex.DrawLatex(x,y,"#mu^{+}#mu^{-}")
  elif channel is '2eTrack':
      channelLatex.DrawLatex(x,y,"e^{+}e^{-}")
      
def addCMSTitle(x=0.2,y=0.93):
    T1 = TLatex()
    T1.SetNDC()
    T1.DrawLatex(x,y,"#scale[0.9]{CMS Preliminary #sqrt{s} = 8 TeV}")   

def addFileLabel(file,x=0.6,y=0.75):
    T1 = TLatex()
    T1.SetNDC()
    if file.find('22Jan')>=0:
        T1.DrawLatex(x,y,"22Jan Rereco")  
    else:
        T1.DrawLatex(x,y,"Prompt Reco")  
        pass
    pass

def getLumi( muon = False ):
    lumiFile = "../LumiFiles/lumi_electron.txt"
    if muon :
        lumiFile = "../LumiFiles/lumi_muon.txt"
    else :
        lumiFile = "../LumiFiles/lumi_electron.txt"
    # Extract lumi from file
    openFile=open(lumiFile,"r")
    lumi=float(openFile.readline().strip())
    openFile.close()
    return lumi