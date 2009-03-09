void makeplotstoyZjetsAll(TString dir, const char* jetflavour) {
  
  if(strcmp(jetflavour,"calojet")==0) {  
    makeplotstoyZjets(dir, "merged-results-Z1calojet.dat", "variablesZ-1calojet.root", "1jet" );
    makeplotstoyZjets(dir, "merged-results-Z2calojet.dat", "variablesZ-2calojet.root", "2jet" );
    makeplotstoyZjets(dir, "merged-results-Z3calojet.dat", "variablesZ-3calojet.root", "3jet" );
    makeplotstoyZjets(dir, "merged-results-Z4calojet.dat", "variablesZ-4calojet.root", "4jet" );
  } else if(strcmp(jetflavour,"trackjet")==0) {
    makeplotstoyZjets(dir, "merged-results-Z1trackjet.dat", "variablesZ-1trackjet.root", "1jet" );
    makeplotstoyZjets(dir, "merged-results-Z2trackjet.dat", "variablesZ-2trackjet.root", "2jet" );
    makeplotstoyZjets(dir, "merged-results-Z3trackjet.dat", "variablesZ-3trackjet.root", "3jet" );
    makeplotstoyZjets(dir, "merged-results-Z4trackjet.dat", "variablesZ-4trackjet.root", "4jet" );
  } else {
    cout << "unknown " << jetflavour << ". Exiting." << endl;
    return;
  }
}


// macor to make usual plots from a set of Toys
void makeplotstoyZjets(TString dir = "./toys", TString file = "resultsZ-1jet.dat", 
		       TString varfile = "variablesZjets.root", TString suffix = "1jet") {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  TH1D* N_sig_pull = new TH1D("N_sig_pull"," ",20, -4., 4.);
  TH1D* N_sig_err = new TH1D("N_sig_err"," ",30, 0., 20.);

  TH1D* N_bkg_pull = new TH1D("N_bkg_pull"," ",20, -4., 4.);
  TH1D* N_bkg_err = new TH1D("N_bkg_err"," ",30, 0., 20.);

  gStyle->SetOptFit(1111111);
  TTree* ntp = readtoy(dir,file,varfile);

  ntp->Project("N_sig_pull","(N_sig - N_siggen)/N_sigerr","covQual==3");
  ntp->Project("N_sig_err","N_sigerr","covQual==3");

  ntp->Project("N_bkg_pull","(N_bkg - N_bkggen)/N_bkgerr","covQual==3");
  ntp->Project("N_bkg_err","N_bkgerr","covQual==3");

 
  // pull distributions, fitted as Gaussians
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);

  N_sig_pull->Fit("gaus");
  N_sig_pull->GetXaxis()->SetTitle("Pull N_{sig}");
  TString pullstring(dir+"/N_sig_pull_");
  pullstring.Append(suffix);
  pullstring.Append(".eps");
  c1->SaveAs(pullstring);

  N_bkg_pull->Fit("gaus");
  N_bkg_pull->GetXaxis()->SetTitle("Pull N_{bkg}");
  TString pullstring(dir+"/N_bkg_pull_");
  pullstring.Append(suffix);
  pullstring.Append(".eps");
  c1->SaveAs(pullstring);

  // error distributions
  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  c2->SetFrameBorderMode(0);
  c2->SetFrameBorderMode(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(1111111);

  N_sig_err->GetXaxis()->SetTitle("#sigma(N_{sig})");
  N_sig_err->Draw();
  TString errstring(dir+"/N_sig_err_");
  errstring.Append(suffix);
  errstring.Append(".eps");
  c2->SaveAs(errstring);

  N_bkg_err->GetXaxis()->SetTitle("#sigma(N_{bkg})");
  N_bkg_err->Draw();
  TString errstring(dir+"/N_bkg_err_");
  errstring.Append(suffix);
  errstring.Append(".eps");
  c2->SaveAs(errstring);

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
  fitResData = RooDataSet::read(file, *variables);
  ntp = &fitResData->tree();
  f.Close();
  return ntp;
}
