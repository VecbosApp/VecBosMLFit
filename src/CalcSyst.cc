#include <iostream>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <RooFitResult.h>
#include <RooRealVar.h>
#include <RooArgList.h>

using namespace std;

void CalcSyst(const char *prefix, int numFits) {

  TH1F *Delta_N_sig = new TH1F("Delta_N_sig","Delta_N_sig",20,-50,50);
  TH1F *Delta_eff_sig = new TH1F("Delta_eff_sig","Delta_eff_sig",20,-0.10,0.10);

  //  TFile *fileNominal = TFile::Open("fitres/WInclusive/fitMinimumWCandleWithEffnJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARLT1.479isIdWP80.root");
  TFile *fileNominal = TFile::Open("fitres/WInclusive/fitMinimumReco_EB.root");
  RooFitResult *fitresNom = (RooFitResult*)fileNominal->Get("fitresult_myFit_T1");
  RooArgList floatParsNom = fitresNom->floatParsFinal();
  RooRealVar *N_sig_nom = (RooRealVar*)floatParsNom.find("N_sig");
  RooRealVar *eff_sig_nom = (RooRealVar*)floatParsNom.find("eff_sig");

  cout << ">>>> Nominal fit <<<<" << endl;
  fitresNom->Print("V");

  for(int ifit=0; ifit<numFits; ++ifit) {

    char index[20];
    sprintf(index,"%d",ifit);

    TString filename(prefix);
    filename += TString(index);
    filename += ".root";
      
    TFile *file = TFile::Open(filename.Data());
    RooFitResult *fitres = (RooFitResult*)file->Get("nll_myFit_T1");
    RooArgList floatPars = fitres->floatParsFinal();
    RooRealVar *N_sig = (RooRealVar*)floatPars.find("N_sig");
    RooRealVar *eff_sig = (RooRealVar*)floatPars.find("eff_sig");

    Delta_N_sig->Fill(N_sig_nom->getVal()-N_sig->getVal());
    Delta_eff_sig->Fill(eff_sig_nom->getVal()-eff_sig->getVal());
    
  }

  TCanvas c1("c1","c1");
  Delta_N_sig->Draw();
  c1.SaveAs("Delta_N_sig.eps");

  Delta_eff_sig->Draw();
  c1.SaveAs("Delta_eff_sig.eps");


}
