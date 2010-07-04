#include <vector>
#include <TString.h>
#include <TFile.h>
#include <RooFitResult.h>
#include <RooRealVar.h>
#include <RooArgList.h>

void writeTable(const char *dir, const char *ana = "Id") {

  std::vector<string> cuts;
  std::vector<TString> WPs;

  WPs.push_back("WP70");
  WPs.push_back("WP80");
  WPs.push_back("WP80modEE");
  WPs.push_back("WP95");

  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARLT1.479"); // EB
  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARLT1.479_AND_etaGT0"); // EB+
  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARLT1.479_AND_etaLT0"); // EB-

  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARGT1.479"); // EE
  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARGT1.479_AND_etaGT0"); // EE+
  cuts.push_back("nJetsEQ0_AND_pfmetOVERptGT0.3_AND_absOPPARetaCLPARGT1.479_AND_etaLT0"); // EE-
  
  std::vector<string> idCuts;
  idCuts.push_back("EB");
  idCuts.push_back("EB+");
  idCuts.push_back("EB-");
  idCuts.push_back("EE");
  idCuts.push_back("EE+");
  idCuts.push_back("EE-");

  cout << "\t NSIG \t EFF SIG \t NQCD \t EFF QCD " << endl;

  for(int iwp=0; iwp<(int)WPs.size(); ++iwp) {

    cout << "++++++++++  WP = " << WPs[iwp] << " +++++++++++" << endl;

    for(int icut=0; icut<(int)cuts.size(); ++ icut) {

      TString filename(dir);
      filename += TString("/");
      filename += TString("fitMinimumWCandleWithEff");
      filename += cuts[icut];
      filename += TString("is")+TString(ana);
      filename += WPs[iwp];
      filename += ".root";
      
      TFile *file = TFile::Open(filename.Data());
      RooFitResult *fitres = (RooFitResult*)file->Get("nll_myFit_T1");
      RooArgList floatPars = fitres->floatParsFinal();
      RooRealVar *N_sig = (RooRealVar*)floatPars.find("N_sig");
      RooRealVar *N_qcd = (RooRealVar*)floatPars.find("N_qcd");
      RooRealVar *eff_sig = (RooRealVar*)floatPars.find("eff_sig");
      RooRealVar *eff_qcd = (RooRealVar*)floatPars.find("eff_qcd");
      
      cout << idCuts[icut] 
           << "\t" << N_sig->getVal() << " +/- " << N_sig->getError()
           << "\t" << eff_sig->getVal() << " +/- " << eff_sig->getError() 
           << "\t" << N_qcd->getVal() << " +/- " << N_qcd->getError() 
           << "\t" << eff_qcd->getVal() << " +/- " << eff_qcd->getError() << endl;
    }
  }

}
