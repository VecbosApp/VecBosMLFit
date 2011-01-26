// macor to make usual plots from a set of Toys
void makeplotstoySystWjets(TString dir = "./toys", TString file = "results.dat", 
		       TString varfile = "variables.root") {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  TH1D* N_sig_syst_1 = new TH1D("N_sig_syst_1"," ",50, -50, 50);
  TH1D* N_sig_syst_2 = new TH1D("N_sig_syst_2"," ",50, -50, 50);
  TH1D* N_sig_syst_3 = new TH1D("N_sig_syst_3"," ",50, -50, 50);
  TH1D* N_sig_syst_4 = new TH1D("N_sig_syst_4"," ",50, -50, 50);

  gStyle->SetOptStat(1111111);
  int nfits=0;
  TTree* ntp = readtoy(dir,file,varfile);

  ntp->Project("N_sig_syst_1","N_W_1j_1-N_W_1j_0","covQual_0==3 && covQual_1==3");
  ntp->Project("N_sig_syst_2","N_W_2j_1-N_W_2j_0","covQual_0==3 && covQual_1==3");
  ntp->Project("N_sig_syst_3","N_W_3j_1-N_W_3j_0","covQual_0==3 && covQual_1==3");
  ntp->Project("N_sig_syst_4","N_W_4j_1-N_W_4j_0","covQual_0==3 && covQual_1==3");

  // pull distributions, fitted as Gaussians
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

  N_sig_syst_1->Draw();
  N_sig_syst_1->GetXaxis()->SetTitle("#Delta N_{W+1jet}");
  c1->SaveAs("syst_Nsig_W1j.eps");

  N_sig_syst_2->Draw();
  N_sig_syst_2->GetXaxis()->SetTitle("#Delta N_{W+2jet}");
  c1->SaveAs("syst_Nsig_W2j.eps");

  N_sig_syst_3->Draw();
  N_sig_syst_3->GetXaxis()->SetTitle("#Delta N_{W+3jet}");
  c1->SaveAs("syst_Nsig_W3j.eps");

  N_sig_syst_4->Draw();
  N_sig_syst_4->GetXaxis()->SetTitle("#Delta N_{W+4jet}");
  c1->SaveAs("syst_Nsig_W4j.eps");

}

TTree *readtoy(const char* _dir, const char* _file="tmp.dat", const char* _varfile = "variables.root")
{ 

  RooDataSet *fitResData;
  TTree *ntp;

  TString dir(_dir);
  dir.Append("/");

  TString file(_file);
  file.Prepend(dir);

  TString varfile(_varfile);
  varfile.Prepend(dir);

  cout << "Reading data from:      " << file << endl;
  cout << "Reading variables from: " << varfile << endl;

  TFile f(varfile);

  RooArgSet *variables = (RooArgSet*)f.Get("variables");

  RooArgSet *errorVars = variables->selectByName("*");
  TIterator *it = errorVars->createIterator();
  RooRealVar *var;
  while (var = (RooRealVar*)it->Next()) {
    var->setRange(-10000000000,100000000000);
//     if(!(TString(var->GetName()).Contains("N_sig_"))) continue;
//     var->Print();
//     TString lastValue = TString(var->GetName()).Remove(0,6);
//     nFit = lastValue.Atoi();
  }

  fitResData = RooDataSet::read(file, *variables);
  ntp = &fitResData->tree();
  f.Close();

  TFile caccone("variablesTree.root","recreate");
  ntp->Write();
  caccone.Close();

  return ntp;
}
