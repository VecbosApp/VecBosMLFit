// macor to make usual plots from a set of Toys
void makeplotstoyWjets(TString dir = "./toys/output/", TString file = "resultsW.dat", 
		       TString varfile = "variablesW.root") {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  TH1D* N_sig_pull = new TH1D("N_sig_pull"," ",20, -4., 4.);
  TH1D* N_sig_err = new TH1D("N_sig_err"," ",50, 0, 60.);

  TH1D* N_ttbar_pull = new TH1D("N_qcd_pull"," ",20, -4., 4.);
  TH1D* N_ttbar_err = new TH1D("N_qcd_err"," ",400, 0., 150.);

  TH1D* N_other_pull = new TH1D("N_other_pull"," ",20, -4., 4.);
  TH1D* N_other_err = new TH1D("N_other_err"," ",400, 0., 150.);

  gStyle->SetOptFit(1111111);
  TTree* ntp = readtoy(dir,file,varfile);

  ntp->Project("N_sig_pull","(N_sig - N_siggen)/N_sigerr","covQual==3");
  ntp->Project("N_sig_err","N_sigerr","covQual==3");

  ntp->Project("N_qcd_pull","(N_qcd - N_qcdgen)/N_qcderr","covQual==3");
  ntp->Project("N_qcd_err","N_qcderr","covQual==3");

  ntp->Project("N_other_pull","(N_other - N_othergen)/N_othererr","covQual==3");
  ntp->Project("N_other_err","N_othererr","covQual==3");

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
  TString pullstring_sig(dir+"/N_sig_pull");
  pullstring_sig.Append(".C");
  c1->SaveAs(pullstring_sig);

  N_qcd_pull->Fit("gaus");
  N_qcd_pull->GetXaxis()->SetTitle("Pull N_{qcd}");
  TString pullstring_qcd(dir+"/N_qcd_pull");
  pullstring_qcd.Append(".eps");
  c1->SaveAs(pullstring_qcd);

  N_other_pull->Fit("gaus");
  N_other_pull->GetXaxis()->SetTitle("Pull N_{other}");
  TString pullstring_other(dir+"/N_other_pull");
  pullstring_other.Append(".eps");
  c1->SaveAs(pullstring_other);

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
  TString errstring_sig(dir+"/N_sig_err");
  errstring_sig.Append(".C");
  c2->SaveAs(errstring_sig);

  N_qcd_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  N_qcd_err->Draw();
  TString errstring_qcd(dir+"/N_qcd_err");
  errstring_qcd.Append(".eps");
  c2->SaveAs(errstring_qcd);

  N_other_err->GetXaxis()->SetTitle("#sigma(N_{tt})");
  N_other_err->Draw();
  TString errstring_other(dir+"/N_other_err");
  errstring_other.Append(".eps");
  c2->SaveAs(errstring_other);

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
