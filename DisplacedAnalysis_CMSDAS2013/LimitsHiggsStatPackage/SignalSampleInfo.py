#/usr/bin/python
####################################################################
# Input info about signal samples from Kristian in convenient form
####################################################################

import sys
import os
from parseMassResolutions import *

#--- Define class to contain information for one sample
class SignalSampleInfo:

   def __init__(self,
                MH_, MX_, ctau0_):
       #== All variables here of type {] allow one to access info for "Electrons" and "Muons".
       self.MH = MH_     # Higgs mass
       self.MX = MX_     # Long-lived exotic mass
       self.ctau0 = ctau0_  # Lifetime of exotic in generated MC sample
       self.ctauScale = [0.033, 0.05, 0.1, 0.333, 0.5, 1., 2., 3., 10., 20., 30.] # List of scale factors for lifetime
       self.ctau = [self.ctau0 * s for s in self.ctauScale] # List of effective lifetimes after scaling
       #
       self.effi        = {} # List of efficiencies (epsilon_1) for each effective lifetime
       self.effi_relerr = {} # Corresponding relative uncertainty
       self.bkg         = {} # Predicted total background in mass spectrum
       self.bkg["Electrons"] = 1.42
       self.bkg["Muons"]     = 0.04
       self.bkg_err     = {} # Corresponding absolute uncertainty
       self.bkg_err["Electrons"] = 1.51
       self.bkg_err["Muons"]     = 1.79
       #
       self.width       = {} # List of width of exotic resonance for each effective lifetime.
       self.width       = parseMassResolutions("WinterSelection/massResolutions.txt", MH_, MX_, len(self.ctauScale) )
       #
       self.widthSys    = {} # Relative systematic uncertainty on exotic resonance width.
       self.widthSys["Electrons"] = 0.01  
       self.widthSys["Muons"]     = 0.01  
       #
       #--- Specify parameters of background mass PDF (aside from the gaussian representing the Z0 peak
       self.paramZ0Frac      = {} # Possible parameters of background PDF
       self.paramBWMean      = {}
       self.paramBWWidth     = {}
       self.paramTurnOn      = {}
       self.paramTurnOnWidth = {}
       #
       # This function assigns values to these background PDF parameters.
       self.backgrPdfOption  = 2 # Choice of background PDF
       self.setBackgrPdfParams(self.backgrPdfOption)
       #
       # Specify if wish to take into account that mass resolution & uncertainty on signal efficiency
       # vary as a function of lifetime. This requires a dedicated calculation of the limits at
       # each lifetime point, so takes x10 CPU.
       self.loopOverCTau = True
       if (self.loopOverCTau):
              self.cTauLoopValues = self.ctauScale
       else:
              self.cTauLoopValues = ["NoCTauLoop"]

       # For limit calculation, specify a number that you are sure will be larger than the upper limit
       # on the expected number of events after all cuts. (If this is too small, limit will be calculated
       # incorrectly. If it is too large, then the limit will be imprecise).
       self.maxPredictedLimit = 10.
       # When calculating limits, if the irelative uncertainty on the efficiency exceed maxRelEffErr,
       # then it will be set equal to maxRelEffErr. This prevents the limit code crashing/failing.
       self.maxRelEffErr = 3.
       # When plotting limits, do not plot point for which the efficiency is below this cut or the
       # relative uncertainty on the efficiency exceeds this cut.
       self.minPlotEff = 0.000001
       self.maxPlotRelEffErr = 0.5

   def set(self, Leptons, 
           effi_, effi_relerr_):
       self.effi       [Leptons] = effi_  
       self.effi_relerr[Leptons] = effi_relerr_  

   def setE(self,
            effi_, effi_relerr_):
       self.set("Electrons", effi_, effi_relerr_)

   def setM(self,
            effi_, effi_relerr_):
       self.set("Muons",     effi_, effi_relerr_)

   def setBackgrPdfParams(self, backgrPdfOption):
      self.backgrPdfOption = backgrPdfOption
      if backgrPdfOption == 1:
         # BW + Flat background PDF (do not use !)
         self.paramZ0Frac["Muons"] = 0.
         self.paramZ0Frac["Electrons"] = 0.
         self.paramBWMean["Muons"] = 0.
         self.paramBWMean["Electrons"] = 0.
         self.paramBWWidth["Muons"] = 0.
         self.paramBWWidth["Electrons"] = 0.

      elif backgrPdfOption == 2:
         # Gaussian * BW + Exponential background PDF
         self.paramZ0Frac["Muons"] = 0.961
         self.paramZ0Frac["Electrons"] = 0.868
         self.paramBWMean["Muons"] = 90.98
         self.paramBWMean["Electrons"] = 91.20
         self.paramBWWidth["Muons"] = 4.16
         self.paramBWWidth["Electrons"] = 4.24
         self.paramTurnOn["Muons"] =124.1
         self.paramTurnOn["Electrons"] = 120.8
         self.paramTurnOnWidth["Muons"] = 52.1
         self.paramTurnOnWidth["Electrons"] = 51.7

      else:
         sys.exit("ERROR: Unknown background option %i" %(backgrPdfOption) )

