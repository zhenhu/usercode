#ifndef GETCATEGORY_H
#define GETCATEGORY_H

TString getCategory(const TString & dirName)
{
  // std::cout << "dirName = " << dirName << std::endl;
  TString fileName(dirName);
  if( std::string(fileName).find("/") != std::string::npos ) {
    fileName = std::string(dirName).substr(std::string(dirName).find_last_of("/")+1, std::string::npos);
  }

  if ( fileName.Contains("22Jan", TString::kIgnoreCase) ) cout << "String contains" << endl;

  if( fileName.BeginsWith("QCD") ) {
    if ( fileName.Contains("QCDem", TString::kIgnoreCase) || fileName.Contains("QCDmu", TString::kIgnoreCase) ) return "QCDenriched";
    else if ( fileName.Contains("BCToE", TString::kIgnoreCase ) ) return "QCDBCToE";
    else return "QCD";
  }
  else if( fileName.BeginsWith("ZZ") ) return "ZZ";
  else if( fileName.BeginsWith("WW") ) return "WW";
  else if( fileName.BeginsWith("WZ") ) return "WZ";
  else if( fileName.BeginsWith("WJets") ) return "WJets";
  else if( fileName.BeginsWith("TTJets") ) return "TTJets";
  else if( fileName.BeginsWith("Zee") ) return "Zee";
  else if( fileName.BeginsWith("Zmumu") ) return "Zmumu";
  else if( fileName.BeginsWith("Ztautau") ) return "Ztautau";
  else if( fileName.BeginsWith("DYJets") ) return "DYJets";
  else if( fileName.BeginsWith("Data") ) {
    if ( fileName.Contains("22Jan", TString::kIgnoreCase ) ) return "Data22Jan";
    else return "Data";
  }
  else if (fileName.BeginsWith("HTo2LongLived") || fileName.BeginsWith("Chi0ToNuLL")) return fileName.Remove(fileName.Index("_analysis"),fileName.Length());
  std::cout << "Unknown category for " << fileName.Data() << std::endl;
  return "";
}

#endif
