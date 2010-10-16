void makeplotstoyWjets(TString dir = "./toys", TString file = "resultsW.dat", 
		       TString varfile = "variablesWjets.root", int njetmin, int njetmax) {

  gROOT->SetStyle("Plain");
  // do not display any of the standard histogram decorations
  gStyle->SetOptTitle(0);

  gStyle->SetOptFit(1111111);
  TTree* ntp = readtoy(dir,file,varfile);

  TH1D* N_sig_pull[10], N_sig_err[10], 
    N_qcd_pull[10], N_qcd_err[10],
    N_other_pull[10], N_other_err[10];

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

  char pullstring[50], errstring[50];
  char var[200];
  for(int nj=njetmin; nj<njetmax; nj++) {
    sprintf(pullstring,"N_sig_pull_%dj",nj);
    sprintf(errstring,"N_sig_err_%dj",nj);
    N_sig_pull[nj] = new TH1D(pullstring,pullstring, 20, -4.0, 4.0);
    N_sig_err[nj] = new TH1D(errstring,errstring, 50, 0.0, 100.);

    cout << "nj = " << nj << endl; 

    sprintf(var, "(N_Wincl%dj_0 - N_Wincl%djgen)/N_Wincl%djerr_0", nj, nj, nj);
    ntp->Project(pullstring, var, "covQual_0==3");

    sprintf(var, "N_Wincl%djerr_0", nj);
    ntp->Project(errstring, var, "covQual_0==3");

    // pulls
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);

    N_sig_pull[nj]->Fit("gaus");
    N_sig_pull[nj]->GetXaxis()->SetTitle("Pull N_{sig}");

    char epsfile[200];
    sprintf(epsfile,"%s/N_sig_pull_%dj.eps",dir.Data(),nj);
    c1->SaveAs(epsfile);

    // errors
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(1111111);

    N_sig_err[nj]->GetXaxis()->SetTitle("#sigma_{N_{sig}}");
    N_sig_err[nj]->Draw();

    sprintf(epsfile,"%s/N_sig_err_%dj.eps",dir.Data(),nj);
    c1->SaveAs(epsfile);
    
  }

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
  }

  fitResData = RooDataSet::read(file, *variables);
  ntp = &fitResData->tree();
  f.Close();
  return ntp;
}
