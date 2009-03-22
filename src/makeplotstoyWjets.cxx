void makeplotstoyWjetsAll(TString dir, const char* jetflavour) {
  
  if(strcmp(jetflavour,"calojet")==0) {  
    makeplotstoyWjets(dir, "merged-results-W1calojet.dat", "variablesW-1calojet.root", "1jet" );
    makeplotstoyWjets(dir, "merged-results-W2calojet.dat", "variablesW-2calojet.root", "2jet" );
    makeplotstoyWjets(dir, "merged-results-W3calojet.dat", "variablesW-3calojet.root", "3jet" );
    makeplotstoyWjets(dir, "merged-results-W4calojet.dat", "variablesW-4calojet.root", "4jet" );
  } else if(strcmp(jetflavour,"trackjet")==0) {
    makeplotstoyWjets(dir, "merged-results-W1trackjet.dat", "variablesW-1trackjet.root", "1jet" );
    makeplotstoyWjets(dir, "merged-results-W2trackjet.dat", "variablesW-2trackjet.root", "2jet" );
    makeplotstoyWjets(dir, "merged-results-W3trackjet.dat", "variablesW-3trackjet.root", "3jet" );
    makeplotstoyWjets(dir, "merged-results-W4trackjet.dat", "variablesW-4trackjet.root", "4jet" );
  } else {
    cout << "unknown " << jetflavour << ". Exiting." << endl;
    return;
  }
}

