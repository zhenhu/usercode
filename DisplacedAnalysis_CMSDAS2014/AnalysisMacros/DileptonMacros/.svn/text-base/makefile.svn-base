CC=g++
CFLAGS=-c -g -Wall `root-config --cflags`
LDFLAGS=`root-config --glibs`
COMMONMACRODIR=../CommonMacros/
INCDIR=-I/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src
TREEDIR=../../TreeProducer/TreeProducer/
OBJECTS=fullAnalyzer.o DileptonAnalyzer.o PileupReweighting.o treeAnalyzerBase.o DileptonAnalysisCuts.o Histograms.o libMyLib.so
HEADERS = $(TREEDIR)/interface/Candidates.h $(TREEDIR)/interface/TreeLepton.h $(TREEDIR)/interface/TreeDipseudoLeptonCandidate.h

all : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o main 

fullAnalyzer.o : fullAnalyzer.C DileptonAnalyzer.h $(COMMONMACRODIR)/treeAnalyzerBase.h $(COMMONMACRODIR)/FilesAndWeights.h $(COMMONMACRODIR)/GetCategory.h $(COMMONMACRODIR)/analysisType.h
	$(CC) $(CFLAGS) $(INCDIR) fullAnalyzer.C

DileptonAnalyzer.o : DileptonAnalyzer.h DileptonAnalyzer.C $(COMMONMACRODIR)/treeAnalyzerBase.h DileptonAnalysisCuts.h DileptonAnalysisCuts.C Histograms.h Histograms.C $(TREEDIR)/interface/Candidates.h  $(TREEDIR)/interface/TreeLepton.h $(TREEDIR)/interface/TreeDipseudoLeptonCandidate.h
	$(CC) $(CFLAGS) $(INCDIR) DileptonAnalyzer.C

treeAnalyzerBase.o : $(COMMONMACRODIR)/treeAnalyzerBase.h $(COMMONMACRODIR)/treeAnalyzerBase.C $(COMMONMACRODIR)/PileupReweighting.h $(COMMONMACRODIR)/analysisType.h $(TREEDIR)/interface/Candidates.h $(TREEDIR)/interface/TreeLepton.h $(TREEDIR)/interface/TreeDipseudoLeptonCandidate.h
	$(CC) $(CFLAGS) $(INCDIR) $(COMMONMACRODIR)/treeAnalyzerBase.C

PileupReweighting.o : $(COMMONMACRODIR)/PileupReweighting.h $(COMMONMACRODIR)/PileupReweighting.C
	$(CC) $(CFLAGS) $(INCDIR) $(COMMONMACRODIR)/PileupReweighting.C

DileptonAnalysisCuts.o : DileptonAnalysisCuts.C DileptonAnalysisCuts.h $(COMMONMACRODIR)/treeAnalyzerBase.h
	$(CC) $(CFLAGS) $(INCDIR) DileptonAnalysisCuts.C

Histograms.o : Histograms.C Histograms.h
	$(CC) $(CFLAGS) $(INCDIR) Histograms.C
	
MyDict.cxx: $(HEADERS) $(TREEDIR)/src/LinkDef.h
	rootcint -f $@ $(CFLAGS) $(INCDIR) -p $^
 
libMyLib.so: MyDict.cxx MyDict.h $(HEADERS) $(TREEDIR)/src/LinkDef.h
	$(CC) $(CFLAGS) $(INCDIR) MyDict.cxx -o libMyLib.so 
	
clean:
	rm ./*.o ./main