#--- Define function to return luminosity for all samples.
def getLumi(lepton):
   lumi = {}
   lumi["Electrons"] = 4085  # /pb
   lumi["Muons"]     = 5082  # /pb
   return lumi[lepton]

#--- Define function to return location of .txt files containing candidates passing all cuts.
def getDataFile(lepton):
   dataFile = "NONE"
   if lepton == "Muons":
     dataFile = "WinterSelection/masses_data_muon.txt"
   elif lepton == "Electrons":
     dataFile = "WinterSelection/masses_data_electron.txt"
   if not os.path.exists(dataFile):
      sys.exit("ERROR: Input data file %s not found !"  %dataFile)
   return dataFile

#--- Define function to return information for all samples.       
def getSignalSampleInfo():
   samples = []
   
   s = SignalSampleInfo(200, 20, 7)
   s.setE(
   [0.016046, 0.018773, 0.021586, 0.017802, 0.015167, 0.010424, 0.006176, 0.004098, 0.000740, 0.000220, 0.000104],
   [0.594481, 0.417365, 0.292253, 0.223326, 0.215693, 0.211034, 0.219063, 0.231775, 0.270706, 0.282843, 0.284206])
   s.setM(
   [0.162946, 0.137090, 0.118892, 0.101796, 0.092228, 0.068922, 0.045331, 0.032846, 0.007329, 0.002310, 0.001112],
   [0.370247, 0.293997, 0.227492, 0.203881, 0.202440, 0.201681, 0.204064, 0.210017, 0.235552, 0.244529, 0.247965])
   samples.append(s)

   s = SignalSampleInfo(200, 50, 20)
   s.setE(
   [0.007515, 0.012672, 0.017014, 0.011033, 0.008600, 0.005279, 0.003045, 0.002111, 0.000450, 0.000141, 0.000068],
   [0.467917, 0.390491, 0.308438, 0.240719, 0.229100, 0.221213, 0.248872, 0.311814, 0.495491, 0.541811, 0.552198])
   s.setM(
   [0.055000, 0.071471, 0.095113, 0.090920, 0.079138, 0.054616, 0.033069, 0.023425, 0.005511, 0.001797, 0.000877],
   [0.424086, 0.295158, 0.225357, 0.204578, 0.203057, 0.202182, 0.206434, 0.226093, 0.354644, 0.402171, 0.419101])
   samples.append(s)

   s = SignalSampleInfo(120, 20, 13)
   s.setE(
   [0.000163, 0.000969, 0.003845, 0.003805, 0.002944, 0.001738, 0.000842, 0.000490, 0.000067, 0.000019, 0.000009],
   [0.524307, 0.460553, 0.392603, 0.308150, 0.282411, 0.260833, 0.273437, 0.287205, 0.311494, 0.330533, 0.298969])
   s.setM(
   [0.021684, 0.024885, 0.023676, 0.015122, 0.012258, 0.007735, 0.004751, 0.003515, 0.000877, 0.000286, 0.000140],
   [0.579509, 0.439181, 0.314386, 0.229171, 0.220189, 0.214703, 0.244598, 0.320656, 0.535871, 0.587536, 0.605418])
   samples.append(s)

   s = SignalSampleInfo(120, 50, 50)
   s.setE(
   [0.001099, 0.001577, 0.001331, 0.000582, 0.000463, 0.000294, 0.000139, 0.000078, 0.000010, 0.000003, 0.000001],
   [1.019804, 1.018560, 0.974905, 0.564134, 0.466241, 0.433276, 0.462721, 0.479590, 0.538516, 0.388730, 1.019804])
   s.setM(
   [0.031114, 0.020570, 0.011479, 0.006587, 0.005174, 0.003024, 0.001527, 0.000931, 0.000143, 0.000041, 0.000019],
   [0.816978, 0.687674, 0.453802, 0.257657, 0.243539, 0.234458, 0.248418, 0.267227, 0.310694, 0.315418, 0.330533])
   samples.append(s)

   s = SignalSampleInfo(1000, 20, 1.5)
   s.setE(
   [0.111764, 0.149827, 0.185541, 0.178585, 0.163170, 0.125502, 0.080554, 0.055892, 0.011361, 0.003507, 0.001677],
   [0.260661, 0.236737, 0.213567, 0.202318, 0.201460, 0.201008, 0.201982, 0.204667, 0.222127, 0.230379, 0.233780])
   s.setM(
   [0.005064, 0.006800, 0.009764, 0.012797, 0.012682, 0.011575, 0.010008, 0.009010, 0.003470, 0.001271, 0.000645],
   [0.875250, 0.677544, 0.367469, 0.226263, 0.215981, 0.209891, 0.237506, 0.335052, 0.622076, 0.684474, 0.703449])
   samples.append(s)

   s = SignalSampleInfo(1000, 50, 4)
   s.setE(
   [0.176849, 0.208673, 0.251375, 0.261354, 0.243203, 0.189219, 0.123220, 0.087574, 0.019409, 0.006173, 0.002985],
   [0.288467, 0.240325, 0.210588, 0.201483, 0.200919, 0.200617, 0.201501, 0.204836, 0.231895, 0.245324, 0.250655])
   s.setM(
   [0.234974, 0.293654, 0.353657, 0.351881, 0.324869, 0.252158, 0.170729, 0.131027, 0.040626, 0.014571, 0.007360],
   [0.248590, 0.224616, 0.207438, 0.201122, 0.200702, 0.200477, 0.202214, 0.217905, 0.378376, 0.438922, 0.459773])
   samples.append(s)

   s = SignalSampleInfo(1000, 150, 10)
   s.setE(
   [0.378880, 0.369663, 0.338285, 0.271698, 0.236055, 0.165896, 0.104798, 0.079029, 0.024301, 0.008696, 0.004388],
   [0.258510, 0.231546, 0.210272, 0.201573, 0.201021, 0.200711, 0.203707, 0.229558, 0.435570, 0.502635, 0.525002])
   s.setM(
   [0.511040, 0.523601, 0.523448, 0.485207, 0.448114, 0.346177, 0.225414, 0.160142, 0.035201, 0.011147, 0.005381],
   [0.243280, 0.220958, 0.206083, 0.200845, 0.200530, 0.200366, 0.200825, 0.202417, 0.213900, 0.219382, 0.221480])
   samples.append(s)

   s = SignalSampleInfo(1000, 350, 35)
   s.setE(
   [0.308821, 0.316729, 0.293390, 0.189999, 0.150708, 0.092830, 0.051308, 0.033598, 0.006153, 0.001845, 0.000874],
   [0.262854, 0.233237, 0.211527, 0.202469, 0.201726, 0.201274, 0.202517, 0.205353, 0.218278, 0.223244, 0.224953])
   s.setM(
   [0.616752, 0.602647, 0.561201, 0.434675, 0.369319, 0.248799, 0.145625, 0.098012, 0.019033, 0.005806, 0.002766],
   [0.237067, 0.219334, 0.205849, 0.200970, 0.200642, 0.200456, 0.200922, 0.202116, 0.208641, 0.211533, 0.212669])
   samples.append(s)

   s = SignalSampleInfo(125, 20, 13)
   s.setE(
   [0.002405, 0.002412, 0.002420, 0.001376, 0.001226, 0.000899, 0.000545, 0.000361, 0.000081, 0.000026, 0.000012],
   [0.283726, 0.251299, 0.233153, 0.315637, 0.285625, 0.262611, 0.286761, 0.323956, 0.779191, 0.794806, 0.856997])
   s.setM(
   [0.017178, 0.017438, 0.016919, 0.014100, 0.011634, 0.007568, 0.005161, 0.004912, 0.001328, 0.000498, 0.000257],
   [0.215836, 0.209050, 0.205392, 0.218998, 0.212839, 0.209187, 0.265731, 0.459857, 0.283589, 0.286271, 0.287279])
   samples.append(s)

   s = SignalSampleInfo(125, 50, 50)
   s.setE(
   [0.001226, 0.001506, 0.001522, 0.000320, 0.000265, 0.000131, 0.000047, 0.000024, 0.000133, 0.000061, 0.000034],
   [0.287377, 0.254902, 0.240760, 0.761122, 0.686388, 0.635353, 0.628420, 0.616667, 0.619631, 0.701256, 0.733669])
   s.setM(
   [0.012660, 0.012051, 0.010722, 0.007330, 0.005579, 0.003081, 0.001428, 0.000823, 0.000407, 0.000183, 0.000102],
   [0.217372, 0.210599, 0.206543, 0.261774, 0.247248, 0.237389, 0.245781, 0.255610, 0.383127, 0.421990, 0.440212])
   samples.append(s)

   s = SignalSampleInfo(400, 20, 4)
   s.setE(
   [0.163302, 0.155446, 0.134034, 0.110492, 0.101619, 0.077538, 0.047367, 0.031348, 0.005578, 0.001649, 0.000777],
   [0.329280, 0.274221, 0.226373, 0.203660, 0.202221, 0.201519, 0.202465, 0.204215, 0.211342, 0.214099, 0.214857])
   s.setM(
   [0.186904, 0.181736, 0.180939, 0.183830, 0.172815, 0.136474, 0.092430, 0.068034, 0.016126, 0.005198, 0.002524],
   [0.306377, 0.259511, 0.217122, 0.202058, 0.201260, 0.200849, 0.202299, 0.207293, 0.237717, 0.250266, 0.254931])
   samples.append(s)

   s = SignalSampleInfo(400, 50, 8)
   s.setE(
   [0.147084, 0.154834, 0.147713, 0.121492, 0.108790, 0.080537, 0.051397, 0.036003, 0.007442, 0.002300, 0.001100],
   [0.293591, 0.254953, 0.220676, 0.203219, 0.202018, 0.201382, 0.202914, 0.206711, 0.224809, 0.231907, 0.234653])
   s.setM(
   [0.364972, 0.365130, 0.363287, 0.332747, 0.307040, 0.240198, 0.162004, 0.117098, 0.025903, 0.008163, 0.003931],
   [0.255225, 0.227606, 0.208167, 0.201173, 0.200728, 0.200493, 0.201111, 0.202826, 0.212500, 0.216702, 0.218205])
   samples.append(s)

   s = SignalSampleInfo(400, 150, 40)
   s.setE(
   [0.191529, 0.176504, 0.151638, 0.090735, 0.070148, 0.042260, 0.024478, 0.017051, 0.003758, 0.001196, 0.000579],
   [0.347239, 0.275614, 0.224373, 0.205432, 0.203858, 0.202819, 0.207271, 0.222232, 0.312018, 0.346902, 0.359550])
   s.setM(
   [0.340011, 0.373725, 0.393889, 0.315859, 0.266319, 0.177798, 0.104569, 0.071496, 0.014884, 0.004663, 0.002243],
   [0.256399, 0.226407, 0.207780, 0.201405, 0.200949, 0.200683, 0.201606, 0.205210, 0.235832, 0.251104, 0.257276])
   samples.append(s)

   return samples