// macor to make usual plots from a set of Toys
void makeplotstoyWjets(TString dir = "./toys", TString file = "resultsW-1jet.dat", 
		       TString varfile = "variablesWjets.root", TString suffix = "1jet") {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  TH1D* N_sig_pull = new TH1D("N_sig_pull"," ",20, -4., 4.);
  TH1D* N_sig_err = new TH1D("N_sig_err"," ",50, 0, 550.);

  TH1D* eff_sig_pull = new TH1D("eff_sig_pull"," ",20, -4., 4.);
  TH1D* eff_sig_err = new TH1D("eff_sig_err"," ",50, 0, 5.);

  TH1D* N_ttbar_pull = new TH1D("N_ttbar_pull"," ",20, -4., 4.);
  TH1D* N_ttbar_err = new TH1D("N_ttbar_err"," ",400, 0., 150.);

  TH1D* eff_ttbar_pull = new TH1D("eff_ttbar_pull"," ",20, -4., 4.);
  TH1D* eff_ttbar_err = new TH1D("eff_ttbar_err"," ",400, 0., 150.);

  TH1D* N_other_pull = new TH1D("N_other_pull"," ",20, -4., 4.);
  TH1D* N_other_err = new TH1D("N_other_err"," ",400, 0., 150.);

  TH1D* eff_other_pull = new TH1D("eff_other_pull"," ",20, -4., 4.);
  TH1D* eff_other_err = new TH1D("eff_other_err"," ",400, 0., 150.);

  gStyle->SetOptFit(1111111);
  TTree* ntp = readtoy(dir,file,varfile);

  ntp->Project("N_sig_pull","(N_sig - N_siggen)/N_sigerr","covQual==3");
  ntp->Project("N_sig_err","N_sigerr","covQual==3");

  ntp->Project("eff_sig_pull","(eff_sig - eff_siggen)/eff_sigerr","covQual==3");
  ntp->Project("eff_sig_err","eff_sigerr","covQual==3");

  ntp->Project("N_ttbar_pull","(N_ttbar - N_ttbargen)/N_ttbarerr","covQual==3");
  ntp->Project("N_ttbar_err","N_ttbarerr","covQual==3");

  ntp->Project("eff_ttbar_pull","(eff_ttbar - eff_ttbargen)/eff_ttbarerr","covQual==3");
  ntp->Project("eff_ttbar_err","eff_ttbarerr","covQual==3");

  ntp->Project("N_other_pull","(N_other - N_othergen)/N_othererr","covQual==3");
  ntp->Project("N_other_err","N_othererr","covQual==3");

  ntp->Project("eff_other_pull","(eff_other - eff_othergen)/eff_othererr","covQual==3");
  ntp->Project("eff_other_err","eff_othererr","covQual==3");

 
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
  TString pullstring_sig(dir+"/N_sig_pull_");
  pullstring_sig.Append(suffix);
  pullstring_sig.Append(".eps");
  c1->SaveAs(pullstring_sig);

  eff_sig_pull->Fit("gaus");
  eff_sig_pull->GetXaxis()->SetTitle("Pull N_{eff_sig}");
  TString pullstring_eff_sig(dir+"/eff_sig_pull_");
  pullstring_eff_sig.Append(suffix);
  pullstring_eff_sig.Append(".eps");
  c1->SaveAs(pullstring_eff_sig);

  N_ttbar_pull->Fit("gaus");
  N_ttbar_pull->GetXaxis()->SetTitle("Pull N_{tt bkg}");
  TString pullstring_ttbar(dir+"/N_ttbar_pull_");
  pullstring_ttbar.Append(suffix);
  pullstring_ttbar.Append(".eps");
  c1->SaveAs(pullstring_ttbar);

  eff_ttbar_pull->Fit("gaus");
  eff_ttbar_pull->GetXaxis()->SetTitle("Pull N_{tt bkg}");
  TString pullstring_eff_ttbar(dir+"/eff_ttbar_pull_");
  pullstring_eff_ttbar.Append(suffix);
  pullstring_eff_ttbar.Append(".eps");
  c1->SaveAs(pullstring_eff_ttbar);

  N_other_pull->Fit("gaus");
  N_other_pull->GetXaxis()->SetTitle("Pull N_{other}");
  TString pullstring_other(dir+"/N_other_pull_");
  pullstring_other.Append(suffix);
  pullstring_other.Append(".eps");
  c1->SaveAs(pullstring_other);

  eff_other_pull->Fit("gaus");
  eff_other_pull->GetXaxis()->SetTitle("Pull N_{eff_other}");
  TString pullstring_eff_other(dir+"/eff_other_pull_");
  pullstring_eff_other.Append(suffix);
  pullstring_eff_other.Append(".eps");
  c1->SaveAs(pullstring_eff_other);

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
  TString errstring_sig(dir+"/N_sig_err_");
  errstring_sig.Append(suffix);
  errstring_sig.Append(".eps");
  c2->SaveAs(errstring_sig);

  eff_sig_err->GetXaxis()->SetTitle("#eff_sigma(N_{eff_sig})");
  eff_sig_err->Draw();
  TString errstring_eff_sig(dir+"/eff_sig_err_");
  errstring_eff_sig.Append(suffix);
  errstring_eff_sig.Append(".eps");
  c2->SaveAs(errstring_eff_sig);

  N_ttbar_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  N_ttbar_err->Draw();
  TString errstring_ttbar(dir+"/N_ttbar_err_");
  errstring_ttbar.Append(suffix);
  errstring_ttbar.Append(".eps");
  c2->SaveAs(errstring_ttbar);

  eff_ttbar_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  eff_ttbar_err->Draw();
  TString errstring_eff_ttbar(dir+"/eff_ttbar_err_");
  errstring_eff_ttbar.Append(suffix);
  errstring_eff_ttbar.Append(".eps");
  c2->SaveAs(errstring_eff_ttbar);

  N_other_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  N_other_err->Draw();
  TString errstring_other(dir+"/N_other_err_");
  errstring_other.Append(suffix);
  errstring_other.Append(".eps");
  c2->SaveAs(errstring_other);

  eff_other_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  eff_other_err->Draw();
  TString errstring_eff_other(dir+"/eff_other_err_");
  errstring_eff_other.Append(suffix);
  errstring_eff_other.Append(".eps");
  c2->SaveAs(errstring_eff_other);

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
