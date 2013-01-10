void txt_to_root(const char *infileName, const char *outfileName) {
  std::ifstream infile;

  infile.open(infileName);

  TFile *outfile = new TFile(outfileName, "RECREATE");
  TH1F *f = new TH1F("mass", "Invariant mass of candidates", 1000, 0, 1000);
  f->Sumw2();

  float mass, lxy, weight;
  while (!infile.eof()) {
    infile >> mass >> lxy >> weight;
    if (!infile.eof())
      f->Fill(mass, weight);
  }
  f->Write();
  outfile->Close();
}
