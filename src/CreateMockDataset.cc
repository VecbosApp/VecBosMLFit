void CreateMockDataset() {
  
  TFile *fileW = TFile::Open("results/datasets/WJetsMADGRAPH_out-Wenu.root");
  RooDataSet *dataW = (RooDataSet*)fileW->Get("T1");
  fileW->Close();

  TFile *fileQCD = TFile::Open("results/datasets/QCD_out-Wenu.root");
  RooDataSet *dataQCD = (RooDataSet*)fileQCD->Get("T1");
  fileQCD->Close();

  TFile *fileOther = TFile::Open("results/datasets/other_out-Wenu.root");
  RooDataSet *dataOther = (RooDataSet*)fileOther->Get("T1");
  fileOther->Close();

  TFile *fileNew = TFile::Open("results/datasets/mockData_out-Wenu.root","recreate");
  RooDataSet mockdata(*dataW);
  mockdata.append(*dataQCD);
  mockdata.append(*dataOther);
  mockdata.Write();
  fileNew->Close();


}
