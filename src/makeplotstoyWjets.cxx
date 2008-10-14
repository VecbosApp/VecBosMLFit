// macor to make usual plots from a set of Toys
void makeplotstoyWjets(TString dir = "./toys", TString file = "resultsW-1jet.dat", 
		       TString varfile = "variablesWjets.root", TString suffix = "1jet") {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  TH1D* N_sig_pull = new TH1D("N_sig_pull"," ",20, -4., 4.);
  TH1D* N_sig_err = new TH1D("N_sig_err"," ",50, 100, 300.);

  TH1D* N_zeeBkg_pull = new TH1D("N_zeeBkg_pull"," ",20, -4., 4.);
  TH1D* N_zeeBkg_err = new TH1D("N_zeeBkg_err"," ",400, 0., 150.);

  TH1D* N_ttbarBkg_pull = new TH1D("N_ttbarBkg_pull"," ",20, -4., 4.);
  TH1D* N_ttbarBkg_err = new TH1D("N_ttbarBkg_err"," ",400, 0., 150.);

  gStyle->SetOptFit(1111111);
  TTree* ntp = readtoy(dir,file,varfile);

  ntp->Project("N_sig_pull","(N_sig - N_siggen)/N_sigerr","covQual==3");
  ntp->Project("N_sig_err","N_sigerr","covQual==3");

  ntp->Project("N_zeeBkg_pull","(N_zeeBkg - N_zeeBkggen)/N_zeeBkgerr","covQual==3");
  ntp->Project("N_zeeBkg_err","N_zeeBkgerr","covQual==3");

  ntp->Project("N_ttbarBkg_pull","(N_ttbarBkg - N_ttbarBkggen)/N_ttbarBkgerr","covQual==3");
  ntp->Project("N_ttbarBkg_err","N_ttbarBkgerr","covQual==3");
 
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
  TString pullstring_sig("toy-plots/Wjets/N_sig_pull_");
  pullstring_sig.Append(suffix);
  pullstring_sig.Append(".eps");
  c1->SaveAs(pullstring_sig);

  N_zeeBkg_pull->Fit("gaus");
  N_zeeBkg_pull->GetXaxis()->SetTitle("Pull N_{Z bkg}");
  TString pullstring_zeeBkg("toy-plots/Wjets/N_zeeBkg_pull_");
  pullstring_zeeBkg.Append(suffix);
  pullstring_zeeBkg.Append(".eps");
  c1->SaveAs(pullstring_zeeBkg);

  N_ttbarBkg_pull->Fit("gaus");
  N_ttbarBkg_pull->GetXaxis()->SetTitle("Pull N_{tt bkg}");
  TString pullstring_ttbarBkg("toy-plots/Wjets/N_ttbarBkg_pull_");
  pullstring_ttbarBkg.Append(suffix);
  pullstring_ttbarBkg.Append(".eps");
  c1->SaveAs(pullstring_ttbarBkg);

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
  TString errstring_sig("toy-plots/Wjets/N_sig_err_");
  errstring_sig.Append(suffix);
  errstring_sig.Append(".eps");
  c2->SaveAs(errstring_sig);

  N_zeeBkg_err->GetXaxis()->SetTitle("#sigma(N_{Z bkg})");
  N_zeeBkg_err->Draw();
  TString errstring_zeeBkg("toy-plots/Wjets/N_zeeBkg_err_");
  errstring_zeeBkg.Append(suffix);
  errstring_zeeBkg.Append(".eps");
  c2->SaveAs(errstring_zeeBkg);

  N_ttbarBkg_err->GetXaxis()->SetTitle("#sigma(N_{tt bkg})");
  N_ttbarBkg_err->Draw();
  TString errstring_ttbarBkg("toy-plots/Wjets/N_ttbarBkg_err_");
  errstring_ttbarBkg.Append(suffix);
  errstring_ttbarBkg.Append(".eps");
  c2->SaveAs(errstring_ttbarBkg);

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
