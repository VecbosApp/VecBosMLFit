// =============================
// in a ROOT session, do:
// .L src/PrintPdfTables.cc++
// printLatex()
// =============================
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <pair.h>

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include <RooFitResult.h>
#include <RooArgList.h>
#include <RooRealVar.h>

using namespace std;

//! methods declaration
void printLatex();

void printPdfTablesZ(const char *jetflavour);
void printPdfTablesW(const char *jetflavour);
std::pair<float, float> getParameterVal(RooFitResult *fitres, const char *name);


void printLatex() {

  cout << "\n\n\n %%% printing latex tables of the fit PDFs %%% \n\n\n" << endl;

  cout << "printing tables for Z->ee + calojets..." << endl;
  printPdfTablesZ("calojet");
  cout << "Done." << endl;

  cout << "printing tables for Z->ee + trackjets..." << endl;
  printPdfTablesZ("trackjet");
  cout << "Done." << endl;

  cout << "printing tables for W->enu + calojets..." << endl;
  printPdfTablesW("calojet");
  cout << "Done." << endl;

  cout << "printing tables for W->enu + trackjets..." << endl;
  printPdfTablesW("trackjet");
  cout << "Done." << endl;

  cout << "\n\n %%% I am very done. " << endl;

}

void printPdfTablesZ(const char *jetflavour) {

  char nametextfile[200];
  sprintf(nametextfile,"pdfParameters_Zee_%s.tex",jetflavour);

  ofstream textfile;
  textfile.open(nametextfile, ios_base::trunc);
  textfile.precision(2);

  textfile << "\\documentclass{article}" << endl;
  textfile << "\\begin{document}" << endl;

  textfile << "\n\n\n\n" << endl;

  // ==============
  // signal PDFs
  // ==============

  textfile << "% ===== SIGNAL Z->EE PDFS PARAMETERS ==== %" << endl; 
  textfile << "\n\n\n\n" << endl;

  // mee Cruijff
  textfile << "% SIGNAL MEE CRUIJFF\n" << endl;
  vector<string> params_sig_mass;
  params_sig_mass.push_back("sig_Mass_mean");
  params_sig_mass.push_back("sig_Mass_sigmaL");
  params_sig_mass.push_back("sig_Mass_sigmaR");
  params_sig_mass.push_back("sig_Mass_alphaL");
  params_sig_mass.push_back("sig_Mass_alphaR");

  vector<string> params_sig_mass_name;
  params_sig_mass_name.push_back("$mean$");
  params_sig_mass_name.push_back("$\\sigma_L$");
  params_sig_mass_name.push_back("$\\sigma_R$");
  params_sig_mass_name.push_back("$\\alpha_L$");
  params_sig_mass_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_mass.size(); par++ ) {

    textfile << params_sig_mass_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-Zonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_mass[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_mass}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;

  // sinMHTphiMET Cruijff
  textfile << "% SIGNAL sinMHTphiMET CRUIJFF\n " << endl;
  vector<string> params_sig_sinMHTphiMET;
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_mean");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_sigmaL");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_sigmaR");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_alphaL");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_alphaR");

  vector<string> params_sig_sinMHTphiMET_name;
  params_sig_sinMHTphiMET_name.push_back("$mean$");
  params_sig_sinMHTphiMET_name.push_back("$\\sigma_L$");
  params_sig_sinMHTphiMET_name.push_back("$\\sigma_R$");
  params_sig_sinMHTphiMET_name.push_back("$\\alpha_L$");
  params_sig_sinMHTphiMET_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_sinMHTphiMET.size(); par++ ) {

    textfile << params_sig_sinMHTphiMET_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-Zonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_sinMHTphiMET[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_sinMHTphiMET}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;



  textfile << "\n\n\n\n" << endl;




  // ==============
  // background PDFs
  // ==============

  textfile << "% ===== BACKGROUND Z->EE PDFS PARAMETERS ==== %" << endl;
  textfile << "\n\n\n\n" << endl;


  // bkg mee poly 2
  textfile << "% BKG MEE POLY 2\n" << endl;
  vector<string> params_bkg_mass;
  params_bkg_mass.push_back("bkg_Mass_p1");
  params_bkg_mass.push_back("bkg_Mass_p2");

  vector<string> params_bkg_mass_name;
  params_bkg_mass_name.push_back("$p_1$");
  params_bkg_mass_name.push_back("$p_2$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_bkg_mass.size(); par++ ) {

    textfile << params_bkg_mass_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-bkgonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_bkg_mass[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:bkg_mass}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;

  // bkg sinMHTphiMET poly 1
  textfile << "% BKG sinMHTphiMET POLY 1\n" << endl;
  vector<string> params_bkg_sinMHTphiMET;
  params_bkg_sinMHTphiMET.push_back("bkg_sinMHTphiMET_p1");

  vector<string> params_bkg_sinMHTphiMET_name;
  params_bkg_sinMHTphiMET_name.push_back("$p_1$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_bkg_sinMHTphiMET.size(); par++ ) {

    textfile << params_bkg_sinMHTphiMET_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-bkgonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_bkg_sinMHTphiMET[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:bkg_sinMHTphiMET}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;




  textfile << "\\end{document}" << endl;


}








void printPdfTablesW(const char *jetflavour) {

  char nametextfile[200];
  sprintf(nametextfile,"pdfParameters_Wenu_%s.tex",jetflavour);

  ofstream textfile;
  textfile.open(nametextfile, ios_base::trunc);
  textfile.precision(2);

  textfile << "\\documentclass{article}" << endl;
  textfile << "\\begin{document}" << endl;

  textfile << "\n\n\n\n" << endl;

  // ==============
  // signal PDFs
  // ==============

  textfile << "% ===== SIGNAL W->ENU PDFS PARAMETERS ==== %" << endl; 
  textfile << "\n\n\n\n" << endl;

  // sig Mt Crystal Cruijff
  textfile << "% SIGNAL MT CRYSTAL CRUIJFF\n" << endl;
  vector<string> params_sig_Mt;
  params_sig_Mt.push_back("sig_Mt_mean");
  params_sig_Mt.push_back("sig_Mt_sigma");
  params_sig_Mt.push_back("sig_Mt_alpha");
  params_sig_Mt.push_back("sig_Mt_alphaCB");
  params_sig_Mt.push_back("sig_Mt_nCB");

  vector<string> params_sig_Mt_name;
  params_sig_Mt_name.push_back("mean");
  params_sig_Mt_name.push_back("$\\sigma$");
  params_sig_Mt_name.push_back("$\\alpha$");
  params_sig_Mt_name.push_back("$\\alpha_{CB}$");
  params_sig_Mt_name.push_back("$n_{CB}$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_Mt.size(); par++ ) {

    textfile << params_sig_Mt_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-Wonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_Mt[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_Mt}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;


  // sig sinMHTphiJet Cruijff

  textfile << "% SIGNAL sinMHTphiJET CRUIJFF\n " << endl;
  vector<string> params_sig_sinMHTphiJet;
  params_sig_sinMHTphiJet.push_back("sig_sinMHTphiJet_mean");
  params_sig_sinMHTphiJet.push_back("sig_sinMHTphiJet_sigmaL");
  params_sig_sinMHTphiJet.push_back("sig_sinMHTphiJet_sigmaR");
  params_sig_sinMHTphiJet.push_back("sig_sinMHTphiJet_alphaL");
  params_sig_sinMHTphiJet.push_back("sig_sinMHTphiJet_alphaR");

  vector<string> params_sig_sinMHTphiJet_name;
  params_sig_sinMHTphiJet_name.push_back("$mean$");
  params_sig_sinMHTphiJet_name.push_back("$\\sigma_L$");
  params_sig_sinMHTphiJet_name.push_back("$\\sigma_R$");
  params_sig_sinMHTphiJet_name.push_back("$\\alpha_L$");
  params_sig_sinMHTphiJet_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_sinMHTphiJet.size(); par++ ) {

    textfile << params_sig_sinMHTphiJet_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-Wonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_sinMHTphiJet[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_sinMHTphiJet}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;



  textfile << "\n\n\n\n" << endl;










  // ==============
  // ttbar PDFs
  // ==============

  textfile << "% ===== TTBAR W->ENU PDFS PARAMETERS ==== %" << endl;
  textfile << "\n\n\n\n" << endl;



  // ttbar Mt Crystal Cruijff
  textfile << "% TTBAR MT CRYSTAL CRUIJFF\n" << endl;
  vector<string> params_ttbar_Mt;
  params_ttbar_Mt.push_back("ttbar_Mt_mean");
  params_ttbar_Mt.push_back("ttbar_Mt_sigma");
  params_ttbar_Mt.push_back("ttbar_Mt_alpha");
  params_ttbar_Mt.push_back("ttbar_Mt_alphaCB");
  params_ttbar_Mt.push_back("ttbar_Mt_nCB");

  vector<string> params_ttbar_Mt_name;
  params_ttbar_Mt_name.push_back("mean");
  params_ttbar_Mt_name.push_back("$\\sigma$");
  params_ttbar_Mt_name.push_back("$\\alpha$");
  params_ttbar_Mt_name.push_back("$\\alpha_{CB}$");
  params_ttbar_Mt_name.push_back("$n_{CB}$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_ttbar_Mt.size(); par++ ) {

    textfile << params_ttbar_Mt_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-ttbaronly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_ttbar_Mt[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:ttbar_Mt}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;


  // ttbar sinMHTphiJet Cruijff

  textfile << "% TTBAR sinMHTphiJET CRUIJFF\n " << endl;
  vector<string> params_ttbar_sinMHTphiJet;
  params_ttbar_sinMHTphiJet.push_back("ttbar_sinMHTphiJet_mean");
  params_ttbar_sinMHTphiJet.push_back("ttbar_sinMHTphiJet_sigmaL");
  params_ttbar_sinMHTphiJet.push_back("ttbar_sinMHTphiJet_sigmaR");
  params_ttbar_sinMHTphiJet.push_back("ttbar_sinMHTphiJet_alphaL");
  params_ttbar_sinMHTphiJet.push_back("ttbar_sinMHTphiJet_alphaR");

  vector<string> params_ttbar_sinMHTphiJet_name;
  params_ttbar_sinMHTphiJet_name.push_back("$mean$");
  params_ttbar_sinMHTphiJet_name.push_back("$\\sigma_L$");
  params_ttbar_sinMHTphiJet_name.push_back("$\\sigma_R$");
  params_ttbar_sinMHTphiJet_name.push_back("$\\alpha_L$");
  params_ttbar_sinMHTphiJet_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_ttbar_sinMHTphiJet.size(); par++ ) {

    textfile << params_ttbar_sinMHTphiJet_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-ttbaronly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_ttbar_sinMHTphiJet[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:ttbar_sinMHTphiJet}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;



  textfile << "\n\n\n\n" << endl;









  // ==============
  // other PDFs
  // ==============

  textfile << "% ===== OTHER W->ENU PDFS PARAMETERS ==== %" << endl;
  textfile << "\n\n\n\n" << endl;



  // other Mt Crystal Cruijff
  textfile << "% OTHER MT CRYSTAL CRUIJFF\n" << endl;
  vector<string> params_other_Mt;
  params_other_Mt.push_back("other_Mt_mean");
  params_other_Mt.push_back("other_Mt_sigma");
  params_other_Mt.push_back("other_Mt_alpha");
  params_other_Mt.push_back("other_Mt_alphaCB");
  params_other_Mt.push_back("other_Mt_nCB");

  vector<string> params_other_Mt_name;
  params_other_Mt_name.push_back("mean");
  params_other_Mt_name.push_back("$\\sigma$");
  params_other_Mt_name.push_back("$\\alpha$");
  params_other_Mt_name.push_back("$\\alpha_{CB}$");
  params_other_Mt_name.push_back("$n_{CB}$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_other_Mt.size(); par++ ) {

    textfile << params_other_Mt_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-otheronly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_other_Mt[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:other_Mt}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;


  // other sinMHTphiJet Cruijff

  textfile << "% SIGNAL sinMHTphiJET CRUIJFF\n " << endl;
  vector<string> params_other_sinMHTphiJet;
  params_other_sinMHTphiJet.push_back("other_sinMHTphiJet_mean");
  params_other_sinMHTphiJet.push_back("other_sinMHTphiJet_sigmaL");
  params_other_sinMHTphiJet.push_back("other_sinMHTphiJet_sigmaR");
  params_other_sinMHTphiJet.push_back("other_sinMHTphiJet_alphaL");
  params_other_sinMHTphiJet.push_back("other_sinMHTphiJet_alphaR");

  vector<string> params_other_sinMHTphiJet_name;
  params_other_sinMHTphiJet_name.push_back("$mean$");
  params_other_sinMHTphiJet_name.push_back("$\\sigma_L$");
  params_other_sinMHTphiJet_name.push_back("$\\sigma_R$");
  params_other_sinMHTphiJet_name.push_back("$\\alpha_L$");
  params_other_sinMHTphiJet_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_other_sinMHTphiJet.size(); par++ ) {

    textfile << params_other_sinMHTphiJet_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesWenu/root/fitRes-otheronly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_other_sinMHTphiJet[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:other_sinMHTphiJet}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;



  textfile << "\n\n\n\n" << endl;







  textfile << "\\end{document}" << endl;

}







std::pair<float, float> getParameterVal(RooFitResult *fitres, const char *name) {

  RooArgList floatingList = fitres->floatParsFinal();
  RooRealVar *var = (RooRealVar*)floatingList.find(name);

  if(var==0) return std::make_pair(0,0);

  float val = var->getVal();
  float err = var->getError();

  return std::make_pair(val,err);

}
