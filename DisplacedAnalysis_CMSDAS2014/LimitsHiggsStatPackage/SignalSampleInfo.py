#/usr/bin/python
####################################################################
# Input info about signal samples from Kristian in convenient form
####################################################################

import sys
import os

#--- Define class with a few options that are the same for all signal masses.
class JobOptions:
   def __init__(self):
      
       # Specify if CLs or Bayesian limits are to be used.
       #self.limitMethod = "CLs"
       self.limitMethod = "Bayesian"

       # By default, limits are placed on H->XX, X->ll. However, if the following parameter is
       # set to True, then limits are placed on Squark --> Neutralino -> l+ l- nu
       # Where the code talks about Higgs and X masses, these should be interpreted as
       # Squark and Neutralino masses in this case.
       self.doNeutralinoLimits = False

       # Specify if wish to take into account that mass resolution & uncertainty on signal efficiency
       # vary as a function of lifetime. This requires a dedicated calculation of the limits at
       # each lifetime point, so takes x10 CPU.
       self.loopOverCTau = True

       # For limit calculation, specify a number that you are sure will be larger than the upper limit
       # on the expected number of events after all cuts. (If this is too small, limit will be calculated
       # incorrectly. If it is too large, then the limit will be imprecise).
       # (This parameter is only used for CLs method, not Bayesian).
       self.maxPredictedLimit = 20.
       
       # When calculating limits, if the irelative uncertainty on the efficiency exceed maxRelEffErr,
       # then it will be set equal to maxRelEffErr. This prevents the limit code crashing/failing.
       self.maxRelEffErr = 3.
       
       # When plotting limits, do not plot point for which the efficiency is below this cut or the
       # relative uncertainty on the efficiency exceeds this cut.
       self.minPlotEff = 0.000001
       self.maxPlotRelEffErr = 0.333

       # Expected limit quantiles to be used.
       self.fracs = (0.500, 0.840, 0.160, 0.975, 0.025)

   #--- Define function to return luminosity for all samples.
   def getLumi(self, lepton):
      lumi = {}
      lumi["Electrons"] = 19636  # /pb
      lumi["Muons"]     = 20532  # /pb
      return lumi[lepton]

   #--- Define function to return location of .txt files containing candidates passing all cuts.
   #--- This is needed only for the "counting" analysis.
   def getDataTxtFile(self, lepton):
      dataFile = "NONE"
      if lepton == "Muons":
        dataFile = "InputData2012/MassFiles/muons/Data_Mu_All_coll.txt"
      elif lepton == "Electrons":
        dataFile = "InputData2012/MassFiles/electrons/Data_Photon_All_coll.txt"
      if not os.path.exists(dataFile):
         sys.exit("ERROR: Input data file %s not found !"  %dataFile)
      return dataFile

   #--- Define function to return location of .root files containing histogram of mass spectrum in dacandidates passing all cuts.
   #--- This is needed only for the "mass resonance" analysis.
   def getDataRootFile(self, lepton):
      # N.B. This file is not needed unless backgrPdfOption = 3.
      dataFile = "NONE"
      if lepton == "Muons":
        dataFile = "InputData2012/BackgroundStudiesFiles/minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts_2muTrack_rereco_tiplipCorrected.root"
      elif lepton == "Electrons":
        dataFile = "InputData2012/BackgroundStudiesFiles/minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts_2eTrack_rereco__tiplipCorrected.root"
      if not os.path.exists(dataFile):
         sys.exit("ERROR: Input data file %s not found !"  %dataFile)
      return dataFile

#--- Define class to contain information for one signal mass sample.
class SignalSampleInfo:

   def __init__(self,
                MH_, MX_, ctau0_, acceptance_):
       #== All variables here of type {] allow one to access info for "Electrons" and "Muons".
       self.MH = MH_     # Higgs mass
       self.MX = MX_     # Long-lived exotic mass
       self.ctau0 = ctau0_  # Lifetime of exotic in generated MC sample
       self.acceptance = acceptance_ # 1 (2) if efficiencies are global (only within acceptance cuts).
       self.ctauScales = [] # List of factors by which MC signal lifetime will be scaled
       self.cTauScaleLoopValues = [] # Ditto, but of length 1 if no loop over lifetimes requested.
       self.ctaus = [] # List of effective lifetimes after scaling
       #
       self.effis        = {} # List of efficiencies (epsilon_1) for each effective lifetime
       self.effi_relerrs = {} # Corresponding relative uncertainty
       #
       #--- N.B. These parameter are only used by the "counting" analysis.
       self.effis_control = {} # Efficiency for signal to be selected and end up in background control region (e.g. -ve d0/sigma).
       self.bkg_relerr     = {} # Relative uncertainty on the background prediction
       self.bkg_relerr["Electrons"] = 0.08
       self.bkg_relerr["Muons"]     = 0.20
       #
       #--- N.B. All the following parameters are needed only for the "mass resonance" analysis.
       #--- N.B. For the "counting" analysis, the script reads the background estimate from the .txt files.
       #
       self.bkg         = {} # Predicted total background in mass spectrum
       self.bkg["Electrons"] = 0.65
       self.bkg["Muons"]     = 1.03
       self.bkg_err     = {} # Corresponding absolute uncertainty
       self.bkg_err["Electrons"] = 0.64
       self.bkg_err["Muons"]     = 1.24
       #
       self.widths      = {} # List of width of exotic resonance for each effective lifetime.
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
       self.backgrPdfOption  = 3 # Choice of background PDF
       self.setBackgrPdfParams(self.backgrPdfOption)

   def setCtauScales(self, ctauScales_):
      self.ctauScales = ctauScales_
      # Also create an array allowing one to loop or not over all ctau scales as desired. 
      jobOpt = JobOptions()
      if (jobOpt.loopOverCTau):
         self.cTauScaleLoopValues = self.ctauScales
      else:
         self.cTauScaleLoopValues = ["NoCTauLoop"]
      # List of effective lifetimes after scaling
      self.ctaus = [self.ctau0 * s for s in self.ctauScales] 


   def setWidths(self, Lepton, widths_):
      self.widths[Lepton] = widths_

   def setEffis(self, Lepton, effis_):
      self.effis        [Lepton] = effis_  

   def setEffiRelErrs(self, Lepton, effi_relerrs_):
      self.effi_relerrs [Lepton] = effi_relerrs_  

   def setEffisInControl(self, Lepton, effis_control_):
      self.effis_control[Lepton] = effis_control_  

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

      elif backgrPdfOption == 3:
         # Simply use histogram of mass spectrum from data with no lifetime cuts.
         # No free parameters in this case.
         pass

      else:
         sys.exit("ERROR: Unknown background option %i" %(backgrPdfOption) )

   #--- This function indicates that the MC statistics are sufficient to do a limit calculation
   def enoughMC(self, lepton, tIndex, loop = True):

      jobOpt = JobOptions()

      if loop:
         OK = self.effis[lepton][tIndex] > jobOpt.minPlotEff and self.effi_relerrs[lepton][tIndex] < jobOpt.maxPlotRelEffErr
#             and self.widths[lepton][tIndex] < 500 # Reject points with crazy mass resolution. -- Not needed for "counting" method.

      else:
         OK = False 
         for tInd in range(len(self.ctauScales)):
            if (self.enoughMC(lepton, tInd)):
               OK = True # If limit calculation not looping on lifetimes, OK if any one lifetime has enough statistics.
      return OK

   #--- This function returns the median relative uncertainty on the efficiency,
   #--- excluding lifetime points with insufficient MC statistics.
   def getMedianEffiRelErr(self, lepton):
      relerr = []
      # Store the relative efficiency for all time points with enough MC statistics.
      for tIndex in range(len(self.ctauScales)):
         if self.enoughMC(lepton, tIndex):
            relerr.append( self.effi_relerrs[lepton][tIndex] )

      relerr_median = sorted(relerr)[len(relerr)/2]
      return relerr_median

   #--- This function returns the median relative uncertainty on the signal mass resolution,
   #--- excluding lifetime points with insufficient MC statistics.
   def getMedianWidth(self, lepton):
      wid = []
      # Store the resolution for all time points with enough MC statistics.
      for tIndex in range(len(self.ctauScales)):
         if self.enoughMC(lepton, tIndex):
            wid.append   ( self.widths[lepton][tIndex] )

      wid_median    = sorted(wid)[len(wid)/2]
      return wid_median

#========= Some general utility functions, not related to above classes ============

#--- Define function to return information for all signal samples.
#--- Contains Higgs & X boson masses and X boson lifetime.
#--- Then contains efficiencies (with relative uncertainties) for each lepton species and lifetime.
#--- And the signal mass resolution for each lepton species and lifetime.
def getSignalSampleInfo():
   
   samples = []

   # Use the appropriate info, depending on whether efficiencies are to be divided by acceptance or not.
   # The files read in here should be produced from the output of parseEfficiencyFiles.pl 

   jobOpt = JobOptions()

   # This returns the directory where SignalSampleInfo.py is, just in case it is not the current one.
   dirScript =  os.path.dirname(os.path.abspath(__file__))

   if jobOpt.doNeutralinoLimits:

      execfile("%s/SignalSampleInfoEffi_Neutralino.py"  %(dirScript) )
      execfile("%s/SignalSampleInfoEffiOverAcc_Neutralino.py"  %(dirScript) )

   else:

      execfile("%s/SignalSampleInfoEffi.py"  %(dirScript) )
      execfile("%s/SignalSampleInfoEffiOverAcc.py"  %(dirScript) )

   return samples;

